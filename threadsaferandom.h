#ifndef THREADSAFERANDOM_H
#define THREADSAFERANDOM_H

#include <QMutex>

class ThreadSafeRandom
{
    QMutex mMutex;
    quint64 x;
public:
    ThreadSafeRandom();
    quint64 threadSafeNext();
    quint64 threadUnsafeNext(quint64 maxExclusive);
};

#endif // THREADSAFERANDOM_H
