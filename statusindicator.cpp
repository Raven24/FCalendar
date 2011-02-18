#include "statusindicator.h"

StatusIndicator::StatusIndicator(QWidget *parent) :
    QWidget(parent)
{
	progress = new QProgressBar();
	working = new QLabel();
	title = new QLabel();

	progress->hide();
	working->hide();
	title->setText(tr("change me"));

	QMovie *mov = new QMovie(this);
	mov->setCacheMode(QMovie::CacheAll);
	working->setMovie(mov);
	mov->setFileName(":loading.gif");
	mov->start();

	stackLayout = new QStackedLayout();
	stackLayout->addWidget(title);
	stackLayout->addWidget(progress);

	QHBoxLayout *layout = new QHBoxLayout();
        layout->setMargin(0);
	layout->addLayout(stackLayout);
	layout->addWidget(working);

	setLayout(layout);
}

void StatusIndicator::toggleIndicator()
{
	if(working->isVisible()) {
		working->hide();
	} else {
		working->show();
	}
}

void StatusIndicator::showIndicator()
{
	working->show();
}

void StatusIndicator::hideIndicator()
{
	working->hide();
}

void StatusIndicator::setTitle(const QString _title)
{
	QString text(_title);
	text.prepend("<b>").append("</b>");
	title->setText(text);
	stackLayout->setCurrentWidget(title);
}

void StatusIndicator::updateProgress(const int _val, const int _max)
{
	stackLayout->setCurrentWidget(progress);
	progress->setMaximum(_max);
	progress->setValue(_val);

	if(_val == _max) {
		stackLayout->setCurrentWidget(title);
	}
}
