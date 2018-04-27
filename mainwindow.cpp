/*
 * Copyright (C) 2018  Wiebe Cazemier <wiebe@halfgaar.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * https://www.gnu.org/licenses/gpl-2.0.html
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <threadview.h>
#include <numberworker.h>
#include <QProgressBar>


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
    connect(&c, SIGNAL(verifyProgress(int)), ui->prgVerify, SLOT(setValue(int)));
    connect(&c, SIGNAL(sortProgress(int)), ui->prgSort, SLOT(setValue(int)));
    connect(&c, SIGNAL(shuffleProgress(int)), ui->prgShuffle, SLOT(setValue(int)));
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
