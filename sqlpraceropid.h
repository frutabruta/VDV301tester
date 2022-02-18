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
    //void Pripoj();
    //void StahniSeznam(int &pocetVysledku, int cisloLinky, int cisloSpoje, SeznamZastavek *docasnySeznamZastavek);

    void vytvorHlavniTextNasledujici(QString &textPoleObsah, QString &textPoleCasu, int cisloporadi, QVector<ZastavkaCil> docasnySeznamZastavek, QString locationState);
    int StahniSeznam(int cisloLinky, int cisloSpoje, QVector<ZastavkaCil> &docasnySeznamZastavek, bool platnost);


    int Pripoj();
    //QVector<Linka> seznamLinek;

    void vytvorHlavniAktualni(QString &textPoleObsah, QString &textPoleCasu, int cisloporadi, QVector<ZastavkaCil> docasnySeznamZastavek, QString locationState);
  //  int StahniSeznamNavazSpoj(int idSpoje, QVector<ZastavkaCil> &docasnySeznamZastavek, bool platnost);
    int otevriDB();
    int zavriDB();
    int StahniSeznam(Linka docasnaLinka, int cisloSpoje, QVector<Spoj> &seznamSpoju, bool platnost);


    int VytvorSeznamLinek(QVector<Linka> &docasnySeznamLinek, QString kj);
    int VytvorSeznamSpoju(QVector<Spoj> &docasnySeznamSpoju, Linka docasnaLinka, QString kj);

    int VytvorSeznamKmenovychLinek(QVector<Linka> &docasnySeznamLinek, QString kj);
    int VytvorSeznamPoradi(QVector<Obeh> &docasnySeznamObehu, Linka docasnaLinka, QString kj);
    int VytvorSeznamTurnusSpoju(Obeh &docasnyObeh, QString kj);

    int StahniSeznamCelySpoj(QVector<Spoj> &seznamSpoju, int indexSpoje, bool platnost);
    int nactiPlatnost(QDate &platnostOd, QDate &platnostDo);
    QString maskaKalendarJizd(QDate pracDatum, QDate prvniDenPlatnosti, QDate konecPlatnosti);
    bool jeDatumVRozsahu(QDate datum, QDate zacatek, QDate konec);

signals:
   // void pridejSubscribera(QUrl adresaSubscribera);
    void odesliChybovouHlasku(QString chybovaHlaska);
private:
    void VypisPole(QVector<ZastavkaCil> docasnySeznamZastavek, int &pocetZastavek);
    QString vytvorCasHodinyMinuty(QString vstup);
    QString doplnNulu(int cislo, int pocetMist = 2);
    QString vytvorCasHodinyMinutySekundy(QString vstup);


};

#endif // SQLPRACEROPID_H
