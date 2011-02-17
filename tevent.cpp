#include <QDateTime>
#include <QDebug>

#include <math.h>

#include "tevent.h"
#include "task.h"

TEvent::TEvent()
{
	m_nextItem = false;
	setStart();
}

void TEvent::setStart(const QDateTime start)
{
	m_start = start;
	//qDebug() << m_start;
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

void TEvent::setNextItem(const bool isNext)
{
	m_nextItem = isNext;
}

QDateTime TEvent::getStart() const
{
	return m_start;
}

QString TEvent::getStartString()
{
    if(m_start.toString("h") == QString("0")) {
        return QString(m_start.toString("ddd d.M.yy"));
    } else {
        return QString(m_start.toString("ddd d.M.yy h:mm"));
    }
}

QDateTime TEvent::getEnd()
{
	return m_end;
}

QString TEvent::getRemaining()
{
	double span = m_start.secsTo(QDateTime::currentDateTime());
	bool pos = (span>0)?true:false;

	if(!pos) {
		span = span * (-1);
	}
	QString out;

	if (span > 62208000) {
		out = QString("%1 Jahre").arg(floor(span/31104000));
	} else if (span > 31104000) {
		out = QString("%1 Jahr").arg(floor(span/31104000));
	} else if (span > 5184000) {
		out = QString("%1 Monate").arg(floor(span/2592000));
	} else if (span > 2592000) {
		out = QString("%1 Monat").arg(floor(span/2592000));
	} else if (span > 172800) {
		out = QString("%1 Tage").arg(floor(span/86400));
	} else if (span > 86400) {
		out = QString("1 Tag");
	} else if (span > 3600) {
		out = QString("%1 Std.").arg(floor(span/3600));
	} else if (span > 1800) {
		out = QString("1 Std.");
	} else if (span > 900) {
		out = QString("30 Min.");
	} else if (span > 300) {
		out = QString("15 Min.");
	} else if (span > 60) {
		out = QString("%1 Min.").arg(floor(span/60));
	} else if (span > 0 ) {
		out = QString("%1 Sek.").arg(span);
	} else {
		out = QString("...strange");
	}

	if(pos) {
		out.prepend("-");
	}

	return out;
}

QString TEvent::toString()
{
	QString out = Task::toString();
	QString evtOut = QString("\n\tStart: %1\n\tEnd: %2\n\tRemaining: %3")
					 .arg(m_start.toString(), m_end.toString(), getRemaining());
	out.append(evtOut);
	return out;
}

/**
 * basic sanity check
 */
bool TEvent::isValid()
{
	if( (getSummary().size() > 1) &&
		(m_end.isValid())) {
		return true;
	}
	return false;
}

bool TEvent::isNextItem()
{
	return m_nextItem;
}

bool TEvent::operator<(const TEvent &other) const
{
    return m_start < other.getStart();
}

bool TEvent::operator==(const TEvent &other) const
{
    return m_start == other.getStart();
}
