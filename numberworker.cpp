/*
 * Copyright (C) 2018  Wiebe Cazemier <wiebe@halfgaar.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * https://www.gnu.org/licenses/gpl-2.0.html
 */

#include "numberworker.h"
#include <QThread>
#include <QDebug>
#include <QDateTime>

int NumberWorker::globalThreadCounter = 0;

NumberWorker::NumberWorker(const TaskPerThread task, QThread &thread, qint64 *totalResultList, const qint64 n, qint64 randSeed) :
    QObject(0), // We can't have a parent, because then we can't move to a thread.
    n(task.getN()),
    nOffset(task.getNOffset()),
    minInclusive(task.getMinInclusive()),
    maxExclusive(task.getMaxExclusive()),
    mCancelled(false),
    mTotalResultList(totalResultList),
    mN(n)
{
    if (maxExclusive < n)
    {
        QString message = "There are more elements in the array then there are numbers available.";
        qDebug() << message;
        emit error(message);
    }

    moveToThread(&thread);
    mThreadID = globalThreadCounter++;
    x = randSeed;
}

void NumberWorker::doWork()
{
    // merely for the progress signals
    const int period = 10000;
    const qint64 nStart = n;

    for (qint64 i = maxExclusive; i > minInclusive && !mCancelled; i--)
    {
        // This is a well known linear congruential function for random number generation.
        // Doing it locally, to avoid slow function calls and even slower mutexes. This does mean the seed value needs to be different
        // per thread.
        x = 48271 * x;
        const qint64 random = x % (i - minInclusive);

        const qint64 candidateValue = maxExclusive - i + minInclusive;

        if (random < n)
        {
            n--;
            // the + part is necessary because all threads are writing their portion in the same result.
            mTotalResultList[n+nOffset] = candidateValue;

            if (n % period == 0)
            {
                int percentDone = (nStart - n) / ((double)nStart) * 100;
                emit progress(percentDone);
            }
        }
    }

    if (mCancelled)
        return;

    if (n != 0)
    {
        QString message = QString("n = %1, which is not 0, so the algorithm has a bug.").arg(n);
        qDebug() << message;
        emit error(message);
        return;
    }

    emit resultReady();
}

void NumberWorker::cancel()
{
    mCancelled = true;
}

int NumberWorker::getThreadID() const
{
    return mThreadID;
}

