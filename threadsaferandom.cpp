#include "threadsaferandom.h"
#include <QDateTime>

ThreadSafeRandom::ThreadSafeRandom()
{
    mMutex.lock(); // Not really necessary, because you're only supposed to instantiate this class once.
    x = QDateTime::currentDateTime().toMSecsSinceEpoch();
    mMutex.unlock();
}

/**
 * Simple linear congruential function, as found in the art of computer programming volume 2 (TODO: expand documentation)
 */
qint64 ThreadSafeRandom::next()
{
    mMutex.lock();
    x = 48271 * x;
    mMutex.unlock();
    return x;
}
