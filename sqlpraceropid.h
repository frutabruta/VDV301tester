#ifndef SQLPRACEROPID_H
#define SQLPRACEROPID_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSql>

#include "VDV301_Display/seznamzastavek.h"

class SqlPraceRopid
{
public:
    QSqlDatabase mojeDatabaze;
    SqlPraceRopid();
    bool vysledek;
    void Pripoj();
    void StahniSeznam(int &pocetVysledku, int cisloLinky, int cisloSpoje, SeznamZastavek *docasnySeznamZastavek);
    void VypisPole(SeznamZastavek *docasnySeznamZastavek, int &pocetZastavek);
    void TestDotaz(QString &textPoleObsah, int cisloporadi, int cislolinky, int cislospoje, SeznamZastavek *docasnySeznamZastavek, int pocetZastavek);
};

#endif // SQLPRACEROPID_H
