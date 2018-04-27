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

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QList>
#include <QFile>
#include <QByteArray>
#include <numberworker.h>
#include <taskperthread.h>
#include <QVector>
#include <threadsaferandom.h>

class Controller : public QObject
{
    Q_OBJECT
    QList<QThread*> mThreads;
    QList<NumberWorker*> mWorkers;
    const int mNoOfThreads;
    bool mRunning;
    qint64 * mResultList;
    const qint64 mN;
    const qint64 mMaxExclusive;
    int mWorkersDone;
    ThreadSafeRandom mTsRandom;
    const QByteArray mChars; // The characters of which the random strings can consist of
    const int lineLength = 8; // Remember that you can't make strings longer if the amount of permutations exceed a 64 bit int. TODO: test it.

    QList<TaskPerThread> getTaskDivisions(const qint64 n, const qint64 maxExclusive);
    void sort();
    bool verifyUniqueness();
    void shuffle();

    /**
     * nrToCharacterString converts the integer based notation into base-[234679acdefghjkmnpqrtxyz] (or actually, the chars array)
     *
     * So, 0 would be 2. 23 would be z. 24 would be 32.
     *
     * Padding is also added. So, the lowest value is 22222222, meaning 0.
     *
     */
    QString nrToCharacterString(quint64 n) const;
public:
    explicit Controller(const qint64 n, const qint64 maxExclusive, QObject *parent = 0);
    ~Controller();
    void start();
    int getNrOfThreads();
    QList<NumberWorker*> getWorkers();
    void cancel();
    bool isRunning() const;

    void saveList(QString filename) const;

signals:
    void operate();
    void error(QString message);
    void started();
    void stopped(bool success);
    void verifyProgress(int value);
    void sortProgress(int value);
    void shuffleProgress(int value);

private slots:
    void handleWorkerResults();

public slots:

};

#endif // CONTROLLER_H
