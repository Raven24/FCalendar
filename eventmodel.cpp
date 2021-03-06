#include <QtGui>

#include "eventmodel.h"
#include "vcalparser.h"
#include "tevent.h"

EventModel::EventModel(QObject *parent)
		: QAbstractTableModel(parent)
{
}

void EventModel::fetchData(VCalParser *parser)
{
	modelData = parser->m_events;
	reset();
    qDebug() << "[info] there are" << modelData.size() << "events";
}

int EventModel::rowCount(const QModelIndex & /* parent */) const
{
	return modelData.count();
}

int EventModel::columnCount(const QModelIndex & /* parent */) const
{
	return 2;
}

QVariant EventModel::data(const QModelIndex &index, int role) const
{
	if(!index.isValid())
		return QVariant();

	TEvent event = modelData.at(index.row());
	switch(role) {
		case RoleSummary:
			return event.getSummary();
		case RoleDate:
			return event.getStartString();
		case RoleRemaining:
			return event.getRemaining();
		case RoleLocation:
			return event.getLocation();
		default:
			return QVariant();
	}
}

QVariant EventModel::headerData(int section, Qt::Orientation /* orientation */, int role) const
{
	if (role == Qt::SizeHintRole) {
		//qDebug() << "header data - size hint ";
		switch(section) {
			case 0: return QSize(100, 18);
			case 1: return QSize(60, 18);
		}
	 }
	//qDebug() << "header data requested: \n\tsection: " << section << "\n\trole: " << role;
	switch(section) {
		case 0: return QString("Event");
		case 1: return QString("Time");
		default: return QVariant();

	}
}
