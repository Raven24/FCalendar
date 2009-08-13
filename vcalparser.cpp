#include "vcalparser.h"
#include "task.h"
#include "tevent.h"
#include "ttodo.h"

#include <QDebug>
#include <QStringList>
#include <QList>
#include <QMap>

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

		if (lines.at(i).contains(QString("BEGIN:") + type, Qt::CaseInsensitive)) {
			// make a clean list for the new event
			temp.clear();
		}
		if(!lines.at(i).startsWith(" ")) {
			temp[lines.at(i).split(":").at(0)] = lines.at(i).split(":").at(1);
		}
		if (lines.at(i).contains(QString("END:") + type, Qt::CaseInsensitive)) {
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
		// qDebug() << event.toString();

		m_events.append(event);
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

QDateTime VCalParser::decodeDate(QString date)
{
	if (date.size() < 9) {
		int year	= date.mid(0, 4).toInt();
		int month	= date.mid(4, 2).toInt();
		int day		= date.mid(6, 2).toInt();

		QDateTime retVal;
		retVal.setDate(QDate(year, month, day));

		return retVal;
	}

	QStringList splitted = date.split("T");
	int year	= splitted.at(0).mid(0, 4).toInt();
	int month	= splitted.at(0).mid(4, 2).toInt();
	int day		= splitted.at(0).mid(6, 2).toInt();
	int hours	= splitted.at(1).mid(0, 2).toInt();
	int mins	= splitted.at(1).mid(2, 2).toInt();
	int secs	= splitted.at(1).mid(4, 2).toInt();

	QDateTime retVal;
	retVal.setDate(QDate(year, month, day));
	retVal.setTime(QTime(hours, mins, secs, 0));

	return retVal;
}
