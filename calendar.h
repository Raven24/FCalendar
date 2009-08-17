#include <QNetworkAccessManager>
#include <QTabWidget>

#include "vcalparser.h"

#ifndef CALENDAR_H
#define CALENDAR_H

#include <QtGui/QMainWindow>


class QTableWidget;
class QNetworkReply;

class Calendar : public QMainWindow
{
    Q_OBJECT

public:
    Calendar(QWidget *parent = 0);
    ~Calendar();

	void getData();
	void initNetwork();

public slots:
	void populateList(QNetworkReply *networkReply);
	void showEventInfo(int row, int col);
	void showTodoInfo(int row, int col);

private:
	QTableWidget *m_events;
	QTableWidget *m_todos;
	QTabWidget *m_tabs;
	QNetworkAccessManager networkManager;
	VCalParser *parser;
};

#endif // CALENDAR_H
