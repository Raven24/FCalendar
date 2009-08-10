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
		event.setStart();
		event.setEnd();
		// qDebug() << event.toString();

		m_events.append(event);
	}
}
