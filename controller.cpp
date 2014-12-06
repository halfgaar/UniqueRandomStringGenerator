#include "controller.h"
#include <QDebug>
#include <taskperthread.h>

/**
 * @brief Controller::getTaskDivisions generates a list of ranges for each thread to work on.
 * @param n is the amount of numbers to pick
 * @param maxExclusive is the exclusive upper limit,
 * @return
 *
 * Note: as it is now, the list has an aesthetic/cosmetic Endian-like issue. The algorithm works backwards, but the segments are
 * distributed forwards. This is hard-ish to solve because the last thread gets the remainder from an uneven division, making it hard
 * to inverse the nOffset.
 *
 * So, this is an example list (for the trained eye; yes, with random seeding issue):
 *
 * 24 -> created by thread 1
 * 14 -> created by thread 1.
 * 49 -> created by thread 2.
 * 39 -> created by thread 2.
 * 74 -> created by thread 3.
 * 64 -> created by thread 3.
 * 99 -> created by thread 4.
 * 93 -> created by thread 4.
 * 89 -> created by thread 4.
 * 79 -> created by thread 4.
 *
 * If you were to sort descending by thread number but keep the order per thread, you get the order as a single thread version
 * of the algorithm would have created. In other words, a list of unique descending values.
 */
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
        TaskPerThread task(nPerThread, i*nPerThread, min, max);
        result.append(task);
    }

    result.last().appendN(nRemainder);
    result.last().appendMax(segmentRemainder);

    return result;
}

bool Controller::verifyUniqueness()
{
    qint64 lastOne = -1;
    qint64 counter = 0;
    const qint64 total = mResultList.length();

    foreach(const qint64 value, mResultList)
    {
        if (lastOne == value)
        {
            emit error(QString("%1 was encountered twice.").arg(value));
            return false;
        }

        lastOne = value;

        ++counter;

        int progress = (counter / (double)total) * 100;
        emit verifyProgress(progress);
    }

    return true;
}

void Controller::shuffle()
{

}

Controller::Controller(const qint64 n, const qint64 maxExclusive, QObject *parent) :
    QObject(parent),
    mNoOfThreads(QThread::idealThreadCount ()),
    mRunning(false),
    mResultList(n),
    mWorkersDone(0)
{
    qRegisterMetaType<QSharedPointer<QVector<qint64> > >("QSharedPointer<QVector<qint64> >");

    foreach(TaskPerThread task, getTaskDivisions(n, maxExclusive))
    {
        QThread * thread = new QThread(this);
        mThreads.append(thread);
        NumberWorker * worker = new NumberWorker(task, *thread, mResultList, mTsRandom.next());
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
    mWorkersDone = 0;
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

    mWorkersDone = 0;
    mRunning = false;
    emit stopped(false);
}

bool Controller::isRunning() const
{
    return mRunning;
}

void Controller::handleWorkerResults()
{
    mWorkersDone++;

    if (mWorkersDone == mNoOfThreads)
    {
        // TODO: Hmm, how am I going to emit progress events for this?
        emit sortProgress(0);
        std::sort(mResultList.begin(), mResultList.end());
        emit sortProgress(100);

        if (verifyUniqueness())
        {
            mRunning = false;
            emit stopped(false);
        }
        else
        {
            mRunning = false;
            emit stopped(true);
        }

        shuffle();
    }
}



