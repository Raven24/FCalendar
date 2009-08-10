#include <QString>

#ifndef TASK_H
#define TASK_H

class QString;

class Task
{
public:
    Task();
	Task(QString summ, QString desc);

	QString getSummary();
	QString getDescription();
	QString toString();

	void setSummary(const QString summ);
	void setDescription(const QString desc);

private:
	QString m_summary;
	QString m_description;

};

#endif // TASK_H
