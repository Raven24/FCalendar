#include <QtGui/QApplication>
#include "calendar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	a.setApplicationName("FCalendar");
	a.setOrganizationName("FCalendar");
    Calendar w;
	QString style = "* {"
					"	color: #222;"
					"}"

					"Calendar {"
					"	background-color: #FEFEFE;"
					"	color: #111;"
					"}"

					"StatusIndicator {"
					"	margin: 0;"
					"	padding: 0;"
					"}"

					"StatusIndicator QLabel {"
					"	color: #111;"
					"}"

					"ContextMenu {"
					"	background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #BBB, stop: 1 #888);"
					"}"

					"ContextMenu QPushButton {"
					"    border: none;"
					"    border-radius: 3px;"
					"    padding: 5px;"
					"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #888, stop: 1 #BBB);"
					"}"

					"ContextMenu QPushButton:default {"
					"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #333, stop: 1 #BBB);"
					"}"

					"EventTableView QHeaderView {"
					"	padding: 0;"
					"	margin: 0;"
					"}"

					"EventTableView QHeaderView::section {"
					"	font-size: 9px;"
					"	font-weight: bold;"
					"	color: #EEE;"
					"	background-color: #888;"
					"	padding: 4px;"
					"	border: none;"
					"	border-bottom: 1px solid #AAA;"
					"}"

					"EventTableView {"
					"    gridline-color: #EEE;"
					"    color: #222;"
					"}"

					"EventTableView::item {"
					"    background-color: #FFF;"
					"}"

					"EventTableView::item:alternate {"
					"    background-color: #EEE;"
					"}"

					"EventTableView::item:hover {"
					"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);"
					"    background-color: #f2f7ff;"
					"    border: 1px solid #bfcde4;"
					"}"

					"EventTableView::item:selected:active{"
					"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #d9e2f1, stop: 1 #c3d1e6);"
					"}";
        a.setStyleSheet(style);

#ifdef Q_OS_SYMBIAN
	w.showFullScreen();
	//w.showMaximized();
#else
	w.show();
#endif
    return a.exec();
}
