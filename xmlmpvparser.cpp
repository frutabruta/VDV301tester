#include "xmlmpvparser.h"
#include <QDebug>
#include <QMainWindow>
#include "prestupmpv.h"
#include <QCoreApplication>


XmlMpvParser::XmlMpvParser()
{
}
XmlMpvParser::~XmlMpvParser()
{
}

void XmlMpvParser::naplnVstupDokument(QByteArray vstup)
{
    qDebug()<<"XmlMpvParser::naplnVstupDokument\n";
    QByteArray llooll = vstup;
    QString s = QString::fromUtf8(vstup);
    QString str =QString::fromUtf8(vstup);
    s = QString::fromUtf8(str.toLatin1());
    vstupniDomDokument.setContent(llooll);
}

QDomDocument XmlMpvParser::connections1_0( QVector<prestupMPV> lokPrestupy)
{

    qDebug()<<"XmlMpvParser::VytvorVystupniDokument";
    QDomDocument xmlko;
    QDomElement root=xmlko.createElement("wrapper");



    QString nizkop="";
    QString BusSubmode="";
    QString dopravniProstredek="";
    QString language ="cs";
    QString destinationRef="1";

    QString mainMode="";
    QString subMode="";
    for (int i=0;i<lokPrestupy.count();i++)
    {
        seznamPrestupu[i].lin=seznamPrestupu[i].lin.number(10);
        dopravniProstredek="";
        QDomElement dConnectionMode = xmlko.createElement("ConnectionMode");
        if( seznamPrestupu[i].np==true)
        {
            nizkop="Accessible";
        }

        if (seznamPrestupu[i].t=="Bus")
        {
            subMode="localBus";
            mainMode="BusSubmode";

            dopravniProstredek+="<PtMainMode>";
            dopravniProstredek+="BusSubmode";
            dopravniProstredek+="</PtMainMode>";
            dopravniProstredek+="<BusSubmode>";
            dopravniProstredek+="localBus";
            dopravniProstredek+="</BusSubmode>";
        }
        else
        {
            subMode="localTram";
            mainMode="TramSubmode";
            dopravniProstredek+="<PtMainMode>";
            dopravniProstredek+="TramSubmode";
            dopravniProstredek+="</PtMainMode>";
            dopravniProstredek+="<TramSubmode>";
            dopravniProstredek+="localTram";
            dopravniProstredek+="</TramSubmode>";
        }

        QDomElement dConnection=xmlko.createElement("Connection");
        xmlko.appendChild(dConnection);
        //dConnection.appendChild(xmlko.createElement("StopRef")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode("&lt;StopProperty&gt;&lt;/StopProperty&gt;"));
        //dConnection.appendChild(xmlko.createElement("ConnectionRef")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode("&lt;ConnectionProperty&gt;"+nizkop+"&lt;/ConnectionProperty&gt;"));

        dConnection.appendChild(xmlko.createElement("StopRef")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode("xx"));
        dConnection.appendChild(xmlko.createElement("ConnectionRef")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode("yy"));


        dConnection.appendChild(xmlko.createElement("ConnectionType")).appendChild(xmlko.createTextNode("Interchange"));
        QDomElement dDisplayContent=xmlko.createElement("DisplayContent");
        dConnection.appendChild(dDisplayContent);
        dDisplayContent.appendChild(xmlko.createElement("DisplayContentRef")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode("2244"));

        QDomElement dLineInformation=xmlko.createElement("LineInformation");
        dDisplayContent.appendChild(dLineInformation);
        QDomElement dLineRef=xmlko.createElement("LineRef");
        dLineRef.appendChild(xmlko.createElement("Value"));
        dLineRef.firstChildElement("Value").appendChild(xmlko.createTextNode(seznamPrestupu[i].alias));
        dLineInformation.appendChild(dLineRef);
        QDomElement dLineName=xmlko.createElement("LineName");
        dLineName.appendChild(xmlko.createElement("Value"));
        dLineName.firstChildElement("Value").appendChild(xmlko.createTextNode(seznamPrestupu[i].alias));
        dLineInformation.appendChild(dLineName);
        dLineName.appendChild(xmlko.createElement("Language"));
        dLineName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
        QDomElement dLineNumber=xmlko.createElement("LineNumber");
        dLineNumber.appendChild(xmlko.createElement("Value"));
        dLineNumber.firstChildElement("Value").appendChild(xmlko.createTextNode("1"));
        dLineInformation.appendChild(dLineNumber);
        QDomElement dDestination=xmlko.createElement("Destination");
        dDisplayContent.appendChild(dDestination);
        QDomElement dDestinationRef=xmlko.createElement("DestinationRef");
        dDestinationRef.appendChild(xmlko.createElement("Value"));
        dDestinationRef.firstChildElement("Value").appendChild(xmlko.createTextNode(destinationRef));
        dDestination.appendChild(dDestinationRef);

        QDomElement dDestinationName=xmlko.createElement("DestinationName");
        dDestinationName.appendChild(xmlko.createElement("Value"));
        dDestinationName.firstChildElement("Value").appendChild(xmlko.createTextNode(seznamPrestupu[i].smer));
        dDestination.appendChild(dDestinationName);
        dDestinationName.appendChild(xmlko.createElement("Language"));
        dDestinationName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
        dConnection.appendChild(xmlko.createElement("Platform")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(seznamPrestupu[i].stan));
        dConnectionMode.appendChild(xmlko.createElement("PtMainMode")).appendChild(xmlko.createTextNode(mainMode));
        dConnectionMode.appendChild(xmlko.createElement(mainMode)).appendChild(xmlko.createTextNode(subMode));
        dConnection.appendChild(dConnectionMode);
        QDomElement dExpectedDepartureTime=xmlko.createElement("ExpectedDepatureTime"); //verze 1.0
        // QDomElement dExpectedDepartureTime=xmlko.createElement("ExpectedDepartureTime"); verze 2.0
        dExpectedDepartureTime.appendChild(xmlko.createElement("Value")).appendChild( xmlko.createTextNode(  seznamPrestupu[i].odj ));
        dConnection.appendChild(dExpectedDepartureTime);

    }


    qDebug()<<"DOMverze";
  //  qDebug()<<xmlko.toString()<<"/n/n";

    return xmlko;

}

