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

VCalParser::VCalParser(QString &vcaldata)
{
	m_rawData = new QString(vcaldata);
	getEvents();
	getTodos();
}

QList<QMap <QString, QString> > VCalParser::split()
{
	return split("VEVENT");
}

QList<QMap <QString, QString> > VCalParser::split(QString type)
{
	QStringList lines = m_rawData->split(QRegExp("\r\n"), QString::SkipEmptyParts);

	QList<QMap <QString, QString> > itemsList;
	QMap<QString, QString> temp;

	for (int i = 0; i < lines.size(); ++i) {
		if (lines.at(i).contains("BEGIN:" + type)) {
			// make a clean list for the new event
			temp.clear();
		}
		if(!lines.at(i).startsWith(" ") && lines.at(i).contains(":")) {
			temp[lines.at(i).split(":").at(0)] = lines.at(i).split(":").at(1);
		}
		if (lines.at(i).contains("END:" + type)) {
			// event is over, append to itemsList
			itemsList.append(temp);
		}

	}
	return itemsList;
}

void VCalParser::getEvents()
{
	qDebug() << "parsing calendar (events) ...";

	QList<QMap<QString, QString> > eventList = split("VEVENT");

	TEvent event;
	nextEvent.setStart(QDateTime::currentDateTime().addYears(100));

	for (int i = 0; i < eventList.size(); i++) {
		event.setUid(eventList.at(i)["UID"]);
		event.setDescription(eventList.at(i)["DESCRIPTION"]);
		event.setSummary(eventList.at(i)["SUMMARY"]);
		event.setLocation(eventList.at(i)["LOCATION"]);
		// start date
		if (eventList.at(i)["DTSTART"].size() > 1) {
			event.setStart(decodeDate(eventList.at(i)["DTSTART"]));
		} else if (eventList.at(i)["DTSTART;VALUE=DATE"].size() > 1) {
			event.setStart(decodeDate(eventList.at(i)["DTSTART;VALUE=DATE"]));
		}
		// end date
		if (eventList.at(i)["DTEND"].size() > 1) {
			event.setEnd(decodeDate(eventList.at(i)["DTEND"]));
		} else if (eventList.at(i)["DTEND;VALUE=DATE"].size() > 1) {
			event.setEnd(decodeDate(eventList.at(i)["DTEND;VALUE=DATE"]));
		}
		event.setLastModified(decodeDate(eventList.at(i)["LAST-MODIFIED"]));
		event.setClass(eventList.at(i)["CLASS"]);
		event.setStatus(eventList.at(i)["STATUS"]);

		// event is in the future
		if(event.getStart() > QDateTime::currentDateTime()) {
			if(event < nextEvent) {
				nextEvent = event;
			}
		}

		m_events.append(event);
	}

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
	qDebug() << "parsing calendar (todos) ...";
	QList<QMap<QString, QString> > todoList = split("VTODO");
	TTodo todo;

	for (int i = 0; i < todoList.size(); i++) {
		todo.setUid(todoList.at(i)["UID"]);
		todo.setDescription(todoList.at(i)["DESCRIPTION"]);
		todo.setSummary(todoList.at(i)["SUMMARY"]);
		todo.setLocation(todoList.at(i)["LOCATION"]);
		todo.setPercentComplete(todoList.at(i)["PERCENT-COMPLETE"].toInt());
		todo.setLastModified(decodeDate(todoList.at(i)["LAST-MODIFIED"]));
		todo.setClass(todoList.at(i)["CLASS"]);
		todo.setStatus(todoList.at(i)["STATUS"]);

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
