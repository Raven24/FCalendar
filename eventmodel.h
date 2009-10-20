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
	static const int RoleSummary;
	static const int RoleDate;
	static const int RoleRemaining;

	EventModel(QObject *parent = 0);
	void fetchData(VCalParser *parser);

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
	QList<TEvent> modelData;
};

#endif // EVENTMODEL_H
