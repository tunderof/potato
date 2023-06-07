TARGET = HallServer

QT += network
QT += sql
QT -= gui
QT += testlib

CONFIG += console c++11
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        functions.cpp \
        main.cpp \
        mytcpserver.cpp \
        unitTests.cpp

HEADERS += \
    functions.h \
    mytcpserver.h \
    unitTests.h
