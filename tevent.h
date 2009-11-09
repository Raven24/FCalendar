#include <QDateTime>
#include "task.h"

#ifndef TEVENT_H
#define TEVENT_H

class Task;

class TEvent : public Task
{
public:
    TEvent();

	void setStart();
	void setEnd();
	void setStart(const QDateTime start);
	void setEnd(const QDateTime end);
	void setNextItem(const bool isNext);

	QDateTime	getStart();
	QDateTime	getEnd();
	QString     getStartString();
	QString		getRemaining();
	QString		toString();
	bool		isNextItem();

private:
	QDateTime	m_start;
	QDateTime	m_end;
	bool		m_nextItem;
};

#endif // TEVENT_H
