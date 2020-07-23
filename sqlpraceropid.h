#ifndef SQLPRACEROPID_H
#define SQLPRACEROPID_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSql>
//#include <QVector>

#include "VDV301_Display/seznamzastavek.h"

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
    void StahniSeznam(int &pocetVysledku, int cisloLinky, int cisloSpoje, QVector<SeznamZastavek> &docasnySeznamZastavek);
    QString vytvorCas(QString vstup);
    QString doplnNulu(int cislo, int pocetMist = 2);
    void Pripoj(QString adresa);
};

#endif // SQLPRACEROPID_H
