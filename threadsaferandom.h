#ifndef THREADSAFERANDOM_H
#define THREADSAFERANDOM_H

#include <QMutex>

class ThreadSafeRandom
{
    QMutex mMutex;
    qint64 x;
public:
    ThreadSafeRandom();
    qint64 next();
};

#endif // THREADSAFERANDOM_H
