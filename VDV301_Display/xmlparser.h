#ifndef XMLPARSER_H
#define XMLPARSER_H
#define MAX_ZAST 10

#include <QMainWindow>
#include <QObject>
#include <QtXml>
#include "seznamzastavek.h"
class XmlParser
{
public:
    XmlParser();
    int linka=0;
    QString cil="";
   // SeznamZastavek docasnySeznamZastavek[] ;
    SeznamZastavek* docasnySeznamZastavek = new SeznamZastavek[MAX_ZAST];
    QDomDocument dokument;
    void Test();
};




#endif // XMLPARSER_H
