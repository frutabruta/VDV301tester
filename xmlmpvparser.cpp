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

QDomDocument XmlMpvParser::VytvorVystupniDokument(int max, QDomDocument xmlko)
{

    qDebug()<<"XmlMpvParser::VytvorVystupniDokument";
    //QDomDocument xmlko;
    QDomElement root=xmlko.createElement("wrapper");

    QByteArray navratovaHodnota="";
    QString vysledek="";
    QString nizkop="";
    QString BusSubmode="";
    QString dopravniProstredek="";
    QString language ="cs";
    QString destinationRef="1";

    QString mainMode="";
    QString subMode="";
    for (int i=0;i<max;i++)
    {
        mujPrestup[i].lin=mujPrestup[i].lin.number(10);
        dopravniProstredek="";
        QDomElement dConnectionMode = xmlko.createElement("ConnectionMode");
        if( mujPrestup[i].np==true)
        {
            nizkop="Accessible";
        }

        if (mujPrestup[i].t=="Bus")
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
        dConnection.appendChild(xmlko.createElement("StopRef")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode("&lt;StopProperty&gt;&lt;/StopProperty&gt;"));
        dConnection.appendChild(xmlko.createElement("ConnectionRef")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode("&lt;ConnectionProperty&gt;"+nizkop+"&lt;/ConnectionProperty&gt;"));

        dConnection.appendChild(xmlko.createElement("ConnectionType")).appendChild(xmlko.createTextNode("Interchange"));
        QDomElement dDisplayContent=xmlko.createElement("DisplayContent");
        dConnection.appendChild(dDisplayContent);
        dDisplayContent.appendChild(xmlko.createElement("DisplayContentRef")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode("2244"));

        QDomElement dLineInformation=xmlko.createElement("LineInformation");
        dDisplayContent.appendChild(dLineInformation);
        QDomElement dLineRef=xmlko.createElement("LineRef");
        dLineRef.appendChild(xmlko.createElement("Value"));
        dLineRef.firstChildElement("Value").appendChild(xmlko.createTextNode(mujPrestup[i].alias));
        dLineInformation.appendChild(dLineRef);
        QDomElement dLineName=xmlko.createElement("LineName");
        dLineName.appendChild(xmlko.createElement("Value"));
        dLineName.firstChildElement("Value").appendChild(xmlko.createTextNode(mujPrestup[i].alias));
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
        dDestinationName.firstChildElement("Value").appendChild(xmlko.createTextNode(mujPrestup[i].smer));
        dDestination.appendChild(dDestinationName);
        dDestinationName.appendChild(xmlko.createElement("Language"));
        dDestinationName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
        dConnection.appendChild(xmlko.createElement("Platform")).appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(mujPrestup[i].stan));
        dConnectionMode.appendChild(xmlko.createElement("PtMainMode")).appendChild(xmlko.createTextNode(mainMode));
        dConnectionMode.appendChild(xmlko.createElement(mainMode)).appendChild(xmlko.createTextNode(subMode));
        dConnection.appendChild(dConnectionMode);
        QDomElement dExpectedDepartureTime=xmlko.createElement("ExpectedDepatureTime"); //verze 1.0
        // QDomElement dExpectedDepartureTime=xmlko.createElement("ExpectedDepartureTime"); verze 2.0
        dExpectedDepartureTime.appendChild(xmlko.createElement("Value")).appendChild( xmlko.createTextNode(  mujPrestup[i].odj ));
        dConnection.appendChild(dExpectedDepartureTime);
        vysledek+="<Connection><StopRef><Value>&lt;StopProperty&gt;&lt;/StopProperty&gt;</Value></StopRef><ConnectionRef><Value>&lt;ConnectionProperty&gt;";
        vysledek+=nizkop;
        vysledek+="&lt;/ConnectionProperty&gt;</Value></ConnectionRef><ConnectionType>Interchange</ConnectionType><DisplayContent><DisplayContentRef><Value>2234</Value></DisplayContentRef><LineInformation><LineRef><Value>&lt;LineProperty&gt;Day&lt;/LineProperty&gt;</Value></LineRef><LineName><Value>";
        vysledek+=mujPrestup[i].alias;
        vysledek+="</Value><Language>cz</Language></LineName><LineShortName><Value>";
        vysledek+=mujPrestup[i].alias;
        vysledek+="</Value><Language>cz</Language></LineShortName><LineNumber><Value>";
        //vysledek+=mujPrestup[i].lin;
        vysledek+="1";
        vysledek+="</Value></LineNumber></LineInformation><Destination><DestinationRef><Value>&lt;DestinationProperty&gt;&lt;/DestinationProperty&gt;</Value></DestinationRef><DestinationName><Value>";
        vysledek+=mujPrestup[i].smer;
        vysledek+="</Value><Language>cz</Language></DestinationName></Destination></DisplayContent><Platform><Value>";
        vysledek+=mujPrestup[i].stan;
        vysledek+="</Value></Platform><ConnectionMode>";
        vysledek+=dopravniProstredek;
        vysledek+="</ConnectionMode><ExpectedDepatureTime><Value>";
        vysledek+=mujPrestup[i].odj;
        vysledek+="</Value></ExpectedDepatureTime></Connection>";
    }
    vlozitDoXml="";
    vlozitDoXml+=vysledek;
    navratovaHodnota+=vysledek;
    qDebug()<<"DOMverze";
    qDebug()<<xmlko.toString()<<"/n/n";
    qDebug()<<"QBytearrayVerze";
    qDebug()<<vlozitDoXml;
    return xmlko;

}

int XmlMpvParser::parsujDomDokument()
{
    qDebug()<<"parsujDomDokument";
    QDomElement root = vstupniDomDokument.firstChildElement();
    QDomNodeList nodes = root.elementsByTagName("t").at(0).toElement().elementsByTagName("o");
    int docasnyPocetPrestupu= nodes.count();
    for (int i=0; i<nodes.count();i++)
    {
        mujPrestup[i].stan=nodes.at(i).attributes().namedItem("stan").nodeValue();
        mujPrestup[i].lin=nodes.at(i).attributes().namedItem("lin").nodeValue();
        mujPrestup[i].alias=nodes.at(i).attributes().namedItem("alias").nodeValue();
        mujPrestup[i].spoj=nodes.at(i).attributes().namedItem("spoj").nodeValue().toInt();
        mujPrestup[i].smer=nodes.at(i).attributes().namedItem("smer").nodeValue();
        mujPrestup[i].odj=nodes.at(i).attributes().namedItem("odj").nodeValue();
        mujPrestup[i].zpoz=nodes.at(i).attributes().namedItem("zpoz").nodeValue().toInt();
        mujPrestup[i].sled=nodes.at(i).attributes().namedItem("sled").nodeValue().toInt();
        mujPrestup[i].np=nodes.at(i).attributes().namedItem("np").nodeValue().toInt();
        mujPrestup[i].nad=nodes.at(i).attributes().namedItem("nad").nodeValue().toInt();
        mujPrestup[i].t=nodes.at(i).attributes().namedItem("t").nodeValue();
        mujPrestup[i].dd=nodes.at(i).attributes().namedItem("dd").nodeValue().toInt();
        mujPrestup[i].smer_c=nodes.at(i).attributes().namedItem("smer_c").nodeValue().toInt();
        qDebug()<<mujPrestup[i].smer;
    }
    return docasnyPocetPrestupu;
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


