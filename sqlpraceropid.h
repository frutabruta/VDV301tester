#ifndef SQLPRACEROPID_H
#define SQLPRACEROPID_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSql>
//#include <QVector>

#include "VDV301struktury/seznamzastavek.h"
#include "VDV301struktury/linka.h"
#include "VDV301struktury/spoj.h"
#include "VDV301struktury/pasmo.h"

class SqlPraceRopid
{
public:

    QSqlDatabase mojeDatabaze;
    SqlPraceRopid();
    bool vysledek;
    //void Pripoj();
    //void StahniSeznam(int &pocetVysledku, int cisloLinky, int cisloSpoje, SeznamZastavek *docasnySeznamZastavek);

    void vytvorHlavniTextNasledujici(QString &textPoleObsah, QString &textPoleCasu, int cisloporadi, QVector <SeznamZastavek> docasnySeznamZastavek, QString locationState);
    int StahniSeznam(int cisloLinky, int cisloSpoje, QVector<SeznamZastavek> &docasnySeznamZastavek, bool platnost);


    int Pripoj(QString adresa);
    //QVector<Linka> seznamLinek;
    int VytvorSeznamLinek(QVector<Linka> &docasnySeznamLinek);
    int VytvorSeznamSpoju(QVector<Spoj> &docasnySeznamSpoju, int cisloLinky);
    void vytvorHlavniAktualni(QString &textPoleObsah, QString &textPoleCasu, int cisloporadi, QVector<SeznamZastavek> docasnySeznamZastavek, QString locationState);
private:
    void VypisPole(QVector<SeznamZastavek> docasnySeznamZastavek, int &pocetZastavek);
    QString vytvorCasHodinyMinuty(QString vstup);
    QString doplnNulu(int cislo, int pocetMist = 2);
    QString vytvorCasHodinyMinutySekundy(QString vstup);
};

#endif // SQLPRACEROPID_H
