#ifndef SQLPRACEROPID_H
#define SQLPRACEROPID_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSql>
//#include <QVector>

#include "VDV301struktury/zastavka.h"
#include "VDV301struktury/linka.h"
#include "VDV301struktury/spoj.h"
#include "VDV301struktury/pasmo.h"
#include "VDV301struktury/zastavkacil.h"
//#include "VDV301struktury/trip.h"
#include "VDV301struktury/obeh.h"

class SqlPraceRopid: public QObject
{
    Q_OBJECT
public:

    QSqlDatabase mojeDatabaze;
    SqlPraceRopid();
    bool vysledek;



    int Pripoj();
    //QVector<Linka> seznamLinek;

    //  int StahniSeznamNavazSpoj(int idSpoje, QVector<ZastavkaCil> &docasnySeznamZastavek, bool platnost);
    int otevriDB();
    int zavriDB();

    int StahniSeznamLinkospoj(Linka docasnaLinka, int cisloSpoje, QVector<Spoj> &seznamSpoju, QString kj);
    int StahniSeznamCelySpojTurnus(QVector<Spoj> &seznamSpoju, int indexSpoje, QString kj);
    void vytvorDisplejRidiceAktualniZastavka(QString &textPoleObsah, QString &textPoleCasu, int cisloporadi, QVector<ZastavkaCil> docasnySeznamZastavek, QString locationState);
    void vytvorDisplejRidiceSeznamZastavek(QString &textPoleObsah, QString &textPoleCasu, int cisloporadi, QVector<ZastavkaCil> docasnySeznamZastavek, QString locationState);


    int VytvorSeznamLinek(QVector<Linka> &docasnySeznamLinek, QString kj);
    int VytvorSeznamSpoju(QVector<Spoj> &docasnySeznamSpoju, Linka docasnaLinka, QString kj);

    int VytvorSeznamKmenovychLinek(QVector<Linka> &docasnySeznamLinek, QString kj);
    int VytvorSeznamPoradi(QVector<Obeh> &docasnySeznamObehu, Linka docasnaLinka, QString kj);
    int VytvorSeznamTurnusSpoju(Obeh &docasnyObeh, QString kj);

    // kalendář jízdenek
    int nactiPlatnost(QDate &platnostOd, QDate &platnostDo);
    QString maskaKalendarJizd(QDate pracDatum, QDate prvniDenPlatnosti, QDate konecPlatnosti);
    bool jeDatumVRozsahu(QDate datum, QDate zacatek, QDate konec);

    QString pasmaDoStringu(QVector<Pasmo> pasma, QString delimiter);
    QString vytvorCasHodinyMinutySekundy(QString vstup);
    QString vytvorCasHodinyMinuty(QString vstup);
    QString doplnNulu(int cislo, int pocetMist = 2);
    QString StahniSeznamSpolecnaCastDotazu();
signals:
    void odesliChybovouHlasku(QString chybovaHlaska);
private:
    void VypisPole(QVector<ZastavkaCil> docasnySeznamZastavek, int &pocetZastavek);




    QVector<Pasmo> vyrobPasmaMezikraj(QVector<QString> tp, QVector<QString> pz, QVector<QString> pc, QString cids, QString tl);
};

#endif // SQLPRACEROPID_H
