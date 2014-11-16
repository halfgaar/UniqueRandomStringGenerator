#include "controller.h"
#include <QDebug>

TaskPerThread::TaskPerThread(qint64 n, qint64 minInclusive, qint64 maxExclusive) :
    n(n),
    minInclusive(minInclusive),
    maxExclusive(maxExclusive)
{

}

void TaskPerThread::appendN(qint64 n)
{
    this->n += n;
}

void TaskPerThread::appendMax(qint64 maxExlusive)
{
    this->maxExclusive += maxExlusive;
}

qint64 TaskPerThread::getN()
{
    return n;
}

qint64 TaskPerThread::getMinInclusive()
{
    return minInclusive;
}

qint64 TaskPerThread::getMaxExclusive()
{
    return maxExclusive;
}

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
    mNoOfThreads(QThread::idealThreadCount ())
{
    qRegisterMetaType<QSharedPointer<QVector<qint64> > >("QSharedPointer<QVector<qint64> >");

    foreach(TaskPerThread task, getTaskDivisions(n, maxExclusive))
    {
        NumberWorker * worker = new NumberWorker(task.getN(), task.getMinInclusive(), task.getMaxExclusive());
        QThread * thread = new QThread(this);
        worker->moveToThread(thread);

        connect(this, &Controller::operate, worker, &NumberWorker::doWork);
        connect(worker, &NumberWorker::resultReady, this, &Controller::handleWorkerResults);
        connect(worker, &NumberWorker::error, this, &Controller::error);
        thread->start();

        mWorkers.append(worker);
        mThreads.append(thread);
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

void Controller::cancel()
{
    foreach (NumberWorker *worker, mWorkers)
    {
        worker->cancel();
    }
}

void Controller::handleWorkerResults(QSharedPointer<QVector<qint64> > result)
{
    qDebug() << "Worker done. It returned " << result->count() << "numbers";
}



