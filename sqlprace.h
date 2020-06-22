#ifndef SQLPRACE_H
#define SQLPRACE_H
#include <QCoreApplication>
#include <QtSql>


class SQLprace
{
public:
    SQLprace();
    bool vysledek;
    QSqlDatabase mojeDatabaze;
    void Pripoj();
    void TestDotaz(QString &textPoleObsah, int cisloporadi, int cislolinky, int cislospoje);
    void zjistiPocet (int &pocetvysledku, int cisloporadi, int cislolinky, int cislospoje);
};

#endif // SQLPRACE_H
