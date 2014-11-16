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
    const qint64 minInclusive;
    const qint64 maxExclusive;
    bool mCancelled;
    static int globalThreadCounter;
    int mThreadID;
public:
    explicit NumberWorker(const TaskPerThread task, QThread &thread);
    void cancel();
    int getThreadID() const;

public slots:
    void doWork();

signals:
    void progress(int value);
    void resultReady(QSharedPointer<QVector<qint64> > result);
    void error(QString error);

public slots:

};

#endif // NUMBERWORKER_H
