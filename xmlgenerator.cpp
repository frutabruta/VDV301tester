#include "xmlgenerator.h"
#include "xmlgenerator.h"
#include <QTime>
#include "cestaudaje.h"
#include "VDV301_Display/seznamzastavek.h"
#include "cestaudaje.h"
#include <QCoreApplication>
#include <QtDebug>
#include <QtXml>
#include "prestupmpv.h"
#include "xmlmpvparser.h"
#include "struktury/pasmo.h"

xmlGenerator::xmlGenerator(QWidget *parent) : QMainWindow(parent)
{
    qDebug()<<"xmlGenerator::xmlGenerator";
    QDomDocument dokument;
}



QString xmlGenerator::AllData1_0(  QVector <SeznamZastavek> docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections, CestaUdaje stav )
{
    int poradi=stav.indexAktZastavky;
    SeznamZastavek cilovaZastavka=docasnySeznamZastavek.last();
    qDebug()<<" xmlGenerator::AllData1_0 ";

    // QString testVysledek="<TBL cas=\"2019-08-10T23:12:41\" ver=\"1.0.7145.21217\" text=\"Ověřovací provoz. Bez záruky.\"><t id=\"62887\" stan=\"A,B,M1,M2\" zast=\"Národní třída\"><o stan=\"A\" lin=\"9\" alias=\"9\" spoj=\"77\" smer=\"Praha,Spojovací\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27891\"/><o stan=\"B\" lin=\"18\" alias=\"18\" spoj=\"15\" smer=\"Praha,Nádraží Podbaba\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"63414\"/><o stan=\"A\" lin=\"22\" alias=\"22\" spoj=\"273\" smer=\"Praha,Nádraží Strašnice\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"57696\"/><o stan=\"M1\" lin=\"B\" alias=\"B\" spoj=\"32\" smer=\"Praha,Zličín\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Metro\" dd=\"1\" smer_c=\"28037\"/><o stan=\"B\" lin=\"22\" alias=\"22\" spoj=\"161\" smer=\"Praha,Bílá Hora\" odj=\"2019-08-10T23:17:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27908\"/></t></TBL>";
    qDebug()<<"  ";
    QString language="cz";
    QString deflanguage="cz";
    QString lineNumber=QByteArray::number(docasLinka);
    QString lineName=lineNumber.right(3);
    QString vehicleref="33";
    int currentStopIndex= poradi;
    QString routeDeviation="onroute";
    QString vehicleStopRequested="0";
    QString exitSide="right";
    QString tripRef="3";
    QString displayContentRef="1234";
    QString destinationName=docasnySeznamZastavek[poradi].DestinationName;
    qDebug()<<"nazev cile2"<<destinationName;

    QDomDocument xmlko;
    QDomProcessingInstruction dHlavicka=xmlko.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
    xmlko.appendChild(dHlavicka);
    QDomElement dCustomerInformationService=xmlko.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlko.createElement("AllData");
    xmlko.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);


    dAllData.appendChild(TimeStampTag1_0(xmlko));

    QDomElement dVehicleRef=xmlko.createElement("VehicleRef");
    dVehicleRef.appendChild(xmlko.createElement("Value"));
    dVehicleRef.firstChildElement("Value").appendChild(xmlko.createTextNode(vehicleref));
    dAllData.appendChild(dVehicleRef);
    QDomElement dDefaultLanguage=xmlko.createElement("DefaultLanguage");
    dDefaultLanguage.appendChild(xmlko.createElement("Value"));
    dDefaultLanguage.firstChildElement("Value").appendChild(xmlko.createTextNode(deflanguage));
    dAllData.appendChild(dDefaultLanguage);
    QDomElement dTripInformation=xmlko.createElement("TripInformation");
    dAllData.appendChild(dTripInformation);

    QDomElement dTripRef=xmlko.createElement("TripRef");
    dTripRef.appendChild(xmlko.createElement("Value"));
    dTripRef.firstChildElement("Value").appendChild(xmlko.createTextNode(tripRef));
    dTripInformation.appendChild(dTripRef);

    //stop sequence
    dTripInformation.appendChild(StopSequence1_0(xmlko,docasnySeznamZastavek,language,currentStopIndex,Connections,stav));
    //dTripInformation.appendChild(dStopSequence);


    QDomElement dLocationState=xmlko.createElement("LocationState");
    dLocationState.appendChild(xmlko.createTextNode( locationState));
    dTripInformation.appendChild(dLocationState);

    QDomElement dCurrentStopIndex=xmlko.createElement("CurrentStopIndex");
    dCurrentStopIndex.appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(QString::number(currentStopIndex)));
    dAllData.appendChild(dCurrentStopIndex);
    QDomElement dRouteDeviation = xmlko.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlko.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);
    QDomElement dDoorState = xmlko.createElement("DoorState");
    dDoorState.appendChild(xmlko.createTextNode(doorState));
    dAllData.appendChild(dDoorState);
    QDomElement dVehicleStopRequested=xmlko.createElement("VehicleStopRequested");
    dVehicleStopRequested.appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(vehicleStopRequested));
    dAllData.appendChild(dVehicleStopRequested);
    QDomElement dExitSide = xmlko.createElement("ExitSide");
    dExitSide.appendChild(xmlko.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);
    /*telo="";
    telo+=xmlko;*/
    return xmlko.toString();
}

