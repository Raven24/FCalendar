#include <QtGui/QApplication>
#include "calendar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	a.setApplicationName("FCalendar");
	a.setOrganizationName("FCalendar");
    Calendar w;
#ifdef Q_OS_SYMBIAN
	w.showMaximized();
#else
	w.show();
#endif
    return a.exec();
}
