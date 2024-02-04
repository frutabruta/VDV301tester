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
QT += httpserver
#CONFIG   += console

DEFINES+= QZEROCONF_STATIC
include(VDV301publisher/QtZeroConf/qtzeroconf.pri)


#include <QtXml>

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat


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

#LIBS += -lqhttpserver

SOURCES += \
    VDV301DataStructures/additionalannoucement.cpp \
    VDV301DataStructures/connection.cpp \
    VDV301DataStructures/connectiongolemio.cpp \
    VDV301DataStructures/connectionmpv.cpp \
    VDV301DataStructures/farezone.cpp \
    VDV301DataStructures/line.cpp \
    VDV301DataStructures/stoppoint.cpp \
    VDV301DataStructures/stoppointdestination.cpp \
    VDV301DataStructures/trip.cpp \
    VDV301DataStructures/vehiclerun.cpp \
    VDV301DataStructures/vehiclestate.cpp \
    VDV301publisher/colordisplayrules.cpp \
    VDV301publisher/customerinformationservice.cpp \
    VDV301publisher/devicemanagementservice.cpp\
    VDV301publisher/httpservice.cpp \
    VDV301publisher/httpserverpublisher.cpp \
    VDV301publisher/subscriber.cpp \
    VDV301publisher/ticketvalidationservice.cpp \
    VDV301publisher/xmlcommon.cpp \
    VDV301publisher/xmlcustomerinformationservice.cpp \
    VDV301publisher/xmldevicemanagementservice.cpp \
    VDV301publisher/xmlticketvalidationservice.cpp \
    VDV301subscriber/devmgmtpublisherstruct.cpp \
    VDV301subscriber/devmgmtsubscriber.cpp \
    VDV301subscriber/devmgmtsubscriber1.cpp \
    VDV301subscriber/devmgmtsubscriber2.cpp \
    VDV301subscriber/ibisipsubscriber.cpp \
    VDV301subscriber/httpserversubscriber.cpp \
    VDV301subscriber/ibisipsubscriberonepublisher.cpp \
    VDV301testy/polozkatestu.cpp \
    VDV301testy/testdemo.cpp \
    VDV301testy/testdetekcebonjour.cpp \
    VDV301testy/testodberuserver.cpp \
    VDV301testy/vdv301testy.cpp \
    XmlRopidImportStream/xmlimportjr.cpp \
    XmlRopidImportStream/xmlropidimportstream.cpp \
    golemio.cpp \
    hlasic.cpp \
    ibisovladani.cpp \
    konfigurace.cpp \
    logfile.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindowpomocne.cpp \
    XmlRopidImportStream/sqlitezaklad.cpp \
    MapaVykresleni/mapabod.cpp \
    MapaVykresleni/mapavykresleni.cpp \
    MapaVykresleni/mnozinabodu.cpp \
    sqldotazymodel.cpp \
    sqlropidxmldotazy.cpp \
    xmlmpvparser.cpp

HEADERS += \
    VDV301DataStructures/additionalannoucement.h \
    VDV301DataStructures/connection.h \
    VDV301DataStructures/connectiongolemio.h \
    VDV301DataStructures/connectionmpv.h \
    VDV301DataStructures/farezone.h \
    VDV301DataStructures/line.h \
    VDV301DataStructures/stoppoint.h \
    VDV301DataStructures/stoppointdestination.h \
    VDV301DataStructures/trip.h \
    VDV301DataStructures/vehiclerun.h \
    VDV301DataStructures/vehiclestate.h \
    VDV301publisher/colordisplayrules.h \
    VDV301publisher/customerinformationservice.h \
    VDV301publisher/devicemanagementservice.h \
    VDV301publisher/httpservice.h \
    VDV301publisher/httpserverpublisher.h \
    VDV301publisher/subscriber.h \
    VDV301publisher/ticketvalidationservice.h \
    VDV301publisher/xmlcommon.h \
    VDV301publisher/xmlcustomerinformationservice.h \
    VDV301publisher/xmldevicemanagementservice.h \
    VDV301publisher/xmlticketvalidationservice.h \
    VDV301subscriber/devmgmtpublisherstruct.h \
    VDV301subscriber/devmgmtsubscriber.h \
    VDV301subscriber/devmgmtsubscriber1.h \
    VDV301subscriber/devmgmtsubscriber2.h \
    VDV301subscriber/ibisipsubscriber.h \
    VDV301subscriber/httpserversubscriber.h \
    VDV301subscriber/ibisipsubscriberonepublisher.h \
    VDV301testy/polozkatestu.h \
    VDV301testy/testdemo.h \
    VDV301testy/testdetekcebonjour.h \
    VDV301testy/testodberuserver.h \
    VDV301testy/vdv301testy.h \
    XmlRopidImportStream/xmlimportjr.h \
    XmlRopidImportStream/xmlropidimportstream.h \
    XmlRopidImportStream/sqlitezaklad.h \
    golemio.h \
    hlasic.h \
    ibisovladani.h \
    konfigurace.h \
    logfile.h \
    mainwindow.h \
    mainwindowpomocne.h \
    MapaVykresleni/mapabod.h \
    MapaVykresleni/mapavykresleni.h \
    MapaVykresleni/mnozinabodu.h \
    sqldotazymodel.h \
    sqlropidxmldotazy.h \
    xmlmpvparser.h

FORMS += \
        mainwindow.ui

TRANSLATIONS += \
        lang_cs.ts\
        lang_en.ts

RESOURCES += \
    lang.qrc
