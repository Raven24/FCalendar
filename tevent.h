#include <QDateTime>
#include "task.h"

#ifndef TEVENT_H
#define TEVENT_H

class Task;

class TEvent : public Task
{
public:
    TEvent();
	TEvent(const TEvent &event);

	void setStart();
	void setEnd();
	void setStart(const QDateTime start);
	void setEnd(const QDateTime end);

	QDateTime	getStart();
	QDateTime	getEnd();
	QString		getRemaining();

private:
	QDateTime m_start;
	QDateTime m_end;
};

#endif // TEVENT_H
