#include "mainwindow.h"
#include <QApplication>
#include <controller.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Controller c(220000000, 110075314176, &a); // TODO: I'm not sure yet if it should be 110075314176 or 110075314175 (the exclusive/inclusive part).
    Controller c(10, 100, &a);

    MainWindow w(c);
    w.show();

    return a.exec();
}
