#-------------------------------------------------
#
# Project created by QtCreator 2015-11-28T20:00:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chatchat
TEMPLATE = app


SOURCES += main.cpp\
    ui/rootwindow.cpp \
    ui/addnewaccountview.cpp

HEADERS  += \
    base/base.h \
    ui/rootwindow.h \
    ui/addnewaccountview.h \
    base/thread_temple.h

FORMS    += \
    ui/rootwindow.ui \
    ui/addnewaccountview.ui
