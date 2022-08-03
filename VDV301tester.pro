#-------------------------------------------------
#
# Project created by QtCreator 2017-10-03T20:55:15
# blabla
#-------------------------------------------------
#requires(qtHaveModule(httpserver))
QT       += core gui
QT += network sql
QTPLUGIN += QSQLMYSQL
QT += xml
QT += serialport
QT += multimedia
QT+= httpserver

DEFINES+= QZEROCONF_STATIC
include(VDV301publisher/QtZeroConf/qtzeroconf.pri)


#include <QtXml>

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VDV301tester
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


QT_MULTIMEDIA_PREFERRED_PLUGINS=
# QT       += core

//LIBS += -lqhttpserver

SOURCES += \
    VDV301publisher/customerinformationservice.cpp \
    VDV301publisher/devicemanagementservice.cpp\
    VDV301publisher/httpsluzba.cpp \
    VDV301publisher/newhttpserver.cpp \
    VDV301publisher/subscriber.cpp \
    VDV301publisher/ticketvalidationservice.cpp \    
    VDV301publisher/xmlcommon.cpp \
    VDV301publisher/xmlcustomerinformationservice.cpp \
    VDV301publisher/xmldevicemanagementservice.cpp \
    VDV301publisher/xmlticketvalidationservice.cpp \    
    VDV301subscriber/ibisipsubscriber.cpp \
    VDV301struktury/cestaudaje.cpp \
    VDV301struktury/linka.cpp \
    VDV301struktury/obeh.cpp \
    VDV301struktury/pasmo.cpp \
    VDV301struktury/prestup.cpp \
    VDV301struktury/prestupmpv.cpp \
    VDV301struktury/spoj.cpp \
    VDV301struktury/zastavka.cpp \
    VDV301struktury/zastavkacil.cpp \
    VDV301struktury/specialnihlaseni.cpp \
    VDV301testy/polozkatestu.cpp \
    VDV301testy/testdemo.cpp \
    VDV301testy/testdetekcebonjour.cpp \
    VDV301testy/testodberuserver.cpp \
    VDV301testy/vdv301testy.cpp \
    hlasic.cpp \
    ibisovladani.cpp \
    konfigurace.cpp \
    logfile.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindowpomocne.cpp \   
    sqlpraceropid.cpp \
    xmlmpvparser.cpp \
    xmlropidparser.cpp


HEADERS += \
    VDV301publisher/customerinformationservice.h \
    VDV301publisher/devicemanagementservice.h \
    VDV301publisher/httpsluzba.h \
    VDV301publisher/newhttpserver.h \
    VDV301publisher/subscriber.h \
    VDV301publisher/ticketvalidationservice.h \
    VDV301publisher/xmlcommon.h \
    VDV301publisher/xmlcustomerinformationservice.h \
    VDV301publisher/xmldevicemanagementservice.h \
    VDV301publisher/xmlticketvalidationservice.h \    
    VDV301struktury/cestaudaje.h \
    VDV301struktury/linka.h \
    VDV301struktury/obeh.h \
    VDV301struktury/prestup.h \
    VDV301struktury/pasmo.h \
    VDV301struktury/prestupmpv.h \
    VDV301struktury/specialnihlaseni.h \
    VDV301struktury/spoj.h \
    VDV301struktury/zastavka.h \
    VDV301struktury/zastavkacil.h \
    VDV301subscriber/ibisipsubscriber.h \
    VDV301subscriber/newhttpserver.h \
    VDV301testy/polozkatestu.h \
    VDV301testy/testdemo.h \
    VDV301testy/testdetekcebonjour.h \
    VDV301testy/testodberuserver.h \
    VDV301testy/vdv301testy.h \
    hlasic.h \    
    ibisovladani.h \
    konfigurace.h \
    logfile.h \
    mainwindow.h \
    mainwindowpomocne.h \    
    sqlpraceropid.h \
    xmlmpvparser.h \    
    xmlropidparser.h

FORMS += \
        mainwindow.ui
