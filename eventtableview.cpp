#include <QtGui>

#include "eventtableview.h"

EventTableView::EventTableView()
{
}

QModelIndex EventTableView::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) 
{
	QModelIndex tmpIndex = QTableView::moveCursor(cursorAction, modifiers);
	emit cursorChanged(tmpIndex);
	return tmpIndex;
}
