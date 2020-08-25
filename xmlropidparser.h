#ifndef XMLROPIDPARSER_H
#define XMLROPIDPARSER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtXml>
#include "sqlpraceropid.h"

class XmlRopidParser
{
public:

    struct navrat
    {
    QString nazevSloupce="";
    QString obsah="";
    QString typ="";
    };
    XmlRopidParser();
    SqlPraceRopid ropidSQL;
    void otevriSoubor();
    //void databazeStart();

    int truncateTable(QString tabulka);
    int truncateAll();


    QString vytvorCas(QString vstup);
    void databazeStart(QString adresaServeru);


    QVector<navrat> polozkyKeVlozeni;
    QString slozInsert(QString nazevTabulky, QVector<navrat>);

    navrat inicializujPolozku(QString nazevSloupce, QString obsah, QString typ);
private:
    int vlozM(QDomElement koren);
    int vlozD(QDomElement koren);
    int vlozZ(QDomElement koren);
    int vlozS(QDomElement koren);
    int vlozL(QDomElement koren);
    int vlozP(QDomElement koren);
    int vlozDd(QDomElement koren);
    int vlozTv(QDomElement koren);
    int vlozT(QDomElement koren);
    int vlozX(QDomElement koren);
    QString overBoolean(QString vstup);
    QString overInteger(QString vstup);
    QString overString(QString vstup);
    int vlozTv2(QDomElement koren);
};

#endif // XMLROPIDPARSER_H