QString xmlGenerator::devStatus()
{
    qDebug()<<" xmlGenerator::devStatus ";
    qDebug()<<"  ";
    QString  pozadavek ="";
    QString  hlavicka="";
    QString  telo="";
    QString  deviceState="running";
    QString  TgetDeviceStatusResponse="";
    QString  TgetDeviceStatusResponseData="";
    QString  TtimeStamp="";
    QString  TdeviceState="";

    TtimeStamp+="<TimeStamp>"+this->createTimestamp()+"</TimeStamp>";
    TdeviceState+="<DeviceState>"+deviceState+"</DeviceState>";
    TgetDeviceStatusResponseData+="<DeviceManagementService.GetDeviceStatusResponseData>"+TtimeStamp+TdeviceState+"</DeviceManagementService.GetDeviceStatusResponseData>";
    TgetDeviceStatusResponse+="<DeviceManagementService.GetDeviceStatusResponse>"+TgetDeviceStatusResponseData+"</DeviceManagementService.GetDeviceStatusResponse>";
    hlavicka+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    hlavicka+=("Content-Type: application/xml\r\n");
    hlavicka+=("Connection: close\r\n");
    hlavicka+=("Pragma: no-cache\r\n");
    hlavicka+=("\r\n");
    telo+=("<?xml version=\"1.0\" encoding=\"UTF-8\"?>  ")+TgetDeviceStatusResponse;
    pozadavek=hlavicka+telo;
    return pozadavek;
}

QString xmlGenerator::createTimestamp()
{
    qDebug()<<" xmlGenerator::createTimestamp  ";
    QDateTime casovaZnacka = QDateTime::currentDateTime();
    QString casnaformatovanoString= casovaZnacka.toString("yyyy-MM-ddThh:mm:ss");

    /*
     QByteArray dopole="";
     dopole.append(casnaformatovanoString);
    */
    qDebug()<<casnaformatovanoString;
    return casnaformatovanoString;
}


