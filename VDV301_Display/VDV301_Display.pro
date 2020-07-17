#-------------------------------------------------
#
# Project created by QtCreator 2018-06-07T13:35:40
#
#-------------------------------------------------

QT       += core gui
QT += xml
QT       += core gui network
#QT += svg
#QT += webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VDV301_Display
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


SOURCES += \
    httpserver2/myhttpserver.cpp \
        main.cpp \
        mainwindow.cpp \
    xmlparser.cpp \
    seznamzastavek.cpp

HEADERS += \
    httpserver2/myhttpserver.h \
        mainwindow.h \
    xmlparser.h \
    seznamzastavek.h

FORMS += \
        mainwindow.ui
