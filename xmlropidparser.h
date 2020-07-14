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
};

#endif // XMLROPIDPARSER_H
