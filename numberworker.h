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

#ifndef NUMBERWORKER_H
#define NUMBERWORKER_H

#include <QObject>
#include <QVector>
#include <QSharedPointer>
#include <taskperthread.h>
#include <QThread>

class NumberWorker : public QObject
{
    Q_OBJECT

    qint64 n;
    const int nOffset;
    const qint64 minInclusive;
    const qint64 maxExclusive;
    bool mCancelled;
    static int globalThreadCounter;
    int mThreadID;
    qint64 * mTotalResultList;
    const qint64 mN;
    quint64 x;
public:
    explicit NumberWorker(const TaskPerThread task, QThread &thread, qint64 * totalResultList, const qint64 n, qint64 randSeed);
    void cancel();
    int getThreadID() const;

public slots:
    void doWork();

signals:
    void progress(int value);
    void resultReady();
    void error(QString error);

public slots:

};

#endif // NUMBERWORKER_H
