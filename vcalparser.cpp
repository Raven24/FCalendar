#include <QtGui>
#include <QStringList>
#include <QList>
#include <QMap>

#include "vcalparser.h"
#include "task.h"
#include "tevent.h"
#include "ttodo.h"

VCalParser::VCalParser()
{
	qDebug() << "not possible";
}

VCalParser::VCalParser(QString *vcaldata):
		m_rawData(vcaldata)
{
	getEvents();
	getTodos();
}

QList<QMap <QString, QString> > VCalParser::split()
{
	return split("VEVENT");
}

QList<QMap <QString, QString> > VCalParser::split(QString type)
{
	//QTime time;
	QStringList lines = m_rawData->split(QRegExp("\n"), QString::SkipEmptyParts);
	QStringList::const_iterator i;
	QList<QMap <QString, QString> > itemsList;
	QMap<QString, QString> temp;

	//time.start();
	for (i = lines.constBegin(); i != lines.constEnd(); ++i) {
		if ((*i).contains("BEGIN:" + type)) {
			// make a clean list for the new event
			temp.clear();
		}
		if(!(*i).startsWith(" ") && (*i).contains(":")) {
			temp[(*i).split(":").at(0)] = (*i).split(":").at(1);
		}
		if ((*i).contains("END:" + type)) {
			// event is over, append to itemsList
			itemsList.append(temp);
		}

	}
	//qDebug() << "[debug] splitting took: " << time.elapsed();
	return itemsList;
}

void VCalParser::getEvents()
{
	qDebug() << "[calendar] parsing events";
	//QTime time;

	QList<QMap<QString, QString> > eventList = split("VEVENT");
	nextEvent.setStart(QDateTime::currentDateTime().addYears(100));

	//time.start();
	QList<QMap<QString, QString> >::const_iterator i;
	for (i = eventList.constBegin(); i != eventList.constEnd(); ++i) {

		TEvent event;
		event.setUid((*i).value("UID"));
		event.setDescription((*i).value("DESCRIPTION"));
		event.setSummary((*i).value("SUMMARY"));
		event.setLocation((*i).value("LOCATION"));
		// start date
		if ((*i).value("DTSTART").size() > 1) {
			event.setStart(decodeDate((*i).value("DTSTART")));
		} else if ((*i).value("DTSTART;VALUE=DATE").size() > 1) {
			event.setStart(decodeDate((*i).value("DTSTART;VALUE=DATE")));
		}
		// end date
		if ((*i).value("DTEND").size() > 1) {
			event.setEnd(decodeDate((*i).value("DTEND")));
		} else if ((*i).value("DTEND;VALUE=DATE").size() > 1) {
			event.setEnd(decodeDate((*i).value("DTEND;VALUE=DATE")));
		}
		event.setLastModified(decodeDate((*i).value("LAST-MODIFIED")));
		event.setClass((*i).value("CLASS"));
		event.setStatus((*i).value("STATUS"));

		// event is in the future
		if(event.getStart() > QDateTime::currentDateTime()) {
			if(event < nextEvent) {
				nextEvent = event;
			}
		}
		m_events.append(event);
	}
	//qDebug() << "[debug] parsing events took: " << time.elapsed();

	qSort(m_events);

	if(nextEvent.isValid()) {
		nextEventIndex = m_events.indexOf(nextEvent);
	} else {
		// there seems to be no reasonable event in the near future
		nextEventIndex = m_events.size()-1;
	}
}

void VCalParser::getTodos()
{
	qDebug() << "[calendar] parsing todos";
	QList<QMap<QString, QString> > todoList = split("VTODO");

	QList<QMap<QString, QString> >::const_iterator i;
	for (i = todoList.constBegin(); i != todoList.constEnd(); ++i) {
		TTodo todo;
		todo.setUid((*i).value("UID"));
		todo.setDescription((*i).value("DESCRIPTION"));
		todo.setSummary((*i).value("SUMMARY"));
		todo.setLocation((*i).value("LOCATION"));
		todo.setPercentComplete((*i).value("PERCENT-COMPLETE").toInt());
		todo.setLastModified(decodeDate((*i).value("LAST-MODIFIED")));
		todo.setClass((*i).value("CLASS"));
		todo.setStatus((*i).value("STATUS"));

		m_todos.append(todo);
	}
}

/**
 * convert the VCAL date/time string into something useful
 */
QDateTime VCalParser::decodeDate(QString date)
{
	if (date.size() < 9) {
		return QDateTime::fromString(date, "yyyyMMdd");
	}
	return QDateTime::fromString(date, "yyyyMMddThhmmssZ");
}
