#ifndef SQLPRACEROPID_H
#define SQLPRACEROPID_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSql>
//#include <QVector>

#include "VDV301_Display/seznamzastavek.h"
#include "VDV301_Display/linka.h"
#include "spoj.h"
#include "struktury/pasmo.h"

class SqlPraceRopid
{
public:

    QSqlDatabase mojeDatabaze;
    SqlPraceRopid();
    bool vysledek;
    //void Pripoj();
    //void StahniSeznam(int &pocetVysledku, int cisloLinky, int cisloSpoje, SeznamZastavek *docasnySeznamZastavek);

    void vytvorHlavniText(QString &textPoleObsah, QString &textPoleCasu, int cisloporadi, QVector <SeznamZastavek> docasnySeznamZastavek);
    int StahniSeznam(int cisloLinky, int cisloSpoje, QVector<SeznamZastavek> &docasnySeznamZastavek, bool platnost);


    int Pripoj(QString adresa);
    //QVector<Linka> seznamLinek;
    int VytvorSeznamLinek(QVector<Linka> &docasnySeznamLinek);
    int VytvorSeznamSpoju(QVector<Spoj> &docasnySeznamSpoju, int cisloLinky);
private:
    void VypisPole(QVector<SeznamZastavek> docasnySeznamZastavek, int &pocetZastavek);
    QString vytvorCasHodinyMinuty(QString vstup);
    QString doplnNulu(int cislo, int pocetMist = 2);
    QString vytvorCasHodinyMinutySekundy(QString vstup);
};

#endif // SQLPRACEROPID_H
