#include "calendar.h"
#include "task.h"
#include "tevent.h"
#include "ttodo.h"
#include "vcalparser.h"

#include <QTNetwork>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QDebug>
#include <QTabWidget>

Calendar::Calendar(QWidget *parent)
	: QMainWindow(parent)
{
	m_events = new QTableWidget(0, 2);
	m_todos = new QTableWidget(0, 1);

	//connect signals
	connect(m_events, SIGNAL(cellClicked(int,int)), this, SLOT(showEventInfo(int, int)));
	connect(m_todos, SIGNAL(cellClicked(int,int)), this, SLOT(showTodoInfo(int, int)));
	connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(populateList(QNetworkReply*)));

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

	//initNetwork();
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

			QTableWidgetItem *item1 = new QTableWidgetItem(event.getDescription(), 0);
			QTableWidgetItem *item2 = new QTableWidgetItem(event.getRemaining(), 0);

			int row = m_events->rowCount();
			m_events->insertRow(row);

			m_events->setItem(row, 0, item1);
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
}

void Calendar::getData()
{
	qDebug() << "fetching data...";
	networkManager.get(QNetworkRequest(QString("http://florian:Apfelkuchen12@aristoteles.serveftp.org/calendar/icalclient.php")));
}

void Calendar::initNetwork()
{
	m_http.setProxy("proxy.bmlv.gv.at", 3128, "", "");
}

void Calendar::showEventInfo(int row, int col)
{
	TEvent evt = parser->m_events.value(row);
	qDebug() << evt.toString();
}

void Calendar::showTodoInfo(int row, int col)
{
	TTodo todo = parser->m_todos.value(row);
	qDebug() << todo.toString();
}
