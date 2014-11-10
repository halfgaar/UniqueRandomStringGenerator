#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <threadview.h>
#include <numberworker.h>

MainWindow::MainWindow(Controller &c, QWidget *parent) :
    QMainWindow(parent),
    mController(c),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    foreach(NumberWorker *numWorker, c.getWorkers())
    {
        ThreadView * tView = new ThreadView(numWorker, this);
        ui->threadsView->addWidget(tView);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnGenerate_clicked()
{
    mController.start();
}
