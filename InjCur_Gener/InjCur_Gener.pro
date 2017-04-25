#-------------------------------------------------
#
# Project created by QtCreator 2017-04-08T00:27:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InjCur_Gener
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    InjCur.cpp

HEADERS  += mainwindow.h \
    InjCur.h \
    ILogger.hpp

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../../../../Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc/' -ltkVisa32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../../../../Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc/' -ltkVisa32

INCLUDEPATH += $$PWD/'../../../../../../Program Files (x86)/IVI Foundation/VISA/WinNT/include'
DEPENDPATH += $$PWD/'../../../../../../Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc'
