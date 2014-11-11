#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QList>
#include <numberworker.h>

class TaskPerThread
{
public:
    explicit TaskPerThread(qint64 n, qint64 minInclusive, qint64 maxExclusive);
    void appendN(qint64 n);
    void appendMax(qint64 maxExlusive);

    qint64 getN();
    qint64 getMinInclusive();
    qint64 getMaxExclusive();

private:
    qint64 n;
    qint64 minInclusive;
    qint64 maxExclusive;
};

class Controller : public QObject
{
    Q_OBJECT
    QList<QThread*> mThreads;
    QList<NumberWorker*> mWorkers;
    const int mNoOfThreads;


    QList<TaskPerThread> getTaskDivisions(const qint64 n, const qint64 maxExclusive);
public:
    explicit Controller(const qint64 n, const qint64 maxExclusive, QObject *parent = 0);
    ~Controller();
    void start();
    int getNrOfThreads();
    QList<NumberWorker*> getWorkers();

signals:
    void operate();
    void error(QString message);

private slots:
    void handleWorkerResults(QSharedPointer<QVector<qint64> > result);

public slots:

};

#endif // CONTROLLER_H
