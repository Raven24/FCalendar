#include <QtGui/QApplication>
#include "calendar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calendar w;
#ifdef Q_OS_SYMBIAN
	w.showFullScreen();
	qt_SetDefaultIap();
#else
	w.show();
#endif
    return a.exec();
}
