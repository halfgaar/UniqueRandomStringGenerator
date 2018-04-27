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
quint64 ThreadSafeRandom::threadSafeNext()
{
    mMutex.lock();
    x = 48271 * x;
    mMutex.unlock();
    return x;
}

quint64 ThreadSafeRandom::threadUnsafeNext(quint64 maxExclusive)
{
    x = 48271 * x;
    return x % maxExclusive;
}
