#include "mainwindow.h"
#include <QApplication>
#include <controller.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller c(&a);

    MainWindow w(c);
    w.show();

    return a.exec();
}
