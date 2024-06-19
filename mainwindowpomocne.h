#ifndef MAINWINDOWPOMOCNE_H
#define MAINWINDOWPOMOCNE_H

#include <QMainWindow>
#include <QObject>
#include "VDV301publisher/subscriber.h"
#include "sqlropidxmlqueries.h"
#include <QTableWidget>
#include "VDV301publisher/VDV301DataStructures/additionalannoucement.h"
#include "VDV301publisher/VDV301DataStructures/stoppointdestination.h"
#include "VDV301publisher/VDV301DataStructures/vdv301enumerations.h"

class MainWindowPomocne: public QObject
{
    Q_OBJECT
public:
    MainWindowPomocne();
    // void vypisSubscribery2_2CZ(QVector<Subscriber> adresy);
    static int jeVRozsahu(int index, int pocetHodnot, QString funkce);
    static void naplnTabulkuHlaseni(QTableWidget *vstup, QVector<AdditionalAnnoucement> seznamHlaseni);

    static void dumpStopsToTable(int cisloporadi, QVector<StopPointDestination> docasnySeznamZastavek, Vdv301Enumerations::LocationStateEnumeration locationState, SqlRopidXmlQueries &sqlRopidQuerries, QTableWidget *table);
};

#endif // MAINWINDOWPOMOCNE_H
