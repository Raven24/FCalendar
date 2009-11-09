#include "task.h"

#include <QString>
#include <QDateTime>

Task::Task()
{
}

Task::Task(QString uid)
{
	m_uid = uid;
}

Task::Task(QString summ, QString desc)
{
	m_summary = summ;
	m_description = desc;
}

QString Task::getUid()
{
	return m_uid;
}

QString Task::getSummary()
{
	return m_summary;
}

QString Task::getDescription()
{
	return m_description;
}

QString Task::getLocation()
{
	return m_location;
}

QDateTime Task::getLastModified()
{
	return m_lastModified;
}

QString Task::getClass()
{
	return m_class;
}

QString Task::getStatus()
{
	return m_status;
}

void Task::setUid(const QString uid)
{
	m_uid = QString(uid);
}

void Task::setDescription(const QString desc)
{
	m_description = QString(desc);
}

void Task::setSummary(const QString summ)
{
	m_summary = QString(summ);
}

void Task::setLocation(const QString loc)
{
	m_location = QString(loc);
}

void Task::setLastModified(const QDateTime last)
{
	m_lastModified = QDateTime(last);
}

void Task::setClass(const QString cls)
{
	m_class = QString(cls);
}

void Task::setStatus(const QString stat)
{
	m_status = QString(stat);
}

QString Task::toString()
{
	return QString("UID: %3\n\tSummary: %1,\n\tDescription: %2\n\tLocation: %4\n\tLast Modified: %5\n\tStatus: %6\n\tClass: %7")
			.arg(m_summary).arg(m_description).arg(m_uid).arg(m_location).arg(m_lastModified.toString()).arg(m_status).arg(m_class);
}
