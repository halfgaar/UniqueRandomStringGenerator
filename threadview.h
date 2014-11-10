#ifndef THREADVIEW_H
#define THREADVIEW_H

#include <QWidget>
#include <numberworker.h>

namespace Ui {
class ThreadView;
}

class ThreadView : public QWidget
{
    Q_OBJECT

public:
    explicit ThreadView(NumberWorker *numberWorker, QWidget *parent = 0);
    ~ThreadView();

private:
    Ui::ThreadView *ui;

public slots:
    void setValue(int value);
};

#endif // THREADVIEW_H
