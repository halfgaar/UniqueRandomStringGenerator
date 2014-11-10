#include "controller.h"
#include <QDebug>

Controller::Controller(QObject *parent) :
    QObject(parent),
    mNoOfThreads(QThread::idealThreadCount ())
{
    for (int i = 0; i < mNoOfThreads; ++i)
    {
        NumberWorker * worker = new NumberWorker();
        QThread * thread = new QThread(this);
        worker->moveToThread(thread);

        connect(this, &Controller::operate, worker, &NumberWorker::doWork);
        connect(worker, &NumberWorker::resultReady, this, &Controller::handleWorkerResults);
        thread->start();

        mWorkers.append(worker);
        mThreads.append(thread);
    }
}

Controller::~Controller()
{
    foreach (QThread *thread, mThreads)
    {
        thread->quit();
        thread->wait();
    }

    foreach (NumberWorker *worker, mWorkers)
    {
        delete worker;
    }
}

void Controller::start()
{
    emit operate(); // Not calling stuff directly on the worker because it's been moved to another thread. Instead using this queued connection.
}

int Controller::getNrOfThreads()
{
    return mNoOfThreads;
}

QList<NumberWorker *> Controller::getWorkers()
{
    return mWorkers;
}

void Controller::handleWorkerResults(QVector<int> result)
{
    qDebug() << "worker returned " << result.count() << "numbers";
}
