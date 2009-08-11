#include <QHttp>
#include <QTabWidget>

#ifndef CALENDAR_H
#define CALENDAR_H

#include <QtGui/QMainWindow>


class QTableWidget;
class QHttp;

class Calendar : public QMainWindow
{
    Q_OBJECT

public:
    Calendar(QWidget *parent = 0);
    ~Calendar();

	void getData();
	void initNetwork();

public slots:
	void populateList();

private:
	QTableWidget *m_events;
	QTableWidget *m_todos;
	QTabWidget *m_tabs;
	QHttp m_http;
};

#endif // CALENDAR_H
