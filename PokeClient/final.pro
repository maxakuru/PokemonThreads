#-------------------------------------------------
#
# Project created by QtCreator 2015-12-06T13:51:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = final
TEMPLATE = app

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    Pokemon.cpp \
    Blockable.cpp \
    socket.cpp \
    socketserver.cpp \
    thread.cpp

HEADERS  += mainwindow.h \
    Pokemon.h \
    Blockable.h \
    shared.h \
    socket.h \
    socketserver.h \
    thread.h

FORMS    += mainwindow.ui

RESOURCES += \
    images/images.qrc

DISTFILES += \
    images/alakazam.png \
    images/venusaur.png \
    final.pro.user
