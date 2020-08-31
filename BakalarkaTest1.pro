#-------------------------------------------------
#
# Project created by QtCreator 2017-10-03T20:55:15
# blabla
#-------------------------------------------------

QT       += core gui
QT += network sql
QTPLUGIN += QSQLMYSQL
QT += xml
QT += serialport
QT += multimedia

DEFINES= QZEROCONF_STATIC

include(qtzeroconf/qtzeroconf.pri)



#include <QtXml>

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BakalarkaTest1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QT += network


# QT       += core









//LIBS += -lqhttpserver

SOURCES += \
    VDV301_Display/linka.cpp \
    hlasic.cpp \
        main.cpp \
        mainwindow.cpp \
    prestupmpv.cpp \
    spoj.cpp \
    sqlprace.cpp \
    httpserver/myhttpserver.cpp \
    VDV301_Display/seznamzastavek.cpp\
    xmlgenerator.cpp \
    cestaudaje.cpp \
    xmlmpvparser.cpp \
    sqlpraceropid.cpp \
    xmlropidparser.cpp \
    ibisovladani.cpp


HEADERS += \
    VDV301_Display/linka.h \
    hlasic.h \
        mainwindow.h \
    prestupmpv.h \
    spoj.h \
    sqlprace.h \
    httpserver/myhttpserver.h \
    VDV301_Display/seznamzastavek.h\
    xmlgenerator.h \
    cestaudaje.h \
    xmlmpvparser.h \
    sqlpraceropid.h \
    xmlropidparser.h \
    ibisovladani.h

FORMS += \
        mainwindow.ui
