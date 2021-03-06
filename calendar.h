#include <QtGui>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QtNetwork>

#include "vcalparser.h"
#include "eventmodel.h"
#include "eventtableview.h"
#include "task.h"
#include "tevent.h"
#include "ttodo.h"
#include "eventdelegate.h"
#include "statusindicator.h"
#include "contextmenu.h"

#ifndef CALENDAR_H
#define CALENDAR_H

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
	void authenticate(QNetworkReply* reply, QAuthenticator* auth);
	void configSettings();
	void configNetwork();

	void fetchCalendarData();
	void getData();

	void outputError(QNetworkReply::NetworkError error);
	void outputError(QString message);

	void saveCalendarData();
	void saveCalendarData(QNetworkReply *reply);
	void saveSettings();
	void showEventInfo(const QModelIndex & index);
	void showTodoInfo(int row, int col);

	void transmissionStats(const qint64 done, const qint64 total);
	void viewUpdatedCalendar();

signals:
	void listPopulated();
	void configChanged();
	void visibleRow(int row);
	void authLoop();

private:
	void checkSettings();
	void populateList();
	void prepareTable();
	void viewCalendar();
  
	EventTableView *m_events;
	QTableWidget *m_todos;
	QTabWidget *m_tabs;
	QStackedWidget *stackedWidget;
	QNetworkAccessManager *networkManager;
	QNetworkReply *networkReply;
	VCalParser *parser;
	EventModel *eventModel;
	QSettings *settings;
	QString location;
	QFile calendar;
	QTextStream data;
	int m_nextItemRow;
	int m_currentEventRow;
	int authRetries;
	QWidget *m_configDialog, *m_netDialog, *m_mainWidget;
	QLineEdit *urlscheme, *hostname, *port, *path, *username, *password, *proxyHost, *proxyPort;
	QPushButton *saveSettingsBtn, *saveNetworkBtn, *abortSettingsBtn, *abortNetworkBtn;
	QCheckBox *useProxy, *useTodos;
	StatusIndicator *status;
	ContextMenu *menu;
	
#ifdef Q_OS_SYMBIAN
	bool bDefaultIapSet;
#endif
};

#endif // CALENDAR_H
