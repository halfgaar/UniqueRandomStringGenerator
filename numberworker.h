#ifndef NUMBERWORKER_H
#define NUMBERWORKER_H

#include <QObject>
#include <QVector>
#include <QSharedPointer>

class NumberWorker : public QObject
{
    Q_OBJECT

    qint64 n;
    const qint64 minInclusive;
    const qint64 maxExclusive;
    bool mCancelled;
public:
    explicit NumberWorker(qint64 n, qint64 minInclusive, qint64 maxExclusive, QObject *parent = 0);
    void cancel();

public slots:
    void doWork();

signals:
    void progress(int value);
    void resultReady(QSharedPointer<QVector<qint64> > result);
    void error(QString error);

public slots:

};

#endif // NUMBERWORKER_H
