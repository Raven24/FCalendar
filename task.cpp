#include "task.h"

#include <QString>

Task::Task()
{
}

Task::Task(QString summ, QString desc)
{
	m_summary = summ;
	m_description = desc;
}

QString Task::getSummary()
{
	return m_summary;
}

QString Task::getDescription()
{
	return m_description;
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
	return QString("Summary: %1,\nDescription: %2")
			.arg(m_summary).arg(m_description);
}
