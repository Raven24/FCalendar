#include "calendar.h"

#ifdef Q_OS_SYMBIAN
#include "sym_iap_util.h"
#endif

/**
 * constructor
 * set up all the members
 */
Calendar::Calendar(QWidget *parent)
	: QMainWindow(parent)
{
	settings    = new QSettings();
	m_tabs      = new QTabWidget();
	m_configDialog  = new QWidget();
	m_netDialog     = new QWidget();
	m_mainWidget    = new QWidget();

	status      = new StatusIndicator(this);
	status->setTitle(tr("Calendar"));

	stackedWidget = new QStackedWidget();
	stackedWidget->addWidget(m_configDialog);
	stackedWidget->addWidget(m_netDialog);
	stackedWidget->addWidget(m_tabs);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(status, 1);
	mainLayout->addWidget(stackedWidget, 10);
	mainLayout->setSpacing(0);
	m_mainWidget->setLayout(mainLayout);
	m_mainWidget->setContextMenuPolicy(Qt::NoContextMenu);

	urlscheme = new QLineEdit();
	hostname = new QLineEdit();
	port = new QLineEdit();
	path = new QLineEdit();
	username = new QLineEdit();
	password = new QLineEdit();
	proxyHost = new QLineEdit();
	proxyPort = new QLineEdit();
	useProxy = new QCheckBox();
	useTodos = new QCheckBox();
	saveSettingsBtn = new QPushButton(tr("Save"));
	abortSettingsBtn = new QPushButton(tr("Abort"));
	saveNetworkBtn = new QPushButton(tr("Save"));
	abortNetworkBtn = new QPushButton(tr("Abort"));

	m_nextItemRow = 0;
	m_currentEventRow = 0;
	authRetries = 0;

	setupConfigLayouts();
	qDebug() << "[startup] checking for settings";
	checkSettings();

	setContextMenuPolicy(Qt::CustomContextMenu);

	qDebug() << "[startup] setting up MVC architecture";

	eventModel = new EventModel(this);
	EventDelegate *eventDelegate = new EventDelegate(this);

	m_events = new EventTableView();
	m_events->setModel(eventModel);
	m_events->setItemDelegate(eventDelegate);

	m_todos = new QTableWidget(0, 1);

	qDebug() << "[startup] connecting signals and slots";

	//connect signals
	connect(m_events, SIGNAL(activated(QModelIndex)), this, SLOT(showEventInfo(QModelIndex)));
	connect(m_events, SIGNAL(cursorChanged(QModelIndex)),
			this, SLOT(showEventInfo(QModelIndex)));
	connect(m_todos, SIGNAL(cellClicked(int,int)), this, SLOT(showTodoInfo(int, int)));

	connect(this, SIGNAL(authLoop()),
			this, SLOT(configSettings()));
	connect(this, SIGNAL(visibleRow(int)),
			m_events, SLOT(selectRow(int)));

	//connect(updateCal, SIGNAL(triggered()), this, SLOT(viewUpdatedCalendar()));
	connect(this, SIGNAL(configChanged()),
			this, SLOT(fetchCalendarData()));

	connect(saveSettingsBtn, SIGNAL(clicked()), this, SLOT(saveSettings()));
	connect(abortSettingsBtn, SIGNAL(clicked()), this, SLOT(viewUpdatedCalendar()));
	connect(saveNetworkBtn, SIGNAL(clicked()), this, SLOT(saveSettings()));
	connect(abortNetworkBtn, SIGNAL(clicked()), this, SLOT(viewUpdatedCalendar()));

	m_events->setSelectionMode(QAbstractItemView::SingleSelection);
	m_events->setSelectionBehavior(QAbstractItemView::SelectRows);

	m_todos->setSelectionMode(QAbstractItemView::SingleSelection);
	m_todos->setSelectionBehavior(QAbstractItemView::SelectRows);

	// tab bar or not
	if(settings->value("ui/useTodos", false).toBool()) {
		m_tabs->addTab(m_events, tr("Events"));
		m_tabs->addTab(m_todos, tr("Todos"));
		stackedWidget->setCurrentWidget(m_tabs);
	} else {
		stackedWidget->removeWidget(m_tabs);
		stackedWidget->addWidget(m_events);
		stackedWidget->setCurrentWidget(m_events);
	}

	qDebug() << "[startup] getting data";
	getData();

	setCentralWidget(m_mainWidget);

	qDebug() << "[startup] initializing menu";

	menu		= new ContextMenu(this);
	menu->setVisible(false);

	connect(this, SIGNAL(customContextMenuRequested(QPoint)),
			menu, SLOT(show()));
	connect(menu, SIGNAL(requestSettings()),
			this, SLOT(configSettings()));
	connect(menu, SIGNAL(requestNetwork()),
			this, SLOT(configNetwork()));
	connect(menu, SIGNAL(requestCalendar()),
			this, SLOT(viewUpdatedCalendar()));
	connect(menu, SIGNAL(requestQuit()),
			qApp, SLOT(quit()));

#ifdef Q_OS_SYMBIAN
	Qt::WindowFlags flags = windowFlags();
	flags |= Qt::WindowSoftkeysVisibleHint;
	flags &= ~Qt::WindowSoftkeysRespondHint;
	setWindowFlags(flags);

	QAction *menuAction = new QAction(tr("Options"), this);
	menuAction->setSoftKeyRole(QAction::PositiveSoftKey);
	m_mainWidget->addAction(menuAction);
	connect(menuAction, SIGNAL(triggered()),
			menu, SLOT(show()));

	QAction *cancelAction = new QAction(tr("Cancel"), menu);
	cancelAction->setSoftKeyRole(QAction::PositiveSoftKey);
	menu->addAction(cancelAction);
	connect(cancelAction, SIGNAL(triggered()),
			menu, SLOT(reject()));
#endif

}

