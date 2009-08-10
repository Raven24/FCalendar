#include <QList>
#include <QMap>

#ifndef VCALPARSER_H
#define VCALPARSER_H

class QString;
class QStringList;
class Task;
class TEvent;
class TTodo;

class VCalParser
{
public:
    VCalParser();
	VCalParser(QString &vcaldata);

	void getEvents();
	QList<TEvent> m_events;
	QList<TTodo> m_todos;
private:
	QList<QMap <QString, QString> > split();
	QList<QMap <QString, QString> > split(QString type);

	QString *m_rawData;
	QStringList *m_rawTasks;
};

#endif // VCALPARSER_H
