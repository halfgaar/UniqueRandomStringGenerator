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
