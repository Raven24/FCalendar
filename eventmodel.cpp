#include <QtGui>

#include "eventmodel.h"
#include "vcalparser.h"
#include "tevent.h"

const int EventModel::RoleSummary	= 1;
const int EventModel::RoleDate		= 2;
const int EventModel::RoleRemaining	= 3;

EventModel::EventModel(QObject *parent)
		: QAbstractItemModel(parent)
{
}

void EventModel::fetchData(VCalParser parser)
{
	modelData = parser.m_events;
//	emit dataChanged();
}

int EventModel::rowCount(const QModelIndex & /* parent */) const
{
	return 2;
}

int EventModel::columnCount(const QModelIndex & /* parent */) const
{
	return modelData.count();
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
		default:
			return QVariant();
	}
}

QVariant EventModel::headerData(int section, Qt::Orientation /* orientation */, int /* role */) const
{
	switch(section) {
		case 0:
			return QString("Name");
		case 1:
			return QString("Time");
		default:
			return QVariant();
	}
}
