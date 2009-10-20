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

	QColor c = option.palette.text().color();
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
			painter->drawText(QRect(QPoint(option.rect.x()+2, option.rect.y()), QSize(option.rect.width()-2, 12)), Qt::AlignLeft, index.model()->data(index, EventModel::RoleSummary).toString());
			font.setBold(false);
			font.setPixelSize(8);
			c.setAlphaF(0.75);
			painter->setPen(c);
			painter->setFont(font);
			painter->drawText(QRect(QPoint(option.rect.x(), option.rect.y()+17), QSize(option.rect.width()-2, 10)), Qt::AlignRight, index.model()->data(index, EventModel::RoleDate).toString());
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
	switch(index.column()) {
		case 0:
			if(option.state ^ QStyle::State_Enabled) {
				return QSize(160, 50);
			}
			return QSize(160, 28);
		case 1: return QSize(70, 22);
	}
	return QSize();
}
