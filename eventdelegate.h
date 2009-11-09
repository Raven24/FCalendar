#ifndef EVENTDELEGATE_H
#define EVENTDELEGATE_H

#include <QtGui>

class EventDelegate : public QAbstractItemDelegate
{
		Q_OBJECT

public:
	EventDelegate(QObject *parent = 0);

	void paint(QPainter *painter, const QStyleOptionViewItem &option,
				const QModelIndex &index) const;

	QSize sizeHint(const QStyleOptionViewItem &option,
					const QModelIndex &index ) const;

};

#endif // EVENTDELEGATE_H
