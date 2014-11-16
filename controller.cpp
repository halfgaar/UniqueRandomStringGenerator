#include "controller.h"
#include <QDebug>
#include <taskperthread.h>

QList<TaskPerThread> Controller::getTaskDivisions(const qint64 n, const qint64 maxExclusive)
{
    QList<TaskPerThread> result;

    const qint64 nPerThread = n / mNoOfThreads;
    const qint64 nRemainder = n % mNoOfThreads;

    const qint64 segmentSize = maxExclusive / mNoOfThreads;
    const qint64 segmentRemainder = maxExclusive % mNoOfThreads;

    for (int i = 0; i < mNoOfThreads; ++i)
    {
        qint64 min = segmentSize * i;
        qint64 max = min + segmentSize;
        TaskPerThread task(nPerThread, min, max);
        result.append(task);
    }

    result.last().appendN(nRemainder);
    result.last().appendMax(segmentRemainder);

    return result;
}

Controller::Controller(const qint64 n, const qint64 maxExclusive, QObject *parent) :
    QObject(parent),
    mNoOfThreads(QThread::idealThreadCount ()),
    mRunning(false)
{
    qRegisterMetaType<QSharedPointer<QVector<qint64> > >("QSharedPointer<QVector<qint64> >");

    foreach(TaskPerThread task, getTaskDivisions(n, maxExclusive))
    {
        QThread * thread = new QThread(this);
        mThreads.append(thread);
        NumberWorker * worker = new NumberWorker(task, *thread);
        mWorkers.append(worker);

        connect(this, &Controller::operate, worker, &NumberWorker::doWork);
        connect(worker, &NumberWorker::resultReady, this, &Controller::handleWorkerResults);
        connect(worker, &NumberWorker::error, this, &Controller::error);
        thread->start();
    }
}

Controller::~Controller()
{
    cancel();

    foreach (QThread *thread, mThreads)
    {
        thread->quit();
        thread->wait();
    }

    foreach (NumberWorker *worker, mWorkers)
    {
        // We could use delete later, but that used to require an event loop, which we no longer have because we quit the thread. However,
        // I think since qt 4.8, that also works without event loop. But, since no queued connections are anything of the sort are
        // active anymore, we can just delete it now.
        delete worker;
    }
}

void Controller::start()
{
    if (mRunning)
        return;

    mRunning = true;
    emit operate(); // Not calling stuff directly on the worker because it's been moved to another thread. Instead using this queued connection.
    emit started();
}

int Controller::getNrOfThreads()
{
    return mNoOfThreads;
}

QList<NumberWorker *> Controller::getWorkers()
{
    return mWorkers;
}

void Controller::cancel()
{
    foreach (NumberWorker *worker, mWorkers)
    {
        worker->cancel();
    }

    emit stopped();
    mRunning = false;
}

bool Controller::isRunning() const
{
    return mRunning;
}

void Controller::handleWorkerResults(QSharedPointer<QVector<qint64> > result)
{
    qDebug() << "Worker done. It returned " << result->count() << "numbers";

    emit stopped();
    mRunning = false;
}



