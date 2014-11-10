#include "numberworker.h"
#include <QThread>
#include <QDebug>

NumberWorker::NumberWorker(QObject *parent) :
    QObject(parent)
{
}

void NumberWorker::doWork()
{
    int i = 0;

    while(i < 10)
    {
        QThread::msleep(200);
        emit progress(i++);
    }
}

