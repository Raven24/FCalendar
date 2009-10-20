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
	painter->setPen(Qt::NoPen);
	if (option.state & QStyle::State_Selected)
		 painter->setBrush(option.palette.highlightedText());
	else
		painter->setBrush(QBrush(Qt::black));

	QFont font = painter->font();

	switch(index.column()) {
		case 0:
			font.setBold(true);
			font.setPixelSize(10);
			painter->setFont(font);
			painter->drawText(QRect(QPoint(0, 0), QSize(200, 10)), Qt::AlignLeft, index.model()->data(index, EventModel::RoleSummary).toString());
			font.setBold(false);
			font.setPixelSize(8);
			painter->setFont(font);
			painter->drawText(QRect(QPoint(0, 10), QSize(200, 8)), Qt::AlignRight, index.model()->data(index, EventModel::RoleDate).toString());
			break;
		case 1:
			font.setPixelSize(10);
			painter->setFont(font);
			painter->drawText(QRect(QPoint(0, 0), QSize(100, 18)), Qt::AlignRight | Qt::AlignVCenter, index.model()->data(index, EventModel::RoleRemaining).toString());
	}

	painter->restore();

}

QSize EventDelegate::sizeHint(const QStyleOptionViewItem & /* option */,
							   const QModelIndex & index) const
{
	switch(index.column()) {
		case 0:
			return QSize(200, 18);
		case 1:
			return QSize(100, 18);
	}
	return QSize();
}
