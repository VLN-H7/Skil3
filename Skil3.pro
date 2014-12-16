#-------------------------------------------------
#
# Project created by QtCreator 2014-11-27T10:37:46
#
#-------------------------------------------------
QT       += core gui sql network
QTPLUGIN += qjpeg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Skil1
CONFIG   += gui
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app

#QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp \
    services/scientistservice.cpp \
    models/scientist.cpp \
    repositories/scientistrepository.cpp \
    date.cpp \
    sqlconnection.cpp \
    models/computer.cpp \
    services/computerservice.cpp \
    repositories/computerrepository.cpp \
    utils.cpp \
    ui/computerscientists.cpp \
    ui/computerdialog.cpp \
    ui/scientistdialog.cpp \
    imageloader.cpp \
    ui/computerconnectdialog.cpp \
    ui/scientistconnectdialog.cpp \
    widgets/droptablewidget.cpp \
    models/type.cpp \
    ui/aboutdialog.cpp \
    ui/computertypedialog.cpp

HEADERS += \
    services/scientistservice.h \
    models/scientist.h \
    repositories/scientistrepository.h \
    date.h \
    utils.h \
    sqlconnection.h \
    models/computer.h \
    services/computerservice.h \
    repositories/computerrepository.h \
    sort.h \
    ui/computerscientists.h \
    ui/computerdialog.h \
    ui/scientistdialog.h \
    imageloader.h \
    ui/computerconnectdialog.h \
    ui/scientistconnectdialog.h \
    widgets/droptablewidget.h \
    widgets/dropmimedata.h \
    models/type.h \
    ui/aboutdialog.h \
    ui/computertypedialog.h

FORMS    += \
    ui/computerscientists.ui \
    ui/scientistdialog.ui \
    ui/computerdialog.ui \
    ui/computerconnectdialog.ui \
    ui/scientistconnectdialog.ui \
    ui/aboutdialog.ui \
    ui/computertypedialog.ui

#CONFIG+=static

RESOURCES += \
    bin.qrc
