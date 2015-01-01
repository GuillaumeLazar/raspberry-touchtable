#-------------------------------------------------
#
# Project created by QtCreator 2014-10-12T20:00:56
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeviceAcquisitionTcpClient
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    devicemessage.cpp \
    devicemessageobject.cpp

HEADERS  += MainWindow.h \
    devicemessage.h \
    devicemessageobject.h

FORMS    += mainwindow.ui