QString xmlGenerator::AllData2_2CZ1_0(int poradi, QVector <SeznamZastavek> docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections )
{
    qDebug()<<"xmlGenerator::AllData2_2CZ1_0";

    SeznamZastavek cilovaZastavka=docasnySeznamZastavek.last();

    // QString testVysledek="<TBL cas=\"2019-08-10T23:12:41\" ver=\"1.0.7145.21217\" text=\"Ověřovací provoz. Bez záruky.\"><t id=\"62887\" stan=\"A,B,M1,M2\" zast=\"Národní třída\"><o stan=\"A\" lin=\"9\" alias=\"9\" spoj=\"77\" smer=\"Praha,Spojovací\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27891\"/><o stan=\"B\" lin=\"18\" alias=\"18\" spoj=\"15\" smer=\"Praha,Nádraží Podbaba\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"63414\"/><o stan=\"A\" lin=\"22\" alias=\"22\" spoj=\"273\" smer=\"Praha,Nádraží Strašnice\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"57696\"/><o stan=\"M1\" lin=\"B\" alias=\"B\" spoj=\"32\" smer=\"Praha,Zličín\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Metro\" dd=\"1\" smer_c=\"28037\"/><o stan=\"B\" lin=\"22\" alias=\"22\" spoj=\"161\" smer=\"Praha,Bílá Hora\" odj=\"2019-08-10T23:17:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27908\"/></t></TBL>";
    qDebug()<<"  ";
    QString language="cz";
    QString deflanguage="cz";
    QString lineNumber=QByteArray::number(docasLinka);
    QString lineName=lineNumber.right(3);
    QString vehicleref="33";
    int currentStopIndex= poradi;
    QString routeDeviation="onroute";
    QString vehicleStopRequested="0";
    QString exitSide="right";
    QString tripRef="15";
    QString displayContentRef="1234";
    QString destinationName=docasnySeznamZastavek[poradi].DestinationName;
    qDebug()<<"nazev cile2"<<destinationName;

    QDomDocument xmlko;
    QDomProcessingInstruction dHlavicka=xmlko.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
    xmlko.appendChild(dHlavicka);
    QDomElement dCustomerInformationService=xmlko.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlko.createElement("AllData");
    xmlko.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);


    dAllData.appendChild(TimeStampTag1_0(xmlko));

    QDomElement dVehicleRef=xmlko.createElement("VehicleRef");
    dVehicleRef.appendChild(xmlko.createElement("Value"));
    dVehicleRef.firstChildElement("Value").appendChild(xmlko.createTextNode(vehicleref));
    dAllData.appendChild(dVehicleRef);
    QDomElement dDefaultLanguage=xmlko.createElement("DefaultLanguage");
    dDefaultLanguage.appendChild(xmlko.createElement("Value"));
    dDefaultLanguage.firstChildElement("Value").appendChild(xmlko.createTextNode(deflanguage));
    dAllData.appendChild(dDefaultLanguage);
    QDomElement dTripInformation=xmlko.createElement("TripInformation");
    dAllData.appendChild(dTripInformation);

    QDomElement dTripRef=xmlko.createElement("TripRef");
    dTripRef.appendChild(xmlko.createElement("Value"));
    dTripRef.firstChildElement("Value").appendChild(xmlko.createTextNode(tripRef));
    dTripInformation.appendChild(dTripRef);

    //stop sequence
    dTripInformation.appendChild(StopSequence2_2CZ1_0(xmlko,docasnySeznamZastavek,language,currentStopIndex,Connections));
    //dTripInformation.appendChild(dStopSequence);


    QDomElement dLocationState=xmlko.createElement("LocationState");
    dLocationState.appendChild(xmlko.createTextNode( locationState));
    dTripInformation.appendChild(dLocationState);

    QDomElement dCurrentStopIndex=xmlko.createElement("CurrentStopIndex");
    dCurrentStopIndex.appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(QString::number(currentStopIndex)));
    dAllData.appendChild(dCurrentStopIndex);
    QDomElement dRouteDeviation = xmlko.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlko.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);
    QDomElement dDoorState = xmlko.createElement("DoorState");
    dDoorState.appendChild(xmlko.createTextNode(doorState));
    dAllData.appendChild(dDoorState);
    QDomElement dVehicleStopRequested=xmlko.createElement("VehicleStopRequested");
    dVehicleStopRequested.appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(vehicleStopRequested));
    dAllData.appendChild(dVehicleStopRequested);
    QDomElement dExitSide = xmlko.createElement("ExitSide");
    dExitSide.appendChild(xmlko.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);
    /*telo="";
    telo+=xmlko;*/
    return xmlko.toString();
}



QString xmlGenerator::CurrentDisplayContent1_0(int poradi, QVector <SeznamZastavek> docasnySeznamZastavek, CestaUdaje stav )
{
    qDebug()<<"xmlGenerator::CurrentDisplayContent1_0";
    SeznamZastavek aktualniZastavka=docasnySeznamZastavek[poradi];

    qDebug()<<"  ";
    QString  language="cz";
    QString  lineNumber=aktualniZastavka.LineNumber;
    QString  lineName=lineNumber.right(3);
    int  currentStopIndex= poradi;




    QString destinationName=docasnySeznamZastavek[poradi].DestinationName;
    QString destinationRef=QString::number(docasnySeznamZastavek[poradi].DestinationCis);
    QDomDocument xmlko;
    QDomProcessingInstruction dHlavicka=xmlko.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
    xmlko.appendChild(dHlavicka);

    QDomElement dCustomerInformationService=xmlko.createElement("CustomerInformationService.GetCurrentDisplayContentResponse");
    QDomElement dCurrentDisplayContentData=xmlko.createElement("CurrentDisplayContentData");


    dCurrentDisplayContentData.appendChild(TimeStampTag1_0(xmlko));


    dCurrentDisplayContentData.appendChild(DisplayContent1_0("CurrentDisplayContent",xmlko,docasnySeznamZastavek,lineNumber,lineName,language,destinationRef,destinationName,stav));
    dCustomerInformationService.appendChild(dCurrentDisplayContentData);
    xmlko.appendChild(dCustomerInformationService);






    return xmlko.toString();
}


