#include "calendar.h"
#include "task.h"
#include "tevent.h"
#include "ttodo.h"
#include "vcalparser.h"

#include <QtNetwork>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QDebug>
#include <QTabWidget>
#include <QLabel>
#include <QVBoxLayout>

#ifdef Q_OS_SYMBIAN
#include "sym_iap_util.h"
#endif

Calendar::Calendar(QWidget *parent)
	: QMainWindow(parent)
{
	settings = new QSettings("FCalendar", "FCalendar");
	checkSettings();
	
	m_events = new QTableWidget(0, 2);
	m_todos = new QTableWidget(0, 1);

	//connect signals
	connect(m_events, SIGNAL(cellClicked(int,int)), this, SLOT(showEventInfo(int, int)));
	connect(m_todos, SIGNAL(cellClicked(int,int)), this, SLOT(showTodoInfo(int, int)));
	connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(populateList(QNetworkReply*)));
	connect(this, SIGNAL(listPopulated()), this, SLOT(scrollToNearestItem()));

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
	m_tabs = new QTabWidget();
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

	setCentralWidget(m_tabs);
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
}

void Calendar::defineSettings(const QString which) 
{
	// TODO: config dialog via QStackedWidget and multiple widgets
	qDebug() << "definition of " << which << " not implemented, setting default values";
		
	settings->setValue("calendar/urlscheme", "http");
	settings->setValue("calendar/hostname", "aristoteles.serveftp.org");
	settings->setValue("calendar/port", 80);
	settings->setValue("calendar/path", "/calendar/icalclient.php");
	settings->setValue("calendar/username", "florian");
	settings->setValue("calendar/password", "Apfelkuchen12");	
	
	settings->setValue("network/proxyHost", "proxy.bmlv.gv.at");
	settings->setValue("network/useProxy", false);
#ifndef Q_OS_SYMBIAN
	settings->setValue("network/proxyPort", 3128);
#else
	settings->setValue("network/defaultIAP", "");
#endif
}
