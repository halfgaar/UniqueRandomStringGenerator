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
