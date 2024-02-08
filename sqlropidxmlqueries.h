#ifndef SQLROPIDXMLQUERIES_H
#define SQLROPIDXMLQUERIES_H

#include <QMainWindow>

#include <QWidget>


#include "VDV301DataStructures/stoppoint.h"
#include "VDV301DataStructures/line.h"
#include "VDV301DataStructures/trip.h"
#include "VDV301DataStructures/farezone.h"
#include "VDV301DataStructures/stoppointdestination.h"
#include "VDV301DataStructures/vehiclerun.h"

#include "XmlRopidImportStream/sqlitezaklad.h"
#include "MapaVykresleni/mnozinabodu.h"
#include "MapaVykresleni/mapavykresleni.h"

class SqlRopidXmlQueries: public  SqLiteZaklad
{
    Q_OBJECT
public:
    
    SqlRopidXmlQueries();

    int stahniSeznamCelySpojTurnus(QVector<Trip> &seznamSpoju, int indexSpoje, QString kj);
    QString stahniSeznamSpolecnaCastDotazu();

    int vytvorSeznamTurnusSpoju(VehicleRun &docasnyObeh, QString kj);

    QString pasmaDoStringu(QVector<FareZone> pasma, QString delimiter);
    QVector<FareZone> pasmoStringDoVectoru(QString vstup, QString system, QString tl);
    QString doplnNulu(int cislo, int pocetMist = 2);

    int najdiTurnusZeSpoje(Trip spoj, int &kmenovaLinka, int &poradi, int &order, QString kj);
    int poziceSpojeNaSeznamu(QVector<Trip> seznamSpoju, Trip spoj);

    QVector<QString> stahniPoznamky(int idSpoje, int xorder);

    int nactiPlatnost(QDate &platnostOd, QDate &platnostDo);
    QString maskaKalendarJizd(QDate pracDatum, QDate prvniDenPlatnosti, QDate konecPlatnosti);

    QSqlQueryModel *stahniSeznamLinekModel(QString kj);
    QSqlQueryModel *stahniSeznamSpojuModel(Line docasnaLinka, QString kj);
    QSqlQueryModel *stahniSeznamKmenovychLinekModel(QString kj);
    QSqlQueryModel *stahniSeznamPoradiModel(Line docasnaLinka, QString kj);
    QSqlQueryModel *stahniSeznamTurnusSpojuModel(VehicleRun &docasnyObeh, QString kj);
    QVector<MapaBod> vytvorTrajektorii(int cisloSpoje, QString kj);
    static double absolutniHodnota(double vstup);
    QSqlQueryModel *stahniSeznamSpojuModel2(Line docasnaLinka, QString kj);
private:

    void vypisPole(QVector<StopPointDestination> docasnySeznamZastavek, int &pocetZastavek);
    QVector<FareZone> vyrobPasmaMezikraj(QVector<QString> tp, QVector<QString> pz, QVector<QString> pc, QString cids, QString tl);
};

#endif // SQLROPIDXMLQUERIES_H
