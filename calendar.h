#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTabWidget>
#include <QSettings>

#include "vcalparser.h"

#ifndef CALENDAR_H
#define CALENDAR_H

#include <QtGui/QMainWindow>

class QWidget;
class QStackedWidget;
class QTableWidget;
class QTableWidgetItem;

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
	void scrollToNearestItem();
	void saveSettings();
	void abortSaveSettings();
	void configSettings();
	void configNetwork();

signals:
	void listPopulated();
	void settingsChanged(const QString which);

private:
	void checkSettings();
  
	QTableWidget *m_events;
	QTableWidget *m_todos;
	QTabWidget *m_tabs;
	QStackedWidget *stackedWidget;
	QNetworkAccessManager networkManager;
	VCalParser *parser;
	QSettings *settings;
	int m_nextItemRow;
	QWidget *m_configDialog;
	QWidget *m_netDialog;
	QLineEdit *urlscheme, *hostname, *port, *path, *username, *password, *proxyHost, *proxyPort;
	QPushButton *save, *abort;
	QCheckBox *useProxy;
	
#ifdef Q_OS_SYMBIAN
	bool bDefaultIapSet;
#endif
};

#endif // CALENDAR_H
