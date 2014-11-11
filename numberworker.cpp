#include "numberworker.h"
#include <QThread>
#include <QDebug>
#include <QDateTime>


NumberWorker::NumberWorker(qint64 n, qint64 minInclusive, qint64 maxExclusive, QObject *parent) :
    QObject(parent),
    n(n),
    minInclusive(minInclusive),
    maxExclusive(maxExclusive)
{
    if (maxExclusive < n)
    {
        QString message = "There are more elements in the array then there are numbers available.";
        qDebug() << message;
        emit error(message);
    }
}

void NumberWorker::doWork()
{
    // Seed the local random generator.
    unsigned long x = QDateTime::currentDateTime().toMSecsSinceEpoch();;

    QVector<qint64> *result = new QVector<qint64>(n);
    QSharedPointer<QVector<qint64> > managedPointer = QSharedPointer<QVector<qint64> >(result);

    // merely for the progress signals
    const int period = 10000;
    const qint64 nStart = n;

    for (qint64 i = maxExclusive; i > minInclusive; i--)
    {
        // This is a well known linear congruential function for random number generation.
        // Doing it locally, to avoid slow function calls. It makes it marginally faster.
        x = 48271 * x;
        const qint64 random = x % (i - minInclusive);

        const qint64 candidateValue = maxExclusive - i;

        if (random < n)
        {
            n--;
            (*result)[n] = candidateValue;

            if (n % period == 0)
            {
                int percentDone = (nStart - n) / ((double)nStart) * 100;
                emit progress(percentDone);
            }
        }
    }

    if (n != 0)
    {
        QString message = QString("n = %1, which is not 0, so the algorithm has a bug.").arg(n);
        qDebug() << message;
        emit error(message);
        return;
    }

    emit resultReady(managedPointer);
}

