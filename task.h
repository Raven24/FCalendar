#include <QString>

#ifndef TASK_H
#define TASK_H

class QString;

class Task
{
public:
    Task();
	Task(QString uid);
	Task(QString summ, QString desc);

	QString getUid();
	QString getSummary();
	QString getDescription();
	QString toString();

	void setUid(const QString uid);
	void setSummary(const QString summ);
	void setDescription(const QString desc);

private:
	QString m_summary;
	QString m_description;
	QString m_uid;

};

#endif // TASK_H
