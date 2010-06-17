#include <QtGui/QApplication>
#include "calendar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	a.setApplicationName("FCalendar");
	a.setOrganizationName("FCalendar");
    Calendar w;
	QString style = "EventTableView{"
					"	alternate-background-color: #EEEEEE;"
					"	gridline-color: #EEEEEE;"
					"}"
					"EventTableView::item {"
					"}"

					"EventTableView::item:hover {"
					"	background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);"
					"	border: 1px solid #bfcde4;"
					"}"

					"EventTableView::item:selected {"
					"	border: 1px solid #567dbc;"
					"}"

					"EventTableView::item:selected:active{"
					"	background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc);"
					"}"

					"EventTableView::item:selected:!active {"
					"	background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6b9be8, stop: 1 #577fbf);"
					"}";
	a.setStyleSheet(style);

#ifdef Q_OS_SYMBIAN
	w.showMaximized();
#else
	w.show();
#endif
    return a.exec();
}
