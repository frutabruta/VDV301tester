#include "xmlparser.h"
#include "seznamzastavek.h"
#include <QDebug>
#include <QMainWindow>




XmlParser::XmlParser()
{
}

void XmlParser::nactiXML(QByteArray vstup)
{
    QByteArray llooll = vstup;
    QString s = QString::fromUtf8(vstup);
    QString str =QString::fromUtf8(vstup);
    s = QString::fromUtf8(str.toLatin1());
    llooll=s.toUtf8();
    qInfo().noquote()<<"nactiOOOxml";
    dokument.setContent(s);
    QString blabla = dokument.toString();
    // qInfo().noquote()<<"XXX"<<blabla;
    qDebug()<<"\n\n XXX "<<s;

}

void XmlParser::VytvorSeznamZastavek(QVector<SeznamZastavek> &docasnySeznamZst, int *docasnyIndexZastavky, int *docasnyPocetZastavek)
{
    QDomElement root = dokument.firstChildElement();
    QDomNodeList nodes = root.elementsByTagName("StopPoint");
    qInfo()<<"testAVVCF";
    *docasnyPocetZastavek= nodes.count();
    *docasnyIndexZastavky=root.elementsByTagName("CurrentStopIndex").at(0).firstChildElement().text().toInt();
    for (int i=0; i<nodes.count();i++)
    {
        SeznamZastavek docasnaZastavka;
        int poradiZastavky=root.elementsByTagName("StopPoint").at(i).toElement().elementsByTagName("StopIndex").at(0).firstChildElement().text().toInt()-1;
        docasnaZastavka.StopName=root.elementsByTagName("StopPoint").at(i).toElement().elementsByTagName("StopName").at(0).firstChildElement().text();
        docasnaZastavka.LineName=root.elementsByTagName("DisplayContent").at(0).toElement().elementsByTagName("LineInformation").at(0).toElement().elementsByTagName("LineName").at(0).firstChildElement().text();
        docasnaZastavka.StopIndex=i;
        docasnaZastavka.DestinationName=root.elementsByTagName("DisplayContent").at(0).toElement().elementsByTagName("Destination").at(0).toElement().elementsByTagName("DestinationName").at(0).firstChildElement().text();
        qInfo()<< "22" << docasnaZastavka.StopName;
        docasnySeznamZst.push_back(docasnaZastavka);
    }
}




void XmlParser::Test()
{
    qInfo()<<"xmlParserTestPoint2";
}

