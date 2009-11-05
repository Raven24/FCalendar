#include "calendar.h"
#include "task.h"
#include "tevent.h"
#include "ttodo.h"
#include "vcalparser.h"
#include "eventdelegate.h"
#include "eventmodel.h"
#include "eventtableview.h"

#include <QtCore>
#include <QtGui>
#include <QtNetwork>

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

	urlscheme = new QLineEdit();
	hostname = new QLineEdit();
	port = new QLineEdit();
	path = new QLineEdit();
	username = new QLineEdit();
	password = new QLineEdit();
	proxyHost = new QLineEdit();
	proxyPort = new QLineEdit();
	useProxy = new QCheckBox();
	saveSettingsBtn = new QPushButton(tr("Save"));
	abortSettingsBtn = new QPushButton(tr("Abort"));
	saveNetworkBtn = new QPushButton(tr("Save"));
	abortNetworkBtn = new QPushButton(tr("Abort"));

	setupConfigLayouts();
	checkSettings();

	// context menu
	QAction *configuration = new QAction("Configuration", this);
	QAction *netSettings = new QAction("Net settings", this);
	QAction *calendar = new QAction("Display Calendar", this);
	QAction *updateCal = new QAction("Update Calendar", this);

#ifdef Q_OS_SYMBIAN
	menuBar()->addAction(configuration);
	menuBar()->addAction(netSettings);
	menuBar()->addAction(calendar);
	menuBar()->addAction(updateCal);
#else
	addAction(configuration);
	addAction(netSettings);
	addAction(calendar);
	addAction(updateCal);
	setContextMenuPolicy(Qt::ActionsContextMenu);
#endif

	eventModel = new EventModel(this);
	EventDelegate *eventDelegate = new EventDelegate(this);

	m_events = new EventTableView();
	//m_events = new QTableView();
	m_events->setModel(eventModel);
	m_events->setItemDelegate(eventDelegate);

	m_todos = new QTableWidget(0, 1);

	//connect signals
	//connect(m_events, SIGNAL(cellClicked(int,int)), this, SLOT(showEventInfo(int, int)));
	connect(m_events, SIGNAL(activated(QModelIndex)), this, SLOT(showEventInfo(QModelIndex)));
	connect(m_events, SIGNAL(cursorChanged(QModelIndex)),
			this, SLOT(showEventInfo(QModelIndex)));
	connect(m_todos, SIGNAL(cellClicked(int,int)), this, SLOT(showTodoInfo(int, int)));
	connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(populateList(QNetworkReply*)));

	connect(this, SIGNAL(visibleRow(int)), m_events, SLOT(selectRow(int)));

	connect(configuration, SIGNAL(triggered()), this, SLOT(configSettings()));
	connect(netSettings, SIGNAL(triggered()), this, SLOT(configNetwork()));
	connect(calendar, SIGNAL(triggered()), this, SLOT(viewUpdatedCalendar()));
	connect(updateCal, SIGNAL(triggered()), this, SLOT(viewUpdatedCalendar()));
	connect(this, SIGNAL(configChanged()), this, SLOT(getData()));

	connect(saveSettingsBtn, SIGNAL(clicked()), this, SLOT(saveSettings()));
	connect(abortSettingsBtn, SIGNAL(clicked()), this, SLOT(viewUpdatedCalendar()));
	connect(saveNetworkBtn, SIGNAL(clicked()), this, SLOT(saveSettings()));
	connect(abortNetworkBtn, SIGNAL(clicked()), this, SLOT(viewUpdatedCalendar()));

	m_events->setSelectionMode(QAbstractItemView::SingleSelection);
	m_events->setSelectionBehavior(QAbstractItemView::SelectRows);

	m_todos->setSelectionMode(QAbstractItemView::SingleSelection);
	m_todos->setSelectionBehavior(QAbstractItemView::SelectRows);

	// tab bar
	m_tabs->addTab(m_events, tr("Events"));
	m_tabs->addTab(m_todos, tr("Todos"));

#ifndef Q_OS_SYMBIAN

	if(settings->value("network/useProxy").toBool()) {
		qDebug() << "setting proxy";
		initNetwork();
	}

