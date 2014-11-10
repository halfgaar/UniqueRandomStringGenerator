#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QList>
#include <numberworker.h>

class Controller : public QObject
{
    Q_OBJECT
    QList<QThread*> mThreads;
    QList<NumberWorker*> mWorkers;
    const int mNoOfThreads;
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();
    void start();
    int getNrOfThreads();
    QList<NumberWorker*> getWorkers();

signals:
    void operate();

private slots:
    void handleWorkerResults(QVector<int> result);

public slots:

};

#endif // CONTROLLER_H
