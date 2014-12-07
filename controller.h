#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QList>
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
    int mWorkersDone;
    ThreadSafeRandom mTsRandom;

    QList<TaskPerThread> getTaskDivisions(const qint64 n, const qint64 maxExclusive);
    void sort();
    bool verifyUniqueness();
    void shuffle();
public:
    explicit Controller(const qint64 n, const qint64 maxExclusive, QObject *parent = 0);
    ~Controller();
    void start();
    int getNrOfThreads();
    QList<NumberWorker*> getWorkers();
    void cancel();
    bool isRunning() const;

signals:
    void operate();
    void error(QString message);
    void started();
    void stopped(bool success);
    void verifyProgress(int value);
    void sortProgress(int value);

private slots:
    void handleWorkerResults();

public slots:

};

#endif // CONTROLLER_H
