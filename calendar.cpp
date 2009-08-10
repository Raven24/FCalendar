#include "calendar.h"
#include "task.h"
#include "tevent.h"
#include "ttodo.h"
#include "vcalparser.h"

#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QHttp>
#include <QDebug>

Calendar::Calendar(QWidget *parent)
	: QMainWindow(parent)
{
	m_list = new QTableWidget(0, 2);

	m_list->setSelectionMode(QAbstractItemView::SingleSelection);
	m_list->setSelectionBehavior(QAbstractItemView::SelectRows);

	QStringList listLabels;

	// headers
	listLabels << tr("Name") << tr("Time");
	m_list->setHorizontalHeaderLabels(listLabels);
	m_list->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	m_list->verticalHeader()->hide();

	//initNetwork();
	getData();

	setCentralWidget(m_list);
}

Calendar::~Calendar()
{
}

void Calendar::populateList()
{
	qDebug() << "Bytes available: " << m_http.bytesAvailable();

	QString response(m_http.readAll());

	//qDebug() << response;

	VCalParser *parser = new VCalParser(response);
	//QList items = new QAppointment::readVCalendarData(response, response.length());

	for (int i = 0; i < parser->m_events.size(); i++) {

		TEvent event = parser->m_events.at(i);

		QTableWidgetItem *item1 = new QTableWidgetItem(event.getDescription(), 0);
		QTableWidgetItem *item2 = new QTableWidgetItem(event.getRemaining(), 0);

		int row = m_list->rowCount();
		m_list->insertRow(row);

		m_list->setItem(row, 0, item1);
		m_list->setItem(row, 1, item2);

	}
}

void Calendar::getData()
{
	m_http.setHost("aristoteles.serveftp.org");
	m_http.setUser("florian", "Apfelkuchen12");

	qDebug() << "fetching data...";

	m_http.get("/calendar/icalclient.php");
	connect(&m_http, SIGNAL(done(bool)), this, SLOT(populateList()));
}

void Calendar::initNetwork()
{
	m_http.setProxy("proxy.bmlv.gv.at", 3128, "", "");
}
