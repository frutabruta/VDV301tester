#ifndef SQLPRACE_H
#define SQLPRACE_H
#include <QCoreApplication>
#include <QtSql>
#include "VDV301_Display/seznamzastavek.h"

class SQLprace
{
public:
    SQLprace();
    bool vysledek;
    QSqlDatabase mojeDatabaze;
    void Pripoj();
    //void TestDotaz(QString &textPoleObsah, int cisloporadi, int cislolinky, int cislospoje);
    void StahniSeznam(int &pocetVysledku, int cisloLinky, int cisloSpoje, SeznamZastavek *docasnySeznamZastavek);
    void zjistiPocet (int &pocetvysledku, int cisloporadi, int cislolinky, int cislospoje);
    void VypisPole(SeznamZastavek *docasnySeznamZastavek, int &pocetZastavek);
    void TestDotaz(QString &textPoleObsah, int cisloporadi, int cislolinky, int cislospoje, SeznamZastavek *docasnySeznamZastavek, int pocetZastavek);
};

#endif // SQLPRACE_H
