#include <QApplication>
#include <QStyleFactory>

#include "ammainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    QApplication::setStyle(QStyleFactory::create("fusion"));
    AMMainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
