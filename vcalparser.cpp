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
	qDebug() << "parsing calendar...";

	QList<QMap<QString, QString> > eventList = split("VEVENT");

	TEvent event;

	for (int i = 0; i < eventList.size(); i++) {

		event.setDescription(eventList.at(i)["DESCRIPTION"]);
		event.setSummary(eventList.at(i)["SUMMARY"]);
		if (eventList.at(i)["DTSTART"].size() > 1) {
			//qDebug() << " DATETIME: " << .toString("yyyy-MM-dd, hh:mm:ss");
			event.setStart(decodeDate(eventList.at(i)["DTSTART"]));
		}

		event.setStart();
		event.setEnd();
		// qDebug() << event.toString();

		m_events.append(event);
	}
}

QDateTime VCalParser::decodeDate(QString date)
{
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
