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
