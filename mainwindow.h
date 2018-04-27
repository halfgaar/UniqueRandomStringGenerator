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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <controller.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Controller &mController;

    void updateInterfaceMode();

public:
    explicit MainWindow(Controller &c, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onControllerStarted();
    void onControllerStopped();

    void on_actionGenerate_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
