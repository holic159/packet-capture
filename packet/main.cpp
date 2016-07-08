#include "mainwindow.h"
#include <QApplication>

MainWindow *indexWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    indexWindow = new MainWindow();
    indexWindow -> show();
    return a.exec();
}
