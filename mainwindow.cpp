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

    connect(&c, &Controller::started, this, &MainWindow::onControllerStarted);
    connect(&c, &Controller::stopped, this, &MainWindow::onControllerStopped);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInterfaceMode()
{
    bool buttonsEnabled = true;

    if (mController.isRunning())
    {
        buttonsEnabled = false;
    }

    ui->actionGenerate->setEnabled(buttonsEnabled);
}

void MainWindow::onControllerStarted()
{
    updateInterfaceMode();
}

void MainWindow::onControllerStopped()
{
    updateInterfaceMode();
}

void MainWindow::on_actionGenerate_triggered()
{
    mController.start();
}
