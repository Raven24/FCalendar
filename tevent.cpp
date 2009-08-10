#include <QDateTime>

#include "tevent.h"
#include "task.h"

TEvent::TEvent()
{
}

void TEvent::setStart(const QDateTime start)
{
	m_start = start;
}

void TEvent::setEnd(const QDateTime end)
{
	m_end = end;
}

void TEvent::setStart()
{
	setStart(QDateTime::currentDateTime());
}

void TEvent::setEnd()
{
	setEnd(QDateTime::currentDateTime());
}

QDateTime TEvent::getStart()
{
	return QDateTime::currentDateTime();
}

QDateTime TEvent::getEnd()
{
	return QDateTime::currentDateTime();
}

QString TEvent::getRemaining()
{
	return QString("... h");
}