QDomElement xmlGenerator::StopSequence1_0(QDomDocument xmlko,QVector<SeznamZastavek> docasnySeznamZastavek,QString language, int currentStopIndex, QDomDocument Connections,CestaUdaje stav)
{
    QDomElement dStopSequence=xmlko.createElement("StopSequence");
    //dTripInformation.appendChild(dStopSequence);
    for (int i=0 ; i<docasnySeznamZastavek.count();i++)
    {
        SeznamZastavek aktZastavka=docasnySeznamZastavek.at(i);

        dStopSequence.appendChild(stopPoint1_0(docasnySeznamZastavek,i,Connections,language,currentStopIndex,stav));

    }
    return dStopSequence;
}

QDomElement xmlGenerator::StopSequence2_2CZ1_0(QDomDocument xmlko,QVector<SeznamZastavek> docasnySeznamZastavek,QString language, int currentStopIndex, QDomDocument Connections)
{
    QDomElement dStopSequence=xmlko.createElement("StopSequence");
    //dTripInformation.appendChild(dStopSequence);
    for (int i=0 ; i<docasnySeznamZastavek.count();i++)
    {
        SeznamZastavek aktZastavka=docasnySeznamZastavek.at(i);

        dStopSequence.appendChild(stopPoint2_2CZ1_0(docasnySeznamZastavek,i,Connections,language,currentStopIndex));

    }
    return dStopSequence;
}


QDomElement xmlGenerator::stopPoint1_0(QVector<SeznamZastavek> docasnySeznamZastavek,int indexZpracZastavky, QDomDocument Connections, QString language,int currentStopIndex,CestaUdaje stav)
{
    SeznamZastavek aktZastavka=docasnySeznamZastavek.at(indexZpracZastavky);
    QDomDocument xmlko;
    //SeznamZastavek prochazenaZastavka=docasnySeznamZastavek.at(i);
    QByteArray cCurrentStopIndex=QByteArray::number(aktZastavka.StopIndex);
    QString cStopName= aktZastavka.StopName;
    QString xDestinationName= aktZastavka.DestinationName;
    QString xDestinationCis=QString::number(aktZastavka.DestinationCis);
    //STOP
    QDomElement dStopPoint=xmlko.createElement("StopPoint");

    QDomElement dStopIndex=xmlko.createElement("StopIndex");
    dStopIndex.appendChild(xmlko.createElement("Value"));
    dStopIndex.firstChildElement("Value").appendChild(xmlko.createTextNode(cCurrentStopIndex ));
    dStopPoint.appendChild(dStopIndex);

    dStopPoint.appendChild(ref("StopRef",QString::number(aktZastavka.cisloCis)));

    QDomElement dStopName=internationalTextType("StopName",cStopName,language);
    dStopPoint.appendChild(dStopName);



    QDomElement dDisplayContent=DisplayContent1_0("DisplayContent",xmlko,docasnySeznamZastavek, aktZastavka.LineNumber ,aktZastavka.LineName,language,xDestinationCis,aktZastavka.DestinationName, stav);
    dStopPoint.appendChild(dDisplayContent);



    QVector<QDomElement> domPasma=FareZoneInformationStructure1_0(aktZastavka.seznamPasem,language);
    for (int i=0;i<domPasma.length();i++)
    {
        dStopPoint.appendChild(domPasma.at(i));
    }





    if (cCurrentStopIndex.toInt()==currentStopIndex)
    {
        qDebug()<<" prestupy "<<Connections.toString();

        QDomNodeList seznamPrestupu = Connections.elementsByTagName("Connection");
        for (int j=0;j<seznamPrestupu.count();j++)
        {
            dStopPoint.appendChild(seznamPrestupu.at(indexZpracZastavky).toElement() );
        }
    }
    return dStopPoint;
}

