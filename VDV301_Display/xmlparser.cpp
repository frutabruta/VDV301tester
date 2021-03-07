#include "xmlparser.h"
#include "seznamzastavek.h"
#include <QDebug>
#include <QMainWindow>




XmlParser::XmlParser()
{
    qDebug()<<"XmlParser::XmlParser";
}

void XmlParser::nactiXML(QString vstup)
{
    qDebug()<<"XmlParser::nactiXML";

    dokument.setContent(vstup);
    QString blabla = dokument.toString();


}

int XmlParser::VytvorSeznamZastavek(QVector<SeznamZastavek> &docasnySeznamZst, int *docasnyIndexZastavky, int *docasnyPocetZastavek)
{
    docasnySeznamZst.clear();
    qDebug()<<"XmlParser::VytvorSeznamZastavek";
    QDomElement root = dokument.firstChildElement();
    qDebug()<<root.tagName();
    if (root.tagName()!="CustomerInformationService.GetAllDataResponse")
    {
        qDebug()<<"vadné XML";
        return 0;
    }
    QDomNodeList nodes = root.elementsByTagName("StopPoint");

    *docasnyPocetZastavek= nodes.count();
    *docasnyIndexZastavky=root.elementsByTagName("CurrentStopIndex").at(0).firstChildElement().text().toInt();
    for (int i=0; i<nodes.count();i++)
    {
        SeznamZastavek docasnaZastavka;
        int poradiZastavky=root.elementsByTagName("StopPoint").at(i).toElement().elementsByTagName("StopIndex").at(0).firstChildElement().text().toInt();
        docasnaZastavka.StopName=root.elementsByTagName("StopPoint").at(i).toElement().elementsByTagName("StopName").at(0).firstChildElement().text();
        docasnaZastavka.LineName=root.elementsByTagName("DisplayContent").at(0).toElement().elementsByTagName("LineInformation").at(0).toElement().elementsByTagName("LineName").at(0).firstChildElement().text();
        docasnaZastavka.StopIndex=i;
        docasnaZastavka.DestinationName=root.elementsByTagName("DisplayContent").at(0).toElement().elementsByTagName("Destination").at(0).toElement().elementsByTagName("DestinationName").at(0).firstChildElement().text();
        qInfo()<< "xml "<<QString::number(poradiZastavky)<<"i "<<QString::number(i) << docasnaZastavka.StopName;
        docasnySeznamZst.push_back(docasnaZastavka);
    }
    if (docasnySeznamZst.size() ==0)
    {
        qDebug()<<"zastavkyNebylyNacteny";
        return 0;
    }
    return 1;
}




void XmlParser::Test()
{
    qDebug()<<" XmlParser::Test";
    qInfo()<<"xmlParserTestPoint2";
}

