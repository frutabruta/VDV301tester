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
    XmlRopidParser();
    SqlPraceRopid ropidSQL;
    void otevriSoubor();
    void databazeStart();
    int vlozM(QDomElement koren);
    int vlozD(QDomElement koren);
    int vlozZ(QDomElement koren);
    int truncateTable(QString tabulka);
    int truncateAll();
    int vlozS(QDomElement koren);
    int vlozL(QDomElement koren);
    int vlozP(QDomElement koren);
    int vlozDd(QDomElement koren);
    int vlozTv(QDomElement koren);
};

#endif // XMLROPIDPARSER_H
