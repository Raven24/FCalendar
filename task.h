#include <QString>
#include <QDateTime>

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
	QString getLocation();
	QDateTime getLastModified();
	QString getStatus();
	QString getClass();
	QString toString();

	void setUid(const QString uid);
	void setSummary(const QString summ);
	void setDescription(const QString desc);
	void setLocation(const QString loc);
	void setLastModified(const QDateTime last);
	void setStatus(const QString stat);
	void setClass(const QString cls);

private:
	QString m_summary;
	QString m_description;
	QString m_uid;
	QString m_location;
	QDateTime m_lastModified;
	QString m_status;
	QString m_class;

};

#endif // TASK_H