QDomDocument XmlMpvParser::connections2_2CZ1_0( QVector<prestupMPV> lokPrestupy)
{

    qDebug()<<"XmlMpvParser::generujXMLnew";
    QDomDocument xmlko;
    QDomElement root=xmlko.createElement("wrapper");



    QString BusSubmode="";
    QString dopravniProstredek="";
    QString language ="cs";
    QString destinationRef="1";

    QString mainMode="";
    QString subMode="";
    for (int i=0;i<lokPrestupy.count();i++)
    {
        prestupMPV aktualniPrestup=seznamPrestupu.at(i);
        aktualniPrestup.lin=aktualniPrestup.lin.number(10);

        QDomElement dConnectionMode = xmlko.createElement("ConnectionMode");


        if (aktualniPrestup.t=="Bus")
        {

            subMode="localBus";
            mainMode="BusSubmode";
        }
        if (aktualniPrestup.t=="RegBus")
        {

            subMode="regionalBus";
            mainMode="BusSubmode";
        }
        if (aktualniPrestup.t=="NBus")
        {

            subMode="nightBus";
            mainMode="BusSubmode";
        }
        if (aktualniPrestup.t=="Tram")
        {
            subMode="localTram";
            mainMode="TramSubmode";

        }
        if (aktualniPrestup.t=="NTram")
        {
            subMode="localTram";
            mainMode="TramSubmode";

        }









        QDomElement dConnection=xmlko.createElement("Connection");
        xmlko.appendChild(dConnection);
        //dConnection.appendChild(xmlko.createElement("StopRef")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode("&lt;StopProperty&gt;&lt;/StopProperty&gt;"));
        //dConnection.appendChild(xmlko.createElement("ConnectionRef")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode("&lt;ConnectionProperty&gt;"+nizkop+"&lt;/ConnectionProperty&gt;"));

        //dConnection.appendChild(xmlko.createElement("StopRef")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode("xx"));
       // dConnection.appendChild(xmlko.createElement("ConnectionRef")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode("yy"));

        if(aktualniPrestup.np==true)
        {
        dConnection.appendChild(xmlko.createElement("ConnectionProperty")).appendChild(xmlko.createTextNode("Accessible"));
        }
        dConnection.appendChild(xmlko.createElement("ConnectionType")).appendChild(xmlko.createTextNode("Interchange"));

        QDomElement dDisplayContent=xmlko.createElement("DisplayContent");
        dConnection.appendChild(dDisplayContent);
       // dDisplayContent.appendChild(xmlko.createElement("DisplayContentRef")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode("2244"));

        QDomElement dLineInformation=xmlko.createElement("LineInformation");
        dDisplayContent.appendChild(dLineInformation);
       /* QDomElement dLineRef=xmlko.createElement("LineRef");
        dLineRef.appendChild(xmlko.createElement("Value"));
        dLineRef.firstChildElement("Value").appendChild(xmlko.createTextNode(seznamPrestupu[i].alias));
        dLineInformation.appendChild(dLineRef);
        */
        QDomElement dLineName=xmlko.createElement("LineName");
        dLineName.appendChild(xmlko.createElement("Value"));
        dLineName.firstChildElement("Value").appendChild(xmlko.createTextNode(aktualniPrestup.alias));
        dLineInformation.appendChild(dLineName);
        dLineName.appendChild(xmlko.createElement("Language"));
        dLineName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
        QDomElement dLineNumber=xmlko.createElement("LineNumber");
        dLineNumber.appendChild(xmlko.createElement("Value"));
        dLineNumber.firstChildElement("Value").appendChild(xmlko.createTextNode("1"));
        dLineInformation.appendChild(dLineNumber);
        QDomElement dDestination=xmlko.createElement("Destination");
        dDisplayContent.appendChild(dDestination);
        /*QDomElement dDestinationRef=xmlko.createElement("DestinationRef");
        dDestinationRef.appendChild(xmlko.createElement("Value"));
        dDestinationRef.firstChildElement("Value").appendChild(xmlko.createTextNode(destinationRef));

        dDestination.appendChild(dDestinationRef); */

        QDomElement dDestinationName=xmlko.createElement("DestinationName");
        dDestinationName.appendChild(xmlko.createElement("Value"));
        dDestinationName.firstChildElement("Value").appendChild(xmlko.createTextNode(aktualniPrestup.smer));
        dDestination.appendChild(dDestinationName);

        dDestinationName.appendChild(xmlko.createElement("Language"));
        dDestinationName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));

        dConnection.appendChild(xmlko.createElement("Platform")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(aktualniPrestup.stan));

        dConnectionMode.appendChild(xmlko.createElement("PtMainMode")).appendChild(xmlko.createTextNode(mainMode));
        dConnectionMode.appendChild(xmlko.createElement(mainMode)).appendChild(xmlko.createTextNode(subMode));
        dConnection.appendChild(dConnectionMode);

       //  QDomElement dExpectedDepartureTime=xmlko.createElement("ExpectedDepatureTime"); verze 1.0
         QDomElement dExpectedDepartureTime=xmlko.createElement("ExpectedDepartureTime"); //verze 2.2CZ1.0
        dExpectedDepartureTime.appendChild(xmlko.createElement("Value")).appendChild( xmlko.createTextNode(  aktualniPrestup.odj ));
        dConnection.appendChild(dExpectedDepartureTime);

    }


    qDebug()<<"DOMverze";
  //  qDebug()<<xmlko.toString()<<"/n/n";

    return xmlko;

}