#else
	bDefaultIapSet = false;
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
		prepareTable();

		QString response(networkReply->readAll());
		// qDebug() << response;

		parser = new VCalParser(response);

		qDebug() << "populating list ...";

		eventModel->fetchData(parser);
		m_events->resizeRowsToContents();
		emit visibleRow(parser->nextEvent);
		showEventInfo(m_events->currentIndex());
		m_currentEventRow = parser->nextEvent;
		//showEventInfo(m_events->model()->index(parser->nextEvent, 0));

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

void Calendar::showEventInfo(const QModelIndex & index)
{
	// reset the height of the previously selected item
	m_events->setRowHeight(m_currentEventRow, m_events->itemDelegate(index)->sizeHint(QStyleOptionViewItem(), index).height());
	
	// set the height of the current row to what is specified in the sizeHint
	QStyleOptionViewItem option = QStyleOptionViewItem();
	option.state = QStyle::State_Selected;
	m_events->setRowHeight(index.row(), m_events->itemDelegate(index)->sizeHint(option, index).height());
	m_currentEventRow = index.row();
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
		return;
	} else if(!settings->contains("network/proxyHost")) {
		defineSettings("network");
		return;
	}
	//qDebug() << "checkSettings, currentIndex: " << stackedWidget->currentIndex();
	viewUpdatedCalendar();
}

void Calendar::setupConfigLayouts()
{
		QFormLayout *settingsLayout = new QFormLayout();

		settingsLayout->addRow(tr("URL scheme"), urlscheme);
		settingsLayout->addRow(tr("Hostname"), hostname);
		settingsLayout->addRow(tr("Port"), port);
		settingsLayout->addRow(tr("Path"), path);
		settingsLayout->addRow(tr("Username"), username),
		settingsLayout->addRow(tr("Password"), password);
		settingsLayout->addRow(saveSettingsBtn);
		settingsLayout->addRow(abortSettingsBtn);

		m_configDialog->setLayout(settingsLayout);
		settingsLayout = new QFormLayout();

		settingsLayout->addRow(tr("Proxy Host"), proxyHost);
		settingsLayout->addRow(tr("Proxy Port"), proxyPort);
		settingsLayout->addRow(tr("Use Proxy"), useProxy);
		settingsLayout->addRow(saveNetworkBtn);
		settingsLayout->addRow(abortNetworkBtn);

		m_netDialog->setLayout(settingsLayout);
}

void Calendar::prepareTable()
{
	for (int i = m_todos->rowCount()-1; i >= 0; --i)
		m_todos->removeRow(i);
//	for (int i = m_events->rowCount()-1; i >= 0; --i)
//		m_events->removeRow(i);

	// headers
	//QStringList eventLabels;
	QStringList todoLabels;

	//eventLabels << tr("Name") << tr("Time");
	todoLabels << tr("Todo");
//	m_events->setHorizontalHeaderLabels(eventLabels);
	m_events->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	m_events->verticalHeader()->hide();

	m_todos->setHorizontalHeaderLabels(todoLabels);
	m_todos->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	m_todos->verticalHeader()->hide();
}

void Calendar::defineSettings(const QString which) 
{
	if (which == QString("calendar")) {

		urlscheme->setText(settings->value("calendar/urlscheme", "http").toString());
		hostname->setText(settings->value("calendar/hostname").toString());
		port->setText(settings->value("calendar/port", QString("80")).toString());
		path->setText(settings->value("calendar/path", "/calendar.ical").toString());
		username->setText(settings->value("calendar/username", "").toString());
		password->setText(settings->value("calendar/password", "").toString());

		stackedWidget->setCurrentIndex(0);

	} else if (which == QString("network")) {

		proxyHost->setText(settings->value("network/proxyHost", "").toString());
		proxyPort->setText(settings->value("network/proxyPort", "").toString());
		useProxy->setChecked(settings->value("network/useProxy", false).toBool());

		stackedWidget->setCurrentIndex(1);

	}
}

void Calendar::saveSettings() {

	qDebug() << "saving settings ...";

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

	viewUpdatedCalendar();
}

void Calendar::viewUpdatedCalendar()
{
	//qDebug() << stackedWidget->currentIndex();
	stackedWidget->setCurrentIndex(2);

	emit configChanged();
}

void Calendar::configSettings()
{
	defineSettings("calendar");
}

void Calendar::configNetwork()
{
	defineSettings("network");
}
