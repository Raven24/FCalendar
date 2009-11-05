#include <QtGui>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include "vcalparser.h"
#include "eventmodel.h"
#include "eventtableview.h"

#ifndef CALENDAR_H
#define CALENDAR_H

#include <QtGui/QMainWindow>

class QWidget;
class QStackedWidget;
class QTableWidget;
class QTableWidgetItem;
class QLineEdit;
class QPushButton;
class QCheckBox;

class Calendar : public QMainWindow
{
    Q_OBJECT

public:
    Calendar(QWidget *parent = 0);
    ~Calendar();

	void initNetwork();
	void defineSettings(const QString which);
	void setupConfigLayouts();

public slots:
	void populateList(QNetworkReply *networkReply);
	void showEventInfo(const QModelIndex & index);
	void showTodoInfo(int row, int col);
	void saveSettings();
	void viewUpdatedCalendar();
	void configSettings();
	void configNetwork();
	void getData();

signals:
	void listPopulated();
	void configChanged();
	void visibleRow(int row);

private:
	void checkSettings();
	void prepareTable();
  
	EventTableView *m_events;
//	QTableView *m_events;
	QTableWidget *m_todos;
	QTabWidget *m_tabs;
	QStackedWidget *stackedWidget;
	QNetworkAccessManager networkManager;
	VCalParser *parser;
	EventModel *eventModel;
	QSettings *settings;
	int m_nextItemRow;
	int m_currentEventRow;
	QWidget *m_configDialog;
	QWidget *m_netDialog;
	QLineEdit *urlscheme, *hostname, *port, *path, *username, *password, *proxyHost, *proxyPort;
	QPushButton *saveSettingsBtn, *saveNetworkBtn, *abortSettingsBtn, *abortNetworkBtn;
	QCheckBox *useProxy;
	
#ifdef Q_OS_SYMBIAN
	bool bDefaultIapSet;
#endif
};

#endif // CALENDAR_H
