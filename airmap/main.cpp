#include <QApplication>

#include "ammainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    AMMainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
