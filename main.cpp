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
#include <QApplication>
#include <controller.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller c(220000000, 110075314176, &a); // TODO: I'm not sure yet if it should be 110075314176 or 110075314175 (the exclusive/inclusive part).
    //Controller c(10, 100, &a);

    MainWindow w(c);
    w.show();

    return a.exec();
}
