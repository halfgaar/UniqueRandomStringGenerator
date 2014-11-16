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
    QVector<qint64> &mTotalResultList;
public:
    explicit NumberWorker(const TaskPerThread task, QThread &thread, QVector<qint64> &totalResultList);
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
