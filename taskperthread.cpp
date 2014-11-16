#include "taskperthread.h"

TaskPerThread::TaskPerThread(qint64 n, const int nOffset, qint64 minInclusive, qint64 maxExclusive) :
    n(n),
    nOffset(nOffset),
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

qint64 TaskPerThread::getN() const
{
    return n;
}

int TaskPerThread::getNOffset() const
{
    return nOffset;
}

qint64 TaskPerThread::getMinInclusive() const
{
    return minInclusive;
}

qint64 TaskPerThread::getMaxExclusive() const
{
    return maxExclusive;
}