QVector<prestupMPV> XmlMpvParser::parsujDomDokument()
{
    qDebug()<<"parsujDomDokument";
    QDomElement root = vstupniDomDokument.firstChildElement();
    QDomNodeList nodes = root.elementsByTagName("t").at(0).toElement().elementsByTagName("o");
    seznamPrestupu.clear();
    for (int i=0; i<nodes.count();i++)
    {
        prestupMPV novy;
        novy.stan=nodes.at(i).attributes().namedItem("stan").nodeValue();
        novy.lin=nodes.at(i).attributes().namedItem("lin").nodeValue();
        novy.alias=nodes.at(i).attributes().namedItem("alias").nodeValue();
        novy.spoj=nodes.at(i).attributes().namedItem("spoj").nodeValue().toInt();
        novy.smer=nodes.at(i).attributes().namedItem("smer").nodeValue();
        novy.odj=nodes.at(i).attributes().namedItem("odj").nodeValue();
        novy.zpoz=nodes.at(i).attributes().namedItem("zpoz").nodeValue().toInt();
        novy.sled=nodes.at(i).attributes().namedItem("sled").nodeValue().toInt();
        if (nodes.at(i).attributes().namedItem("np").nodeValue()=="true")
        {novy.np=1;}
        else
        {novy.np=0;}
        novy.nad=nodes.at(i).attributes().namedItem("nad").nodeValue().toInt();
        novy.t=nodes.at(i).attributes().namedItem("t").nodeValue();
        novy.dd=nodes.at(i).attributes().namedItem("dd").nodeValue().toInt();
        novy.smer_c=nodes.at(i).attributes().namedItem("smer_c").nodeValue().toInt();
        seznamPrestupu.append(novy);
        qDebug()<<novy.smer;

    }
    return seznamPrestupu;
}


// zdroj https://stackoverflow.com/questions/7218851/making-an-http-get-under-qt
    //manager->get(QNetworkRequest(QUrl("http://www.mpvnet.cz/PID/x/21619?pocet=15&pz=true&t=true")));

void XmlMpvParser::StahniMpvXml(int cisloCis, QString Ids)
{
    qDebug()<<"XmlMpvParser::StahniMpvXml";
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(requestReceived(QNetworkReply*)));
    QString adresa = "http://www.mpvnet.cz/"+Ids+"/x/"+QString::number(cisloCis)+"?pocet=15&pz=true&t=true";
    qDebug()<<adresa;
    manager->get(QNetworkRequest(QUrl(adresa)));

}


QByteArray XmlMpvParser::requestReceived(QNetworkReply* replyoo)
{
    qDebug()<<"XmlMpvParser::requestReceived";
    QString replyText;
    QByteArray rawData = replyoo->readAll();
    QString textData(rawData);
    qDebug() << textData;
    this->stazenaData=rawData;
    emit stazeniHotovo();
    return rawData;
}