QDomElement xmlGenerator::stopPoint2_2CZ1_0(QVector<SeznamZastavek> docasnySeznamZastavek,int indexZpracZastavky, QDomDocument Connections, QString language,int currentStopIndex)
{
    SeznamZastavek aktZastavka=docasnySeznamZastavek.at(indexZpracZastavky);
    QDomDocument xmlko;
    //SeznamZastavek prochazenaZastavka=docasnySeznamZastavek.at(i);
    QByteArray cCurrentStopIndex=QByteArray::number(aktZastavka.StopIndex);
    QString cStopName= aktZastavka.StopName;
    QString xDestinationName= aktZastavka.DestinationName;
    QString xDestinationCis=QString::number(aktZastavka.DestinationCis);
    //STOP
    QDomElement dStopPoint=xmlko.createElement("StopPoint");

    QDomElement dStopIndex=xmlko.createElement("StopIndex");
    dStopIndex.appendChild(xmlko.createElement("Value"));
    dStopIndex.firstChildElement("Value").appendChild(xmlko.createTextNode(cCurrentStopIndex ));
    dStopPoint.appendChild(dStopIndex);

    dStopPoint.appendChild(ref("StopRef",QString::number(aktZastavka.cisloCis)));

    QDomElement dStopName=internationalTextType("StopName",cStopName,language);
    dStopPoint.appendChild(dStopName);

    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.naZnameni,"RequestStop"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.prestupLetadlo ,"Air"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.prestupPrivoz ,"Ferry"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.prestupMetroA ,"UndergroundA"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.prestupMetroB ,"UndergroundB"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.prestupMetroC ,"UndergroundC"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.prestupMetroD ,"UndergroundD"));
    /*
nedodelane priznaky:
            <xs:enumeration value="Bus"/>
            <xs:enumeration value="Funicular"/>
            <xs:enumeration value="Night"/>
            <xs:enumeration value="ReplacementService"/>
            <xs:enumeration value="ReplacementStop"/>
            <xs:enumeration value="RequestStop"/>
            <xs:enumeration value="Telecabin"/>
            <xs:enumeration value="Train"/>
            <xs:enumeration value="Tram"/>
            <xs:enumeration value="Trolleybus"/>
            <xs:enumeration value="UndergroundA"/>
            <xs:enumeration value="UndergroundB"/>
            <xs:enumeration value="UndergroundC"/>
            <xs:enumeration value="UndergroundD"/>
            */

    QDomElement dDisplayContent=DisplayContent2_2CZ1_0("DisplayContent",docasnySeznamZastavek,language,indexZpracZastavky,currentStopIndex);

    dStopPoint.appendChild(dDisplayContent);



    QVector<QDomElement> domPasma=FareZoneInformationStructure2_2CZ1_0(aktZastavka.seznamPasem,language);
    for (int i=0;i<domPasma.length();i++)
    {
        dStopPoint.appendChild(domPasma.at(i));
    }





    if (cCurrentStopIndex.toInt()==currentStopIndex)
    {
        qDebug()<<" prestupy "<<Connections.toString();

        QDomNodeList seznamPrestupu = Connections.elementsByTagName("Connection");
        for (int j=0;j<seznamPrestupu.count();j++)
        {
            dStopPoint.appendChild(seznamPrestupu.at(indexZpracZastavky).toElement() );
        }
    }
    return dStopPoint;
}

QDomElement xmlGenerator::DisplayContent1_0(QString tagName,QDomDocument xmlko,QVector<SeznamZastavek> docasnySeznamZastavek, QString lineNumber, QString lineName, QString language, QString destinationRef, QString destinationName,CestaUdaje stav)
{
    int indexAktZastavky=stav.indexAktZastavky;
    bool pridatPristi=true;
    QDomElement dDisplayContent=xmlko.createElement(tagName);

    dDisplayContent.appendChild(ref("DisplayContentRef","1234"));

    QDomElement dLineInformation=xmlko.createElement("LineInformation");
    dDisplayContent.appendChild(dLineInformation);

    dLineInformation.appendChild(ref("LineRef",lineNumber));


    QDomElement dLineName=internationalTextType("LineName",lineName,language);
    dLineInformation.appendChild(dLineName);

    QDomElement dLineNumber=xmlko.createElement("LineNumber");
    dLineNumber.appendChild(xmlko.createElement("Value"));
    dLineNumber.firstChildElement("Value").appendChild(xmlko.createTextNode(lineNumber));
    dLineInformation.appendChild(dLineNumber);

    QDomElement dDestination=xmlko.createElement("Destination");


    dDestination.appendChild(ref("DestinationRef",destinationRef));


    QDomElement dDestinationName=internationalTextType("DestinationName",destinationName,language);
    dDestination.appendChild(dDestinationName);

    dDisplayContent.appendChild(dDestination);

    //badabum


    if(stav.locationState=="AtStop")
    {
        if ((pridatPristi==true)&&((indexAktZastavky+1)<docasnySeznamZastavek.count()))
        {
            SeznamZastavek pristi=docasnySeznamZastavek.at(indexAktZastavky+1);
            if (pristi.nacestna==0)
            {
                dDisplayContent.appendChild(ViaPoint1_0(xmlko,pristi,language));
            }

        }

        for (int j=indexAktZastavky+1;j<docasnySeznamZastavek.count() ;j++)
        {
            //qDebug()<<"Projizdim nacesty "<<docasnySeznamZastavek.at(j).nacestna<<" "<<docasnySeznamZastavek.at(j).StopName ;
            if(docasnySeznamZastavek.at(j).nacestna == 1)
            {
                SeznamZastavek nacestnaZastavka=docasnySeznamZastavek.at(j);
                dDisplayContent.appendChild(ViaPoint1_0(xmlko,nacestnaZastavka,language));
            }
        }
    }
    else
    {
        if ((pridatPristi==true)&&((indexAktZastavky)<docasnySeznamZastavek.count()))
        {
            SeznamZastavek pristi=docasnySeznamZastavek.at(indexAktZastavky);
            if (pristi.nacestna==0)
            {
                dDisplayContent.appendChild(ViaPoint1_0(xmlko,pristi,language));
            }

        }

        for (int j=indexAktZastavky;j<docasnySeznamZastavek.count() ;j++)
        {
            //qDebug()<<"Projizdim nacesty "<<docasnySeznamZastavek.at(j).nacestna<<" "<<docasnySeznamZastavek.at(j).StopName ;
            if(docasnySeznamZastavek.at(j).nacestna == 1)
            {
                SeznamZastavek nacestnaZastavka=docasnySeznamZastavek.at(j);
                dDisplayContent.appendChild(ViaPoint1_0(xmlko,nacestnaZastavka,language));
            }
        }
    }


    return dDisplayContent;
}

