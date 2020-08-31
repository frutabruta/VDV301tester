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

class SqlPraceRopid
{
public:

    QSqlDatabase mojeDatabaze;
    SqlPraceRopid();
    bool vysledek;
    //void Pripoj();
    //void StahniSeznam(int &pocetVysledku, int cisloLinky, int cisloSpoje, SeznamZastavek *docasnySeznamZastavek);
    void VypisPole(QVector<SeznamZastavek> docasnySeznamZastavek, int &pocetZastavek);
    void TestDotaz(QString &textPoleObsah, int cisloporadi, int cislolinky, int cislospoje,QVector <SeznamZastavek> docasnySeznamZastavek, int pocetZastavek);
    int StahniSeznam(int &pocetVysledku, int cisloLinky, int cisloSpoje, QVector<SeznamZastavek> &docasnySeznamZastavek, bool platnost);
    QString vytvorCas(QString vstup);
    QString doplnNulu(int cislo, int pocetMist = 2);
    void Pripoj(QString adresa);
    //QVector<Linka> seznamLinek;
    int VytvorSeznamLinek(QVector<Linka> &docasnySeznamLinek);
    int VytvorSeznamSpoju(QVector<Spoj> &docasnySeznamSpoju, int cisloLinky);
};

#endif // SQLPRACEROPID_H
