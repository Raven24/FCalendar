#include <QtGui>

#include "eventdelegate.h"
#include "eventmodel.h"

EventDelegate::EventDelegate(QObject *parent)
		: QAbstractItemDelegate(parent)
{
}

void EventDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if (option.state & QStyle::State_Selected)
		painter->fillRect(option.rect, option.palette.highlight());

	painter->save();
	painter->setRenderHint(QPainter::Antialiasing, true);

	QColor c	= option.palette.text().color();
//	int role	= EventModel::RoleSummary;
	QRect basicRect = QRect(QPoint(option.rect.x(), option.rect.y()),
							QSize(option.rect.width()-2, 12));

	if (option.state & QStyle::State_Selected) {
		c = option.palette.highlightedText().color();
	}

	painter->setPen(c);
	QFont font = painter->font();

	switch(index.column()) {
		case 0:
			font.setBold(true);
			font.setPixelSize(10);
			painter->setFont(font);
			painter->drawText(basicRect, Qt::AlignLeft, index.model()->data(index, EventModel::RoleSummary).toString());
			if (option.state & QStyle::State_Selected) {
				font.setBold(false);
				painter->setFont(font);
				basicRect.moveTop(basicRect.y()+14);
				painter->drawText(basicRect, Qt::AlignLeft, index.model()->data(index, EventModel::RoleLocation).toString());
			}
			font.setBold(false);
			font.setPixelSize(8.5);
			c.setAlphaF(0.75);
			painter->setPen(c);
			painter->setFont(font);
			basicRect.moveTop(basicRect.y()+16);
			painter->drawText(basicRect, Qt::AlignRight, index.model()->data(index, EventModel::RoleDate).toString());
			break;
		case 1:
			font.setPixelSize(10);
			painter->setFont(font);
			painter->drawText(QRect(QPoint(option.rect.x(), option.rect.y()), QSize(option.rect.width()-2, 18)), Qt::AlignRight | Qt::AlignVCenter, index.model()->data(index, EventModel::RoleRemaining).toString());
	}

	painter->restore();

}

QSize EventDelegate::sizeHint(const QStyleOptionViewItem & option,
							   const QModelIndex & index) const
{
	//qDebug() << "index: " << index.row() << " - " << option.state;

	switch(index.column()) {
		case 0:
			if(option.state & QStyle::State_Selected) {
				return QSize(160, 42);
			}
			return QSize(160, 28);
		case 1:
			if(option.state & QStyle::State_Selected) {
				return QSize(70, 42);
			}
			return QSize(70, 28);
	}
	return QSize();
}
