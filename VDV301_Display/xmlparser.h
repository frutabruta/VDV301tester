#ifndef XMLPARSER_H
#define XMLPARSER_H
#define MAX_ZAST2 10

#include <QMainWindow>
#include <QObject>
#include <QtXml>
#include "seznamzastavek.h"
class XmlParser
{
public:
    XmlParser();
    void nactiXML(QByteArray vstup);
    int linka=0;
    QString cil="";
   // SeznamZastavek docasnySeznamZastavek[] ;
    SeznamZastavek* docasnySeznamZastavek = new SeznamZastavek[MAX_ZAST2];
    int VytvorSeznamZastavek(QVector<SeznamZastavek> &docasnySeznamZst, int* docasnyIndexZastavky, int* docasnyPocetZastavek);
    QDomDocument dokument;
    void Test();

    void nactiXML(QString vstup);
};




#endif // XMLPARSER_H
