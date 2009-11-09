#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include <QtGui>
#include "tevent.h"

class TEvent;
class VCalParser;

class EventModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	EventModel(QObject *parent = 0);
	void fetchData(VCalParser *parser);

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	enum DisplayRole {
		RoleSummary		= 0x00000001,
		RoleDate		= 0x00000002,
		RoleRemaining	= 0x00000004,
		RoleLocation	= 0x00000008
	};
	Q_DECLARE_FLAGS(DisplayRoles, DisplayRole)
private:
	QList<TEvent> modelData;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(EventModel::DisplayRoles)

#endif // EVENTMODEL_H
