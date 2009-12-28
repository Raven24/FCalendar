#include <QList>
#include <QMap>
#include <QDateTime>
#include <QString>

#include "tevent.h"

#ifndef VCALPARSER_H
#define VCALPARSER_H

class QString;
class QStringList;
class Task;
class TTodo;

class VCalParser
{
public:
    VCalParser();
	VCalParser(QString *vcaldata);

	void getEvents();
	void getTodos();

	QList<TEvent>	m_events;
	QList<TTodo>	m_todos;
	QDateTime		decodeDate(QString date);
	int				nextEventIndex;
	TEvent			nextEvent;

private:
	QList<QMap <QString, QString> > split();
	QList<QMap <QString, QString> > split(QString type);

	QString		*m_rawData;
	QStringList *m_rawTasks;
};

#endif // VCALPARSER_H
