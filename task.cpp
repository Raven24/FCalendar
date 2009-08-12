#include "task.h"

#include <QString>

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

QString Task::toString()
{
	return QString("UID: %3\n\tSummary: %1,\n\tDescription: %2")
			.arg(m_summary).arg(m_description).arg(m_uid);
}
