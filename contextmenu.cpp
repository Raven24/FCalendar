#include "contextmenu.h"

ContextMenu::ContextMenu(QWidget *parent) :
    QDialog(parent)
{
        setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
        setAutoFillBackground(true);

	calendar	= new QPushButton();
	network		= new QPushButton();
	settings	= new QPushButton();
	quit		= new QPushButton();

	calendar->setIcon(QIcon(":calendar.png"));
	calendar->setToolTip(tr("Calendar"));

	network->setIcon(QIcon(":network.png"));
	network->setToolTip(tr("Network"));

	settings->setIcon(QIcon(":settings.png"));
	settings->setToolTip(tr("Settings"));

	quit->setIcon(QIcon(":quit.png"));
	quit->setToolTip(tr("Quit"));

	connect(calendar, SIGNAL(clicked()),
			this, SIGNAL(requestCalendar()));
	connect(network, SIGNAL(clicked()),
			this, SIGNAL(requestNetwork()));
	connect(settings, SIGNAL(clicked()),
			this, SIGNAL(requestSettings()));
	connect(quit, SIGNAL(clicked()),
			this, SIGNAL(requestQuit()));

	connect(calendar, SIGNAL(clicked()),
			this, SLOT(hide()));
	connect(network, SIGNAL(clicked()),
			this, SLOT(hide()));
	connect(settings, SIGNAL(clicked()),
			this, SLOT(hide()));

	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(calendar);
	layout->addWidget(network);
	layout->addWidget(settings);
	layout->addWidget(quit);

	setModal(true);
        setBackgroundRole(QPalette::Window);
	setLayout(layout);
}

void ContextMenu::show() {

    if(!isHidden()) {
        hide();
        return;
    }
	//qDebug() << "[debug] parent: " << parentWidget()->size();
	//qDebug() << "[debug] pos: " << pos();

	//resize(QSize(parentWidget()->size().width(), 32));
	//move(0, parentWidget()->size().height()-32);

	QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
	animation->setDuration(170);
	animation->setStartValue(QRect(0, parentWidget()->size().height(), parentWidget()->size().width(), 0));
	animation->setEndValue(QRect(0, parentWidget()->size().height()-42, parentWidget()->size().width(), 42));

	animation->start();

	QDialog::show();

	calendar->setFocus();
	calendar->setDefault(true);

}

void ContextMenu::hide()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(150);
    animation->setStartValue(QRect(0, parentWidget()->size().height()-42, parentWidget()->size().width(), 42));
    animation->setEndValue(QRect(0, parentWidget()->size().height(), parentWidget()->size().width(), 0));

    connect(animation, SIGNAL(finished()),
            this, SLOT(privHide()));

    animation->start();
}

void ContextMenu::privHide()
{
    QDialog::hide();
}
