#ifndef TASKPERTHREAD_H
#define TASKPERTHREAD_H

#include <qglobal.h>

class TaskPerThread
{
public:
    explicit TaskPerThread(qint64 n, const int nOffset, qint64 minInclusive, qint64 maxExclusive);
    void appendN(qint64 n);
    void appendMax(qint64 maxExlusive);

    qint64 getN() const;
    int getNOffset() const;
    qint64 getMinInclusive() const;
    qint64 getMaxExclusive() const;

private:
    qint64 n;
    int nOffset;
    qint64 minInclusive;
    qint64 maxExclusive;
};

#endif // TASKPERTHREAD_H