QDomElement xmlGenerator::DisplayContent2_2CZ1_0(QString tagName,QVector<SeznamZastavek> docasnySeznamZastavek, QString language,int iteracniIndex,int currentStopIndex)
{
    QDomDocument xmlko;
    SeznamZastavek aktZastavka=docasnySeznamZastavek.at(iteracniIndex);
    QString lineNumber=aktZastavka.LineNumber;
    QString lineName=aktZastavka.LineName;
    QString destinationName=aktZastavka.DestinationName;


    bool pridatPristi=true;
    QDomElement dDisplayContent=xmlko.createElement(tagName);

    dDisplayContent.appendChild(ref("DisplayContentRef","1234"));

    QDomElement dLineInformation=xmlko.createElement("LineInformation");
    dDisplayContent.appendChild(dLineInformation);

    //dLineInformation.appendChild(ref("LineRef",lineNumber));


    QDomElement dLineName=internationalTextType("LineName",lineName,language);
    dLineInformation.appendChild(dLineName);

    QDomElement dLineNumber=xmlko.createElement("LineNumber");
    dLineNumber.appendChild(xmlko.createElement("Value"));
    dLineNumber.firstChildElement("Value").appendChild(xmlko.createTextNode(lineNumber));
    dLineInformation.appendChild(dLineNumber);

    QDomElement dDestination=xmlko.createElement("Destination");

    dDestination.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.naZnameni,"RequestStop"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.prestupLetadlo ,"Air"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.prestupPrivoz ,"Ferry"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.prestupMetroA ,"UndergroundA"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.prestupMetroB ,"UndergroundB"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.prestupMetroC ,"UndergroundC"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.prestupMetroD ,"UndergroundD"));
    /*
nedodelane priznaky:
            <xs:enumeration value="Bus"/>
            <xs:enumeration value="Funicular"/>
            <xs:enumeration value="Night"/>
            <xs:enumeration value="ReplacementService"/>
            <xs:enumeration value="ReplacementStop"/>
            <xs:enumeration value="RequestStop"/>
            <xs:enumeration value="Telecabin"/>
            <xs:enumeration value="Train"/>
            <xs:enumeration value="Tram"/>
            <xs:enumeration value="Trolleybus"/>
            <xs:enumeration value="UndergroundA"/>
            <xs:enumeration value="UndergroundB"/>
            <xs:enumeration value="UndergroundC"/>
            <xs:enumeration value="UndergroundD"/>
            */
    //dDestination.appendChild(ref("DestinationRef",destinationRef));


    QDomElement dDestinationName=internationalTextType("DestinationName",destinationName,language);
    dDestination.appendChild(dDestinationName);

    dDisplayContent.appendChild(dDestination);

    //badabum
    if ((pridatPristi==true)&&((currentStopIndex+1)<docasnySeznamZastavek.count()))
    {
        SeznamZastavek pristi=docasnySeznamZastavek.at(currentStopIndex+1);
        if (pristi.nacestna==0)
        {
            dDisplayContent.appendChild(ViaPoint2_2CZ1_0(xmlko,pristi,language));
        }

    }

    for (int j=currentStopIndex+1;j<docasnySeznamZastavek.count() ;j++)
    {
        //qDebug()<<"Projizdim nacesty "<<docasnySeznamZastavek.at(j).nacestna<<" "<<docasnySeznamZastavek.at(j).StopName ;
        if(docasnySeznamZastavek.at(j).nacestna == 1)
        {
            SeznamZastavek nacestnaZastavka=docasnySeznamZastavek.at(j);
            dDisplayContent.appendChild(ViaPoint2_2CZ1_0(xmlko,nacestnaZastavka,language));
        }
    }


    return dDisplayContent;
}

