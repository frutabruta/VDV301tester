#ifndef XMLROPIDPARSER_H
#define XMLROPIDPARSER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtXml>
#include "sqlpraceropid.h"

class XmlRopidParser: public QObject
{
     Q_OBJECT
public:

    struct navrat
    {
    QString nazevSloupce="";
    QString obsah="";
    QString typ="";
    };
    XmlRopidParser();
    SqlPraceRopid ropidSQL;
    void otevriSoubor(QString cesta);
    //void databazeStart();

    int truncateTable(QString tabulka);
    int truncateAll();

    QString vstupniXmlSouborCesta;


    int databazeStart(QString adresaServeru);


    QVector<navrat> polozkyKeVlozeni;


    navrat inicializujPolozku(QString nazevSloupce, QString obsah, QString typ);



    QVector<int> seznamDlouhychSpoju(QDomNodeList &dlouheSpoje);


    QDate platnostOd;
    QDate platnostDo;
    int vlozPlatnost(QDomElement koren, QDate &plOd, QDate &plDo);
signals:
    void odesliChybovouHlasku(QString chybovaHlaska);
private:
    int vlozM(QDomElement koren);
    int vlozD(QDomElement koren);
    int vlozZ(QDomElement koren);
    int vlozS(QDomElement koren);
    int vlozL(QDomElement koren);
    int vlozP(QDomElement koren);
    int vlozDd(QDomElement koren);
    int vlozT(QDomElement koren);
    int vlozX(QDomElement koren);
    int vlozO(QDomElement koren);
    QString overBoolean(QString vstup);
    QString overInteger(QString vstup);
    QString overString(QString vstup);
    QString slozInsert(QString nazevTabulky, QVector<navrat>);
    QString vytvorCas(QString vstup);
    int vlozTv(QDomElement koren);
    int vlozSpPo(QDomElement koren);
    int vlozCh(QDomElement koren);
    int vlozIds(QDomElement koren);
    int vlozPo(QDomElement koren);
    int vlozR(QDomElement koren);
    int vlozK(QDomElement koren);
    int vlozTy(QDomElement koren);
};

#endif // XMLROPIDPARSER_H
