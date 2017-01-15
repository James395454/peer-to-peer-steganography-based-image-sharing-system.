#-------------------------------------------------
#
# Project created by QtCreator 2016-11-26T16:51:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Exercise2
TEMPLATE = app
CONFIG += console
CONFIG += thread
QT += widgets
SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    image.cpp \
    message.cpp \
    messagehandler.cpp \
    udpclientsocket.cpp \
    useraccount.cpp \
    udpsocket.cpp \
    appwindow.cpp \
    server.cpp \
    udpserversocket.cpp \
    getimage.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    client.h \
    image.h \
    message.h \
    messagehandler.h \
    server.h \
    udpclientsocket.h \
    udpserversocket.h \
    useraccount.h \
    udpsocket.h \
    appwindow.h \
    getimage.h \
    dialog.h

FORMS    += mainwindow.ui \
    appwindow.ui \
    dialog.ui
