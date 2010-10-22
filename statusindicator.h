#ifndef STATUSINDICATOR_H
#define STATUSINDICATOR_H

#include <QtGui>

class StatusIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit StatusIndicator(QWidget *parent = 0);

signals:

public slots:
	void toggleIndicator();
	void showIndicator();
	void hideIndicator();
	void setTitle(const QString _title);
	void updateProgress(const int _val, const int _max);

protected:
	QProgressBar *progress;
	QLabel *working, *title;
	QStackedLayout *stackLayout;

};

#endif // STATUSINDICATOR_H
