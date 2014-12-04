#-------------------------------------------------
#
# Project created by QtCreator 2014-11-27T10:37:46
#
#-------------------------------------------------

QT       += core sql

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
    date.cpp \
    sqlconnection.cpp \
    scientistsort.cpp

HEADERS += \
    consoleui.h \
    scientistservice.h \
    scientist.h \
    scientistrepository.h \
    date.h \
    scientistsort.h \
    utils.h \
    sqlconnection.h

OTHER_FILES += data/tables.sql

#copydata.commands = $(COPY_DIR) $$PWD/data $$OUT_PWD
#first.depends = $(first) copydata
#export(first.depends)
#export(copydata.commands)
#QMAKE_EXTRA_TARGETS += first copydata

win32 {
    PWD_WIN = $${PWD}
    DESTDIR_WIN = $${OUT_PWD}
    PWD_WIN ~= s,/,\\,g
    DESTDIR_WIN ~= s,/,\\,g

    copyfiles.commands = $$quote(cmd /c xcopy /S /Q /Y /I $${PWD_WIN}\\data $${DESTDIR_WIN})

}
macx {
    copyfiles.commands = cp -r $$PWD/data/* $$OUT_PWD
}
linux {
    copyfiles.commands = cp -r $$PWD/data/* $$OUT_PWD
}
QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles

#CONFIG+=static
