#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTabWidget>
#include <QSettings>

#include "vcalparser.h"

#ifndef CALENDAR_H
#define CALENDAR_H

#include <QtGui/QMainWindow>

class QTableWidget;

class Calendar : public QMainWindow
{
    Q_OBJECT

public:
    Calendar(QWidget *parent = 0);
    ~Calendar();

	void getData();
	void initNetwork();
	void defineSettings(const QString which);

public slots:
	void populateList(QNetworkReply *networkReply);
	void showEventInfo(int row, int col);
	void showTodoInfo(int row, int col);

private:
	void checkSettings();
  
	QTableWidget *m_events;
	QTableWidget *m_todos;
	QTabWidget *m_tabs;
	QNetworkAccessManager networkManager;
	VCalParser *parser;
	QSettings *settings;
	
#ifdef Q_OS_SYMBIAN
	bool bDefaultIapSet;
#endif
};

#endif // CALENDAR_H
