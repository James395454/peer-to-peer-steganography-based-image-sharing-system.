TEMPLATE = app
CONFIG += console c++11
CONFIG += thread
LIBS += -lsqlite3
QT += widgets
SOURCES += main.cpp \
    server.cpp \
    udpsocket.cpp \
    udpserversocket.cpp \
    message.cpp \
    database.cpp

HEADERS += \
    message.h \
    udpsocket.h \
    udpserversocket.h \
    server.h \
    database.h

FORMS +=


