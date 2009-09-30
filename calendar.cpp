#include "calendar.h"
#include "task.h"
#include "tevent.h"
#include "ttodo.h"
#include "vcalparser.h"

#include <QtCore>
#include <QtGui>
#include <QtNetwork>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QDebug>
#include <QTabWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QStackedWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>

#ifdef Q_OS_SYMBIAN
#include "sym_iap_util.h"
#endif

Calendar::Calendar(QWidget *parent)
	: QMainWindow(parent)
{
	settings = new QSettings("FCalendar", "FCalendar");
	m_configDialog = new QWidget();
	m_netDialog = new QWidget();
	m_tabs = new QTabWidget();

	stackedWidget = new QStackedWidget();
	stackedWidget->addWidget(m_configDialog);
	stackedWidget->addWidget(m_netDialog);
	stackedWidget->addWidget(m_tabs);

	checkSettings();

	// context menu
	QAction *configuration = new QAction("Configuration", this);
	QAction *netSettings = new QAction("Net settings", this);
	QAction *calendar = new QAction("Display Calendar", this);
#if defined(Q_OS_SYMBIAN)
	menuBar()->addAction(configuration);
	menuBar()->addAction(netSettings);
	menuBar()->addAction(calendar);
#else
	addAction(configuration);
	addAction(netSettings);
	addAction(calendar);
	setContextMenuPolicy(Qt::ActionsContextMenu);
#endif

	m_events = new QTableWidget(0, 2);
	m_todos = new QTableWidget(0, 1);

	//connect signals
	connect(m_events, SIGNAL(cellClicked(int,int)), this, SLOT(showEventInfo(int, int)));
	connect(m_todos, SIGNAL(cellClicked(int,int)), this, SLOT(showTodoInfo(int, int)));
	connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(populateList(QNetworkReply*)));
	connect(this, SIGNAL(listPopulated()), this, SLOT(scrollToNearestItem()));
	connect(configuration, SIGNAL(triggered()), this, SLOT(configSettings()));
	connect(netSettings, SIGNAL(triggered()), this, SLOT(configNetwork()));
	connect(calendar, SIGNAL(triggered()), this, SLOT(abortSaveSettings()));

	m_events->setSelectionMode(QAbstractItemView::SingleSelection);
	m_events->setSelectionBehavior(QAbstractItemView::SelectRows);

	m_todos->setSelectionMode(QAbstractItemView::SingleSelection);
	m_todos->setSelectionBehavior(QAbstractItemView::SelectRows);

	// headers
	QStringList eventLabels;
	QStringList todoLabels;

	eventLabels << tr("Name") << tr("Time");
	todoLabels << tr("Todo");
	m_events->setHorizontalHeaderLabels(eventLabels);
	m_events->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	m_events->verticalHeader()->hide();

	m_todos->setHorizontalHeaderLabels(todoLabels);
	m_todos->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	m_todos->verticalHeader()->hide();

	// tab bar
	m_tabs->addTab(m_events, tr("Events"));
	m_tabs->addTab(m_todos, tr("Todos"));

#ifndef Q_OS_SYMBIAN

	if(settings->value("network/useProxy").toBool()) {
		qDebug() << "setting proxy";
		initNetwork();
	}

#else
	if(!bDefaultIapSet) {
		qt_SetDefaultIap();
		bDefaultIapSet = true;
	}
#endif
	getData();
	setCentralWidget(stackedWidget);
}

Calendar::~Calendar()
{
}

void Calendar::populateList(QNetworkReply *networkReply)
{
	if(!networkReply->error()) {
		QString response(networkReply->readAll());
		// qDebug() << response;

		parser = new VCalParser(response);

		qDebug() << "populating list ...";

		for (int i = 0; i < parser->m_events.size(); i++) {

			TEvent event = parser->m_events.at(i);

            //QTableWidgetItem *item1 = new QTableWidgetItem(event.getDescription(), 0);
            QTableWidgetItem *item2 = new QTableWidgetItem(event.getRemaining(), 0);
            //item1->setTextAlignment(Qt::AlignLeft);
            item2->setTextAlignment(Qt::AlignRight);

			QWidget *leftColumn = new QWidget;
            QLabel *eventDescr = new QLabel();
            QLabel *eventTime = new QLabel();

			// font settings
			QFont bigFont;
			bigFont.setPointSize(8);
			bigFont.setBold(true);

			QFont smallFont;
			smallFont.setPointSize(7);

			// color settings
            QString css = QString("QLabel { color: #454545; }");
			
            eventDescr->setText(event.getDescription());
			eventDescr->setFont(bigFont);
			eventDescr->setMinimumHeight(12);

			eventTime->setStyleSheet(css);
            eventTime->setText(event.getStartString());
			eventTime->setFont(smallFont);
            eventTime->setAlignment(Qt::AlignRight | Qt::AlignTop);
			eventTime->setMinimumHeight(27);

			QVBoxLayout *layout = new QVBoxLayout;
			layout->addWidget(eventDescr);
			layout->addWidget(eventTime);

			leftColumn->setLayout(layout);

			int row = m_events->rowCount();
			m_events->insertRow(row);
			if (event.isNextItem()) {
				m_nextItemRow = row;
			}
			m_events->setCellWidget(row, 0, leftColumn);
            //m_events->setItem(row, 1, item2);
            m_events->setItem(row, 1, item2);

		}

		for (int j = 0; j < parser->m_todos.size(); j++) {
			TTodo todo =parser->m_todos.at(j);

			QTableWidgetItem *item1 = new QTableWidgetItem(todo.getSummary(), 0);
			int row = m_todos->rowCount();
			m_todos->insertRow(row);
			m_todos->setItem(row, 0, item1);

		}

		networkReply->deleteLater();
	}

	emit listPopulated();
}

