#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QtGui>

class ContextMenu : public QDialog
{
    Q_OBJECT
public:
    explicit ContextMenu(QWidget *parent = 0);

signals:
	void requestSettings();
	void requestNetwork();
	void requestCalendar();
	void requestQuit();

public slots:
	void show();
        void hide();

protected:
	QPushButton *calendar, *network, *settings, *quit;

private slots:
        void privHide();
};

#endif // CONTEXTMENU_H
