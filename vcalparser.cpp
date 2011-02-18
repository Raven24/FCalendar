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
	nextEvent.setStart(QDateTime::currentDateTime().addYears(100));
	atEnd = false;
	read();
}

void VCalParser::read()
{
	QString tmp;
	i = m_rawData->constBegin();

	while(i != m_rawData->constEnd()) {
		i++;

		// read until the next newline
		tmp = readLine();

		if( tmp == "BEGIN:VEVENT" && !atEnd ) {
			readEvent();
		}

		if( tmp == "BEGIN:VTODO" && !atEnd ) {
			readTodo();
		}

		if( tmp == "END:VCALENDAR" || atEnd ) {
			break;
		}

		tmp.clear();
	}

	qSort(m_events);

	if(nextEvent.isValid()) {
		nextEventIndex = m_events.indexOf(nextEvent);
	} else {
		// there seems to be no valid event in the near future
		nextEventIndex = m_events.size()-1;
	}
}

void VCalParser::readEvent()
{
	//qDebug() << "[calendar] reading event";
	//QTime time;

	QString key, val;
	TEvent event;

	//time.start();
	while( key != "END" && !atEnd ) {
		key = readKey();
		val = readValue();

		if( key == "UID" )				event.setUid(val);
		else if( key == "DESCRIPTION")  event.setDescription(val);
		else if( key == "SUMMARY")      event.setSummary(val);
		else if( key == "LOCATION")     event.setLocation(val);
		else if( key == "LAST-MODIFIED")event.setLastModified(decodeDate(val));
		else if( key == "CLASS")        event.setClass(val);
		else if( key == "STATUS")       event.setStatus(val);
		else if( key == "DTSTART" ||
				 key == "DTSTART;VALUE=DATE") {
			if( val.size() > 1 )		event.setStart(decodeDate(val));
		} else if( key == "DTEND" ||
				   key == "DTEND;VALUE=DATE") {
			if( val.size() > 1 )		event.setEnd(decodeDate(val));
		}

		// event is in the future
		if(event.getStart() > QDateTime::currentDateTime()) {
			if(event < nextEvent) nextEvent = event;
		}
	}

	m_events.append(event);
}

void VCalParser::readTodo()
{
	/*qDebug() << "[calendar] reading todo";
	//QList<QMap<QString, QString> > todoList = split("VTODO");

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
	}*/
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

/**
 * read one line from input
 */
const QString VCalParser::readLine()
{
	QString tmp;

	while( (*i) != '\n' && !atEnd ) {
		tmp += (*i);
		++i;
		if ( i == m_rawData->constEnd() ) atEnd = true;
	}
	return tmp;
}

/**
 * read the name of the property
 */
const QString VCalParser::readKey()
{
	QString tmp;

	while( (*i) != ':' && !atEnd ) {
		if( (*i) != '\n' ) tmp += (*i);
		++i;
		if ( i == m_rawData->constEnd() ) atEnd = true;
	}
	return tmp;
}

/**
 * read the value of the property
 * if the following line contains a space as first char,
 * then the value continues
 */
const QString VCalParser::readValue()
{
	QString tmp = readLine();
	if( tmp.startsWith(":") )
		tmp.remove(0, 1);
	return tmp;
}
