#include <QtGui/QApplication>
#include "calendar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	a.setApplicationName("FCalendar");
	a.setOrganizationName("FCalendar");
    Calendar w;
	QString style = "Calendar {"
					"	background-color: #FEFEFE;"
					"   color: #111111;"
					"}"

					"StatusIndicator {"
					"	margin: 0;"
					"	padding: 0;"
					"}"

					"StatusIndicator QLabel {"
					"	color: #111111;"
					"}"

					"EventTableView{"
					"	gridline-color: #EEEEEE;"
					"	color: #222222;"
					"}"

					"EventTableView::item {"
					"	background-color: #FFFFFF;"
					"}"

					"EventTableView::item:alternate {"
					"	background-color: #EEEEEE;"
					"}"

					"EventTableView::item:hover {"
					"	background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);"
					"	background-color: #f2f7ff;"
					"	border: 1px solid #bfcde4;"
					"}"

					"EventTableView::item:selected:active{"
					"	background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #d9e2f1, stop: 1 #c3d1e6);"
					"}";
	a.setStyleSheet(style);

#ifdef Q_OS_SYMBIAN
	w.showFullScreen();
#else
	w.show();
#endif
    return a.exec();
}
