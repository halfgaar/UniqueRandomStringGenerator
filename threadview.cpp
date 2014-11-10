#include "threadview.h"
#include "ui_threadview.h"

ThreadView::ThreadView(NumberWorker *numberWorker, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThreadView)
{
    ui->setupUi(this);
    connect(numberWorker, &NumberWorker::progress, this, &ThreadView::setValue);
}

ThreadView::~ThreadView()
{
    delete ui;
}

void ThreadView::setValue(int value)
{
    ui->progressBar->setValue(value);
}
