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

    QList<TEvent>	m_events;
	QList<TTodo>	m_todos;
	QDateTime		decodeDate(QString date);
	int				nextEventIndex;
	TEvent			nextEvent;

protected:
    void readEvent();
    void readTodo();

private:
    void read();
    const QString readLine();
    const QString readKey();
    const QString readValue();

	QString		*m_rawData;
	QStringList *m_rawTasks;
    QString::const_iterator i;
    bool        atEnd;
};

#endif // VCALPARSER_H
