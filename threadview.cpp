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

#include "threadview.h"
#include "ui_threadview.h"

ThreadView::ThreadView(NumberWorker *numberWorker, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThreadView)
{
    ui->setupUi(this);
    connect(numberWorker, &NumberWorker::progress, this, &ThreadView::setValue);
    ui->label->setText(QString("Thread %1").arg(numberWorker->getThreadID()));
}

ThreadView::~ThreadView()
{
    delete ui;
}

void ThreadView::setValue(int value)
{
    ui->progressBar->setValue(value);
}
