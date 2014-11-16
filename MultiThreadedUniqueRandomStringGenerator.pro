#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T19:33:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MultiThreadedUniqueRandomStringGenerator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    threadview.cpp \
    numberworker.cpp \
    controller.cpp \
    taskperthread.cpp

HEADERS  += mainwindow.h \
    threadview.h \
    numberworker.h \
    controller.h \
    taskperthread.h

FORMS    += mainwindow.ui \
    threadview.ui
