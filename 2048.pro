#-------------------------------------------------
#
# Project created by QtCreator 2016-09-19T11:07:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2048
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc

DISTFILES += \
    myapp.rc

win32:RC_FILE = myapp.rc
