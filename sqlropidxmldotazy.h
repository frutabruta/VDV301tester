#ifndef SQLROPIDXMLDOTAZY_H
#define SQLROPIDXMLDOTAZY_H

#include <QMainWindow>

#include <QWidget>

#include "VDV301struktury/zastavka.h"
#include "VDV301struktury/linka.h"
#include "VDV301struktury/spoj.h"
#include "VDV301struktury/pasmo.h"
#include "VDV301struktury/zastavkacil.h"
#include "VDV301struktury/obeh.h"

#include "XmlRopidImportStream/sqlitezaklad.h"
#include "MapaVykresleni/mnozinabodu.h"


class SqlRopidXmlDotazy: public  SqLiteZaklad
{
    Q_OBJECT
public:

    SqlRopidXmlDotazy();

    int stahniSeznamCelySpojTurnus(QVector<Spoj> &seznamSpoju, int indexSpoje, QString kj);
    QString stahniSeznamSpolecnaCastDotazu();

    int vytvorSeznamTurnusSpoju(Obeh &docasnyObeh, QString kj);

    QString pasmaDoStringu(QVector<Pasmo> pasma, QString delimiter);
    QVector<Pasmo> pasmoStringDoVectoru(QString vstup, QString system, QString tl);
    QString doplnNulu(int cislo, int pocetMist = 2);

    int najdiTurnusZeSpoje(Spoj spoj, int &kmenovaLinka, int &poradi, int &order, QString kj);
    int poziceSpojeNaSeznamu(QVector<Spoj> seznamSpoju, Spoj spoj);

    QVector<QString> StahniPoznamky(int idSpoje, int xorder);

    int nactiPlatnost(QDate &platnostOd, QDate &platnostDo);
    QString maskaKalendarJizd(QDate pracDatum, QDate prvniDenPlatnosti, QDate konecPlatnosti);

    QSqlQueryModel *stahniSeznamLinekModel(QString kj);
    QSqlQueryModel *stahniSeznaSpojuModel(Linka docasnaLinka, QString kj);
    QSqlQueryModel *stahniSeznamKmenovychLinekModel(QString kj);
    QSqlQueryModel *stahniSeznamPoradiModel(Linka docasnaLinka, QString kj);
    QSqlQueryModel *stahniSeznamTurnusSpojuModel(Obeh &docasnyObeh, QString kj);
    QVector<MapaBod> vytvorTrajektorii(int cisloSpoje);
    static double absolutniHodnota(double vstup);
private:

    void vypisPole(QVector<ZastavkaCil> docasnySeznamZastavek, int &pocetZastavek);
    QVector<Pasmo> vyrobPasmaMezikraj(QVector<QString> tp, QVector<QString> pz, QVector<QString> pc, QString cids, QString tl);
};

#endif // SQLROPIDXMLDOTAZY_H
