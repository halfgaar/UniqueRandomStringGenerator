#ifndef NUMBERWORKER_H
#define NUMBERWORKER_H

#include <QObject>
#include <QVector>

class NumberWorker : public QObject
{
    Q_OBJECT
public:
    explicit NumberWorker(QObject *parent = 0);

public slots:
    void doWork();

signals:
    void progress(int value);
    void resultReady(QVector<int> result);

public slots:

};

#endif // NUMBERWORKER_H
