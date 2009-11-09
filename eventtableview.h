#ifndef EVENTTABLEVIEW_H
#define EVENTTABLEVIEW_H

#include <QTableView>
#include <QModelIndex>

class EventTableView : public QTableView
{
	Q_OBJECT
	
public:
    EventTableView();
	
signals:
	void cursorChanged(QModelIndex index);
	
protected:
	QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers);
};

#endif // EVENTTABLEVIEW_H
