#-------------------------------------------------
#
# Project created by QtCreator 2014-11-27T10:37:46
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Skil1
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp \
    consoleui.cpp \
    scientistservice.cpp \
    scientist.cpp \
    scientistrepository.cpp \
    date.cpp

HEADERS += \
    consoleui.h \
    scientistservice.h \
    scientist.h \
    scientistrepository.h \
    date.h \
    scientistsort.h
