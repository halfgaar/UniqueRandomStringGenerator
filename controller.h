#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QList>
#include <numberworker.h>
#include <taskperthread.h>

class Controller : public QObject
{
    Q_OBJECT
    QList<QThread*> mThreads;
    QList<NumberWorker*> mWorkers;
    const int mNoOfThreads;
    bool mRunning;

    QList<TaskPerThread> getTaskDivisions(const qint64 n, const qint64 maxExclusive);
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
    void stopped();

private slots:
    void handleWorkerResults(QSharedPointer<QVector<qint64> > result);

public slots:

};

#endif // CONTROLLER_H