void Calendar::scrollToNearestItem()
{
	//qDebug() << m_nextItemRow;
	m_events->setCurrentCell(m_nextItemRow, 0);

}

void Calendar::getData()
{
	qDebug() << "fetching data...";
	QUrl url;
	url.setScheme(settings->value("calendar/urlscheme").toString());
	url.setHost(settings->value("calendar/hostname").toString());
	url.setPath(settings->value("calendar/path").toString());
	url.setUserName(settings->value("calendar/username").toString());
	url.setPassword(settings->value("calendar/password").toString());
	url.setPort(settings->value("calendar/port").toInt());
	
    //qDebug() << url.toString();
	
	networkManager.get(QNetworkRequest(url));
}

void Calendar::initNetwork()
{
  	QNetworkProxy proxy;
	proxy.setHostName(settings->value("network/proxyHost").toString());
	proxy.setPort(settings->value("network/proxyPort").toInt());
	proxy.setType(QNetworkProxy::HttpProxy);
	
	qDebug() << "Proxy: " << settings->value("network/proxyHost").toString() << ":" << settings->value("network/proxyPort").toInt();
	
	networkManager.setProxy(proxy);
}

void Calendar::showEventInfo(int row, int col)
{
	qDebug() << "click at: " << row << ", " << col;
	TEvent evt = parser->m_events.value(row);
	qDebug() << evt.toString();
}

void Calendar::showTodoInfo(int row, int col)
{
	qDebug() << "click at: " << row << ", " << col;
	TTodo todo = parser->m_todos.value(row);
	qDebug() << todo.toString();
}

void Calendar::checkSettings()
{	
	if (!settings->contains("calendar/hostname")) {
		defineSettings("calendar");
	} else if(!settings->contains("network/proxyHost")) {
		defineSettings("network");
	}
	//qDebug() << "checkSettings, currentIndex: " << stackedWidget->currentIndex();
	abortSaveSettings();
}

void Calendar::defineSettings(const QString which) 
{


	QFormLayout *settingsLayout = new QFormLayout();

	if (which == QString("calendar")) {
		stackedWidget->setCurrentIndex(0);
		urlscheme = new QLineEdit(settings->value("calendar/urlscheme", "http").toString());
		hostname = new QLineEdit(settings->value("calendar/hostname").toString());
		port = new QLineEdit(settings->value("calendar/port", QString("80")).toString());
		path = new QLineEdit(settings->value("calendar/path", "/calendar.ical").toString());
		username = new QLineEdit(settings->value("calendar/username", "").toString());
		password = new QLineEdit(settings->value("calendar/password", "").toString());

		save =  new QPushButton(tr("Save"));
		abort =  new QPushButton(tr("Abort"));
		connect(save, SIGNAL(clicked()), this, SLOT(saveSettings()));
		connect(abort, SIGNAL(clicked()), this, SLOT(abortSaveSettings()));

		settingsLayout->addRow(tr("URL scheme"), urlscheme);
		settingsLayout->addRow(tr("Hostname"), hostname);
		settingsLayout->addRow(tr("Port"), port);
		settingsLayout->addRow(tr("Path"), path);
		settingsLayout->addRow(tr("Username"), username),
		settingsLayout->addRow(tr("Password"), password);
		settingsLayout->addRow(save);
		settingsLayout->addRow(abort);

		delete m_configDialog->layout();
		m_configDialog->setLayout(settingsLayout);

	} else if (which == QString("network")) {
		stackedWidget->setCurrentIndex(1);
		proxyHost = new QLineEdit(settings->value("network/proxyHost", "").toString());
		proxyPort = new QLineEdit(settings->value("network/proxyPort", "").toString());
		useProxy = new QCheckBox();
		useProxy->setChecked(settings->value("network/useProxy", false).toBool());

		save =  new QPushButton(tr("Save"));
		abort =  new QPushButton(tr("Abort"));
		connect(save, SIGNAL(clicked()), this, SLOT(saveSettings()));
		connect(abort, SIGNAL(clicked()), this, SLOT(abortSaveSettings()));

		settingsLayout->addRow(tr("Proxy Host"), proxyHost);
		settingsLayout->addRow(tr("Proxy Port"), proxyPort);
		settingsLayout->addRow(tr("Use Proxy"), useProxy);
		settingsLayout->addRow(save);
		settingsLayout->addRow(abort);

		delete m_netDialog->layout();
		m_netDialog->setLayout(settingsLayout);
	}

}

void Calendar::saveSettings() {

	settings->setValue("calendar/urlscheme", urlscheme->text());
	settings->setValue("calendar/hostname", hostname->text());
	settings->setValue("calendar/port", port->text().toInt());
	settings->setValue("calendar/path", path->text());
	settings->setValue("calendar/username", username->text());
	settings->setValue("calendar/password", password->text());
	
	settings->setValue("network/proxyHost", proxyHost->text());
	settings->setValue("network/useProxy", useProxy->isChecked());
#ifndef Q_OS_SYMBIAN
	settings->setValue("network/proxyPort", proxyPort->text().toInt());
#else
	settings->setValue("network/defaultIAP", "");
#endif
}

void Calendar::abortSaveSettings()
{
	//qDebug() << stackedWidget->currentIndex();
	stackedWidget->setCurrentIndex(2);
}

void Calendar::configSettings()
{
	defineSettings("calendar");
}

void Calendar::configNetwork()
{
	defineSettings("network");
}
