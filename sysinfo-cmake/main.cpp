#include "SysInfoMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    // handle input, event loop, etc.
    QApplication a(argc, argv);
    SysInfoMainWindow w;

    w.show();

    // trigger the event loop
    return a.exec();
}