/**
 * destructor
 */
Calendar::~Calendar()
{
}

/**
 * hand the data over to the parser and
 * fill the table with items
 */
void Calendar::populateList()
{
	prepareTable();
	QString response;
	data.seek(0);

	data.setCodec("UTF-8");

	while(!data.atEnd()) {
		QString line = data.readLine();
		response.append(line).append("\n");
	}
	response = data.codec()->toUnicode(response.toAscii());
	parser = new VCalParser(&response);

	eventModel->fetchData(parser);
	m_events->resizeRowsToContents();
	emit visibleRow(parser->nextEventIndex);
		showEventInfo(m_events->currentIndex());
	m_currentEventRow = parser->nextEventIndex;

	/*for (int j = 0; j < parser->m_todos.size(); j++) {
        TTodo todo =parser->m_todos.at(j);

        QTableWidgetItem *item1 = new QTableWidgetItem(todo.getSummary(), 0);
		int rohttp://suche.upc.at/upcatassist/dnsassist/main/?domain=qstackedwidgetw = m_todos->rowCount();
        m_todos->insertRow(row);
        m_todos->setItem(row, 0, item1);

	}*/

	emit listPopulated();
	status->hideIndicator();
}

/**
 * make sure data is available for populateList()
 * either cached data or request
 */
void Calendar::getData()
{
	status->showIndicator();

	if(location.isEmpty()) {
		outputError("calendar location not set");
		return;
	}

	//qDebug() << location;

	QDir path(location);
	if(!path.exists()) {
		if(!path.mkpath(location)) {
			outputError("could not create storage path");
			return;
		}
	}
	QDir::setCurrent(location);
	calendar.setFileName("calendar.ical");

	if(!calendar.open(QIODevice::ReadWrite | QIODevice::Text)) {
		outputError("failed to open calendar from file");
		return;
	}

	data.setDevice(&calendar);

	if(!calendar.exists() || (calendar.size() < qint64(100))) {
		fetchCalendarData();
	}

	populateList();
}

/**
 * takes care of the network connection on S60
 * initialises a QNetworkAccessManager and connects the signals
 */
void Calendar::initNetwork()
{
	qDebug() << "[net] setting up network";

#ifdef Q_OS_SYMBIAN
    bDefaultIapSet = false;
    if(!bDefaultIapSet) {
        qt_SetDefaultIap();
        bDefaultIapSet = true;
    }
#endif

    networkManager = new QNetworkAccessManager();

    if(settings->value("network/useProxy").toBool()) {
		qDebug() << "[net] setting proxy";

        QNetworkProxy proxy;
		proxy.setHostName(settings->value("network/proxyHost").toString());
		proxy.setPort(settings->value("network/proxyPort").toInt());
        proxy.setType(QNetworkProxy::HttpProxy);
        //qDebug() << "Proxy: " << settings->value("network/proxyHost").toString() << ":" << settings->value("network/proxyPort").toInt();

        networkManager->setProxy(proxy);
    }

    connect(networkManager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(saveCalendarData(QNetworkReply*)));
    connect(networkManager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
        this, SLOT(authenticate(QNetworkReply*, QAuthenticator*)));

    authRetries = 0;
	qDebug() << "[net] networking set up";
}

void Calendar::fetchCalendarData()
{
	status->showIndicator();

	initNetwork();

	qDebug() << "[net] fetching data";
	QUrl url;
	url.setScheme(settings->value("calendar/urlscheme").toString());
	url.setHost(settings->value("calendar/hostname").toString());
	url.setPath(settings->value("calendar/path").toString());
	//url.setPort(settings->value("calendar/port").toInt());

	networkReply = networkManager->get(QNetworkRequest(url));
	connect(networkReply, SIGNAL(downloadProgress(qint64,qint64)),
			this, SLOT(transmissionStats(qint64,qint64)));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)),
			this, SLOT(outputError(QNetworkReply::NetworkError)));

}

void Calendar::saveCalendarData()
{
	//qDebug() << "networkReply finished";
	saveCalendarData(networkReply);
}

void Calendar::saveCalendarData(QNetworkReply *reply)
{
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
				this, SLOT(outputError(QNetworkReply::NetworkError)));

	if(reply->error()) {
		qDebug() << "Calendar::saveCalendarData() \n\tnetwork error";
		int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		if(code == 404) {
			emit outputError(QString("404 - not found"));
		} else {
			qDebug() << "\t" << reply->errorString();
		}
		return;
	}

	//qDebug() << reply->header(QNetworkRequest::ContentTypeHeader);

	QString response(reply->readAll());

	data.seek(0);
	data << response;
	data.flush();
	qDebug() << "[info] new filesize: " << response.length();
	calendar.resize(response.length());

	reply->deleteLater();

	populateList();
}

/**
 * handles event-table navigation
 * expands the current row to display event location
 * resets the height of the previously selected row
 */
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

/**
 * handles clicks on a todo
 * TODO: implement something useful!
 */
void Calendar::showTodoInfo(int row, int col)
{
	qDebug() << "click at: " << row << ", " << col;
	TTodo todo = parser->m_todos.value(row);
	qDebug() << todo.toString();
}

/**
 * check to see if the necessary config values are set
 * if not shows the config dialogue
 */
void Calendar::checkSettings()
{	
	if (!settings->contains("calendar/hostname")) {
				qDe                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            