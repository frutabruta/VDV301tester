#include "xmlparser.h"
#include "seznamzastavek.h"
#include <QDebug>
#include <QMainWindow>




XmlParser::XmlParser()
{
docasnySeznamZastavek[2].StopName="Ostrata,dolni zast.";
docasnySeznamZastavek[2].StopIndex=3;
docasnySeznamZastavek[2].StopName="741";



QFile file("/home/adam/bakalarka_support_doc/untitled.xml");
   if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
   {
       qInfo() << "Failed to open the file for reading.";
       //return -1;
   }
   else
   {
       // loading
       if(!dokument.setContent(&file))
       {
          qInfo()  << "Failed to load the file for reading.";
         //  return -1;
       }
       else
       {
           qInfo()<< "povedlo se";
       }
       file.close();
   }


   QDomElement root = dokument.firstChildElement();
   QDomNodeList nodes = root.elementsByTagName("StopPoint");
   qInfo()<<nodes.count();
   for (int i=0; i<nodes.count();i++)
   {
       QDomNode elm = nodes.at(3);

       QDomElement e = elm.toElement();
       QDomNodeList StopIndexy = e.elementsByTagName("StopIndex");
       QDomNode jedenStopIndex = StopIndexy.at(0);
       QDomElement vysledek = jedenStopIndex.toElement();
       QString aaoobb = vysledek.firstChild().nodeValue();

       QString vysledek2=root.elementsByTagName("StopPoint").at(i).toElement().elementsByTagName("StopIndex").at(0).firstChildElement().text();
       QString vysledek5=root.elementsByTagName("StopPoint").at(i).toElement().elementsByTagName("StopName").at(0).firstChildElement().text();

       QString vysledek3=root.elementsByTagName("DisplayContent").at(0).toElement().elementsByTagName("LineInformation").at(0).toElement().elementsByTagName("LineName").at(0).firstChildElement().text();
       QString vysledek4=root.elementsByTagName("DisplayContent").at(0).toElement().elementsByTagName("Destination").at(0).toElement().elementsByTagName("DestinationName").at(0).firstChildElement().text();
       qInfo()<< "tohle je obsah:" << vysledek2 <<vysledek3 <<vysledek4 <<vysledek5;
       qInfo()<<vysledek.nodeName();
   }



   //QDomNodeList odpoved = nodes.fi
}




void XmlParser::Test()
{
    qInfo()<<"xmlParserTestPoint2";
}

