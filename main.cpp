#include <QtGui/QApplication>
#include "calendar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calendar w;
	w.show();
    return a.exec();
}