QDomElement xmlGenerator::ViaPoint1_0(QDomDocument xmlko, SeznamZastavek nacestnaZastavka,QString language)
{
    // qDebug()<<"nacestaNalezena";


    QDomElement dViaPoint=xmlko.createElement("ViaPoint");


    dViaPoint.appendChild(ref("ViaPointRef",QString::number(nacestnaZastavka.cisloCis)));

    QDomElement dPlaceName=xmlko.createElement("PlaceName");
    dPlaceName.appendChild(xmlko.createElement("Value"));
    dPlaceName.firstChildElement("Value").appendChild(xmlko.createTextNode(nacestnaZastavka.StopName));
    dPlaceName.appendChild(xmlko.createElement("Language"));
    dPlaceName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
    dViaPoint.appendChild(dPlaceName);

    //qDebug()<<"nacestna zastavka "<<nacestnaZastavka.StopName<<""<<nacestnaZastavka.cisloCis;
    return dViaPoint;
}

QDomElement xmlGenerator::ViaPoint2_2CZ1_0(QDomDocument xmlko, SeznamZastavek nacestnaZastavka,QString language)
{
    //qDebug()<<"nacestaNalezena";


    QDomElement dViaPoint=xmlko.createElement("ViaPoint");


    //dViaPoint.appendChild(ref("ViaPointRef",QString::number(nacestnaZastavka.cisloCis)));

    dViaPoint.appendChild(xxxProperty2_2CZ1_0("ViaPointProperty",nacestnaZastavka.naZnameni,"RequestStop"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0("ViaPointProperty",nacestnaZastavka.prestupLetadlo ,"Air"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0("ViaPointProperty",nacestnaZastavka.prestupPrivoz ,"Ferry"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0("ViaPointProperty",nacestnaZastavka.prestupMetroA ,"UndergroundA"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0("ViaPointProperty",nacestnaZastavka.prestupMetroB ,"UndergroundB"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0("ViaPointProperty",nacestnaZastavka.prestupMetroC ,"UndergroundC"));
    dViaPoint.appendChild(xxxProperty2_2CZ1_0("ViaPointProperty",nacestnaZastavka.prestupMetroD ,"UndergroundD"));
    /*
nedodelane priznaky:
            <xs:enumeration value="Bus"/>
            <xs:enumeration value="Funicular"/>
            <xs:enumeration value="Night"/>
            <xs:enumeration value="ReplacementService"/>
            <xs:enumeration value="ReplacementStop"/>
            <xs:enumeration value="RequestStop"/>
            <xs:enumeration value="Telecabin"/>
            <xs:enumeration value="Train"/>
            <xs:enumeration value="Tram"/>
            <xs:enumeration value="Trolleybus"/>
            <xs:enumeration value="UndergroundA"/>
            <xs:enumeration value="UndergroundB"/>
            <xs:enumeration value="UndergroundC"/>
            <xs:enumeration value="UndergroundD"/>
            */
    QDomElement dPlaceName=xmlko.createElement("PlaceName");
    dPlaceName.appendChild(xmlko.createElement("Value"));
    dPlaceName.firstChildElement("Value").appendChild(xmlko.createTextNode(nacestnaZastavka.StopName));
    dPlaceName.appendChild(xmlko.createElement("Language"));
    dPlaceName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
    dViaPoint.appendChild(dPlaceName);

    //qDebug()<<"nacestna zastavka "<<nacestnaZastavka.StopName<<""<<nacestnaZastavka.cisloCis;
    return dViaPoint;
}

QDomElement xmlGenerator::TimeStampTag1_0(QDomDocument xmlko)
{
    QDomElement dTimeStamp=xmlko.createElement("TimeStamp");
    QDomElement dTimeStampValue =xmlko.createElement("Value");
    dTimeStampValue.appendChild(xmlko.createTextNode(this->createTimestamp()));
    dTimeStamp.appendChild(dTimeStampValue);

    return dTimeStamp;

}

QVector<Pasmo> xmlGenerator::pasmoStringDoVectoru(QString vstup,QString system)
{
    QStringList stringPasma = vstup.split(',');
    QVector<Pasmo> seznamPasem;

    for (int i=0;i<stringPasma.length();i++)
    {
        Pasmo intPasmo;
        intPasmo.nazev=stringPasma.at(i);
        intPasmo.system=system;
        seznamPasem.append(intPasmo);
    }
    return seznamPasem;
}

QVector<QDomElement> xmlGenerator::FareZoneInformationStructure1_0(QVector<Pasmo> seznamPasem,QString language)
{
    QDomDocument xmlko;


    QVector<QDomElement> seznamFareZone;

    for (int i=0;i<seznamPasem.length() ;i++ )
    {
        Pasmo aktPasmo=seznamPasem.at(i);
        QDomElement pasmo=fareZone1_0(aktPasmo.nazev,aktPasmo.nazev,aktPasmo.system,language );
        seznamFareZone.append(pasmo);

    }
    return seznamFareZone;
}
QVector<QDomElement> xmlGenerator::FareZoneInformationStructure2_2CZ1_0(QVector<Pasmo> seznamPasem,QString language)
{
    QDomDocument xmlko;


    QVector<QDomElement> seznamFareZone;

    for (int i=0;i<seznamPasem.length() ;i++ )
    {
        Pasmo aktPasmo=seznamPasem.at(i);
        QDomElement pasmo=fareZone2_2CZ1_0(aktPasmo.nazev,aktPasmo.nazev,aktPasmo.system,language );
        seznamFareZone.append(pasmo);

    }
    return seznamFareZone;
}



QDomElement xmlGenerator::fareZone1_0(QString shortName,QString longName, QString type, QString language)
{
    QDomDocument xmlko;

    QDomElement pasmo=ref("FareZone",shortName);


    return pasmo;
}

QDomElement xmlGenerator::fareZone2_2CZ1_0(QString shortName,QString longName, QString type, QString language)
{
    QDomDocument xmlko;




    QDomElement pasmo=xmlko.createElement("FareZone");
    QDomElement zoneType=xmlko.createElement("FareZoneType");
    QDomElement zoneTypeName=internationalTextType("FareZoneTypeName",type,language);
    zoneType.appendChild(zoneTypeName);
    pasmo.appendChild(zoneType);


    QDomElement zoneLongName=internationalTextType("FareZoneLongName",longName,language);
    QDomElement zoneShortName=internationalTextType("FareZoneShortName",shortName,language);

    pasmo.appendChild(zoneLongName);
    pasmo.appendChild(zoneShortName);

    return pasmo;
}

QDomElement xmlGenerator::internationalTextType(QString name,QString value,QString language)
{
    // qDebug()<<"xmlGenerator::internationalTextType"<<"hodnota "<<value<<" jmeno "<<name;
    // qDebug()<<"xmlGenerator::internationalTextType";
    QDomDocument xmlko;
    QDomElement vysledek=xmlko.createElement(name);
    QDomElement xvalue=xmlko.createElement("Value");
    xvalue.appendChild(xmlko.createTextNode(value));
    vysledek.appendChild(xvalue);
    QDomElement xlanguage=xmlko.createElement("Language");
    //xlanguage.setNodeValue(language); nefunguje
    xlanguage.appendChild(xmlko.createTextNode(language));
    //qDebug()<<"xlanguage node value"<<xlanguage.nodeValue();
    vysledek.appendChild(xlanguage);
    //qDebug()<<"vyledek text "<<vysledek.text();
    return vysledek;
}

QDomElement xmlGenerator::ref(QString name, QString value)
{
    //qDebug()<<"xmlGenerator::ref"<<"hodnota "<<"ref"<<value;
    //qDebug()<<"xmlGenerator::ref";
    QDomDocument xmlko;

    QDomElement ref=xmlko.createElement(name);

    QDomElement xvalue=xmlko.createElement("Value");


    xvalue.appendChild(xmlko.createTextNode(value));
    ref.appendChild(xvalue);


    return ref;
}


QDomElement xmlGenerator::xxxProperty2_2CZ1_0(QString nazev,bool vysledek,QString hodnota)
{
    QDomDocument xmlko;
    if(vysledek)
    {
        QDomElement stopProperty =xmlko.createElement(nazev);
        stopProperty.appendChild(xmlko.createTextNode(hodnota));
        //qDebug()<<"zastavka na znameni";
        return stopProperty;
    }

    QDomElement prazdny;
    return prazdny;


}


