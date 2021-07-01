#include "xmlgenerator.h"
#include "xmlgenerator.h"
#include <QTime>

#include "VDV301struktury/zastavka.h"
#include "VDV301struktury/zastavkacil.h"
#include "VDV301struktury/cestaudaje.h"
#include <QCoreApplication>
#include <QtDebug>
#include <QtXml>
#include "prestupmpv.h"
#include "xmlmpvparser.h"
#include "VDV301struktury/pasmo.h"

xmlGenerator::xmlGenerator(QWidget *parent) : QMainWindow(parent)
{
    qDebug()<<"xmlGenerator::xmlGenerator";
    QDomDocument dokument;
}



QString xmlGenerator::AllData1_0(  QVector <ZastavkaCil> docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections, CestaUdaje stav )
{
    qDebug()<<" xmlGenerator::AllData1_0 ";
    int poradi=stav.indexAktZastavky;
    Zastavka cilovaZastavka;
    if (docasnySeznamZastavek.size()==0)
    {
        qDebug()<<"nejsou zastavky";
        return "AllData1.0 nejsou zastavky";
    }
    //cilovaZastavka=docasnySeznamZastavek.last();

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
    //QString destinationName=docasnySeznamZastavek[poradi].DestinationName;
    QString destinationName=docasnySeznamZastavek[poradi].cil.StopName;
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
    //dTripInformation.appendChild(additionalTextMessage1_0("test obsahu zpravy"));
    QString specialniOznameni=docasnySeznamZastavek.at(stav.indexAktZastavky).zastavka.additionalTextMessage;
    qDebug()<<"spec oznameni="<<specialniOznameni;
    if (specialniOznameni!="")
    {
        qDebug()<<"specOznNeniPrazdne";
        dTripInformation.appendChild(additionalTextMessage1_0(specialniOznameni));
    }
    else
    {
        qDebug()<<"specOznJePrazdne";
    }

    qDebug()<<"zaSpecOzn";


    //stop sequence
    dTripInformation.appendChild(StopSequence1_0(xmlko,docasnySeznamZastavek,language,currentStopIndex,Connections,stav));
    //dTripInformation.appendChild(dStopSequence);


    QDomElement dLocationState=xmlko.createElement("LocationState");
    dLocationState.appendChild(xmlko.createTextNode( locationState));
    dTripInformation.appendChild(dLocationState);
    qDebug()<<"DB1";
    QDomElement dCurrentStopIndex=xmlko.createElement("CurrentStopIndex");
    dCurrentStopIndex.appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(QString::number(currentStopIndex)));
    dAllData.appendChild(dCurrentStopIndex);
    qDebug()<<"DB2";
    QDomElement dRouteDeviation = xmlko.createElement("RouteDeviation");
    dRouteDeviation.appendChild(xmlko.createTextNode(routeDeviation));
    dAllData.appendChild(dRouteDeviation);
    qDebug()<<"DB3";
    QDomElement dDoorState = xmlko.createElement("DoorState");
    dDoorState.appendChild(xmlko.createTextNode(doorState));
    dAllData.appendChild(dDoorState);
    qDebug()<<"DB4";
    QDomElement dVehicleStopRequested=xmlko.createElement("VehicleStopRequested");
    dVehicleStopRequested.appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(vehicleStopRequested));
    dAllData.appendChild(dVehicleStopRequested);
    QDomElement dExitSide = xmlko.createElement("ExitSide");
    qDebug()<<"DB5";
    dExitSide.appendChild(xmlko.createTextNode(exitSide));
    dAllData.appendChild(dExitSide);
    /*telo="";
    telo+=xmlko;*/
    qDebug()<<"DB6";
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


QString xmlGenerator::AllData2_2CZ1_0(int poradi, QVector <ZastavkaCil> docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections )
{
    qDebug()<<"xmlGenerator::AllData2_2CZ1_0";

    //SeznamZastavek cilovaZastavka=docasnySeznamZastavek.last();


    // Zastavka cilovaZastavka;
    if (docasnySeznamZastavek.size()>0)
    {
        //cilovaZastavka=docasnySeznamZastavek.last();
    }
    else
    {
        qDebug()<<"nejsou zastavky";
        return "prazdnyString";
    }

    // QString testVysledek="<TBL cas=\"2019-08-10T23:12:41\" ver=\"1.0.7145.21217\" text=\"Ověřovací provoz. Bez záruky.\"><t id=\"62887\" stan=\"A,B,M1,M2\" zast=\"Národní třída\"><o stan=\"A\" lin=\"9\" alias=\"9\" spoj=\"77\" smer=\"Praha,Spojovací\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27891\"/><o stan=\"B\" lin=\"18\" alias=\"18\" spoj=\"15\" smer=\"Praha,Nádraží Podbaba\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"63414\"/><o stan=\"A\" lin=\"22\" alias=\"22\" spoj=\"273\" smer=\"Praha,Nádraží Strašnice\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"57696\"/><o stan=\"M1\" lin=\"B\" alias=\"B\" spoj=\"32\" smer=\"Praha,Zličín\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Metro\" dd=\"1\" smer_c=\"28037\"/><o stan=\"B\" lin=\"22\" alias=\"22\" spoj=\"161\" smer=\"Praha,Bílá Hora\" odj=\"2019-08-10T23:17:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27908\"/></t></TBL>";
    qDebug()<<"mezera  ";
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
    //QString destinationName=docasnySeznamZastavek[poradi].cil.NameLcd;

    // QString destinationName=docasnySeznamZastavek[poradi].DestinationName;

    /* QString destinationFrontName=docasnySeznamZastavek[poradi].DestinationName;
    QString destinationSideName=docasnySeznamZastavek[poradi].DestinationName;
    QString destinationRearName=docasnySeznamZastavek[poradi].DestinationName;
*/
    //qDebug()<<"nazev cile2"<<destinationName;

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

    QString specialniOznameni=docasnySeznamZastavek.at(poradi).zastavka.additionalTextMessage;
    qDebug()<<"spec oznameni="<<specialniOznameni;
    if (specialniOznameni!="")
    {
        dTripInformation.appendChild(additionalTextMessage1_0(specialniOznameni));
    }

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



QString xmlGenerator::CurrentDisplayContent1_0(int poradi, QVector <ZastavkaCil> docasnySeznamZastavek, CestaUdaje stav )
{
    qDebug()<<"xmlGenerator::CurrentDisplayContent1_0";
    Zastavka cilovaZastavka;
    if (docasnySeznamZastavek.size()==0)
    {
        qDebug()<<"currentDisplayContent NejsouZastavky";
        return "nejsou zastavky";
    }

    ZastavkaCil aktualniZastavka=docasnySeznamZastavek.at(poradi);

    qDebug()<<"  ";
    QString  language="cz";
    QString  lineNumber=aktualniZastavka.linka.LineNumber;
    QString  lineName=lineNumber.right(3);
    int  currentStopIndex= poradi;




    QString destinationName=docasnySeznamZastavek[poradi].cil.StopName;
    QString destinationRef=QString::number(docasnySeznamZastavek[poradi].cil.cisloCis);
    QDomDocument xmlko;
    QDomProcessingInstruction dHlavicka=xmlko.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
    xmlko.appendChild(dHlavicka);

    QDomElement dCustomerInformationService=xmlko.createElement("CustomerInformationService.GetCurrentDisplayContentResponse");
    QDomElement dCurrentDisplayContentData=xmlko.createElement("CurrentDisplayContentData");


    dCurrentDisplayContentData.appendChild(TimeStampTag1_0(xmlko));


    dCurrentDisplayContentData.appendChild(DisplayContent1_0("CurrentDisplayContent",xmlko,docasnySeznamZastavek,language,stav));
    dCustomerInformationService.appendChild(dCurrentDisplayContentData);
    xmlko.appendChild(dCustomerInformationService);






    return xmlko.toString();
}


QDomElement xmlGenerator::StopSequence1_0(QDomDocument xmlko,QVector<ZastavkaCil> docasnySeznamZastavek,QString language, int currentStopIndex, QDomDocument Connections,CestaUdaje stav)
{
    QDomElement dStopSequence=xmlko.createElement("StopSequence");
    //dTripInformation.appendChild(dStopSequence);
    for (int i=0 ; i<docasnySeznamZastavek.count();i++)
    {
        //Zastavka aktZastavka=docasnySeznamZastavek.at(i);

        dStopSequence.appendChild(stopPoint1_0(docasnySeznamZastavek,i,Connections,language,currentStopIndex,stav));

    }
    return dStopSequence;
}

QDomElement xmlGenerator::StopSequence2_2CZ1_0(QDomDocument xmlko,QVector<ZastavkaCil> docasnySeznamZastavek,QString language, int currentStopIndex, QDomDocument Connections)
{
    QDomElement dStopSequence=xmlko.createElement("StopSequence");
    //dTripInformation.appendChild(dStopSequence);
    for (int i=0 ; i<docasnySeznamZastavek.count();i++)
    {
        //Zastavka aktZastavka=docasnySeznamZastavek.at(i);

        dStopSequence.appendChild(stopPoint2_2CZ1_0(docasnySeznamZastavek,i,Connections,language,currentStopIndex));

    }
    return dStopSequence;
}


QDomElement xmlGenerator::stopPoint1_0(QVector<ZastavkaCil> docasnySeznamZastavek,int indexZpracZastavky, QDomDocument Connections, QString language,int currentStopIndex,CestaUdaje stav)
{
    ZastavkaCil aktZastavka=docasnySeznamZastavek.at(indexZpracZastavky);
    QDomDocument xmlko;
    //SeznamZastavek prochazenaZastavka=docasnySeznamZastavek.at(i);
    QByteArray cCurrentStopIndex=QByteArray::number(aktZastavka.zastavka.StopIndex);
    QString cStopName= aktZastavka.zastavka.StopName;
    QString cStopFrontName= aktZastavka.zastavka.NameFront;
    QString cStopSideName= aktZastavka.zastavka.NameSide;
    QString cStopRearName= aktZastavka.zastavka.NameRear;
    QString cStopInnerName= aktZastavka.zastavka.NameInner;
    QString cStopLcdName= aktZastavka.zastavka.NameLcd;
    //QString xDestinationName= aktZastavka.DestinationName;
    QString xDestinationName= aktZastavka.cil.NameFront;

    QString xDestinationCis=QString::number(aktZastavka.cil.cisloCis);
    //STOP
    QDomElement dStopPoint=xmlko.createElement("StopPoint");

    QDomElement dStopIndex=xmlko.createElement("StopIndex");
    dStopIndex.appendChild(xmlko.createElement("Value"));
    dStopIndex.firstChildElement("Value").appendChild(xmlko.createTextNode(cCurrentStopIndex ));
    dStopPoint.appendChild(dStopIndex);

    dStopPoint.appendChild(ref("StopRef",QString::number(aktZastavka.zastavka.cisloCis)));

    QDomElement dStopName=internationalTextType("StopName",cStopName,language);
    dStopPoint.appendChild(dStopName);

    QDomElement dStopFrontName=internationalTextType("StopFrontName",cStopFrontName,language);
    dStopPoint.appendChild(dStopFrontName);

    QDomElement dStopSideName=internationalTextType("StopSideName",cStopSideName,language);
    dStopPoint.appendChild(dStopSideName);

    QDomElement dStopRearName=internationalTextType("StopRearName",cStopRearName,language);
    dStopPoint.appendChild(dStopRearName);

    QDomElement dStopInnerName=internationalTextType("StopInnerName",cStopInnerName,language);
    dStopPoint.appendChild(dStopInnerName);

    QDomElement dStopLcdName=internationalTextType("StopLcdName",cStopLcdName,language);
    dStopPoint.appendChild(dStopLcdName);



    QDomElement dDisplayContent=DisplayContent1_0("DisplayContent",xmlko,docasnySeznamZastavek,language, stav);
    dStopPoint.appendChild(dDisplayContent);



    QVector<QDomElement> domPasma=FareZoneInformationStructure1_0(aktZastavka.zastavka.seznamPasem,language);
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

QDomElement xmlGenerator::stopPoint2_2CZ1_0(QVector<ZastavkaCil> docasnySeznamZastavek,int indexZpracZastavky, QDomDocument Connections, QString language,int currentStopIndex)
{
    ZastavkaCil aktZastavka=docasnySeznamZastavek.at(indexZpracZastavky);
    QDomDocument xmlko;
    //SeznamZastavek prochazenaZastavka=docasnySeznamZastavek.at(i);
    QByteArray cCurrentStopIndex=QByteArray::number(aktZastavka.zastavka.StopIndex);
    QString cStopName= aktZastavka.zastavka.StopName;
    QString xDestinationName= aktZastavka.cil.StopName;
    QString xDestinationCis=QString::number(aktZastavka.cil.cisloCis);
    //STOP
    QDomElement dStopPoint=xmlko.createElement("StopPoint");

    QDomElement dStopIndex=xmlko.createElement("StopIndex");
    dStopIndex.appendChild(xmlko.createElement("Value"));
    dStopIndex.firstChildElement("Value").appendChild(xmlko.createTextNode(cCurrentStopIndex ));
    dStopPoint.appendChild(dStopIndex);

    dStopPoint.appendChild(ref("StopRef",QString::number(aktZastavka.cil.cisloCis)));

    QDomElement dStopName=internationalTextType("StopName",cStopName,language);
    dStopPoint.appendChild(dStopName);

    QDomElement dStopFrontName=internationalTextType("StopFrontName",aktZastavka.zastavka.NameFront,language);
    dStopPoint.appendChild(dStopFrontName);
    QDomElement dStopSideName=internationalTextType("StopSideName",aktZastavka.zastavka.NameSide,language);
    dStopPoint.appendChild(dStopSideName);
    QDomElement dStopRearName=internationalTextType("StopRearName",aktZastavka.zastavka.NameRear,language);
    dStopPoint.appendChild(dStopRearName);
    QDomElement dStopLcdName=internationalTextType("StopLcdName",aktZastavka.zastavka.NameLcd,language);
    dStopPoint.appendChild(dStopLcdName);
    QDomElement dStopInnerName=internationalTextType("StopInnerName",aktZastavka.zastavka.NameInner,language);
    dStopPoint.appendChild(dStopInnerName);

    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.zastavka.naZnameni,"RequestStop"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.zastavka.prestupLetadlo ,"Air"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.zastavka.prestupPrivoz ,"Ferry"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.zastavka.prestupMetroA ,"UndergroundA"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.zastavka.prestupMetroB ,"UndergroundB"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.zastavka.prestupMetroC ,"UndergroundC"));
    dStopPoint.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavka.zastavka.prestupMetroD ,"UndergroundD"));
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



    QVector<QDomElement> domPasma=FareZoneInformationStructure2_2CZ1_0(aktZastavka.zastavka.seznamPasem,language);
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

QDomElement xmlGenerator::DisplayContent1_0(QString tagName,QDomDocument xmlko,QVector<ZastavkaCil> docasnySeznamZastavek, QString language,  CestaUdaje stav)
{

    int indexAktZastavky=stav.indexAktZastavky;
    ZastavkaCil aktZastCil=docasnySeznamZastavek.at(indexAktZastavky);


    QString destinationName=aktZastCil.cil.NameLcd;
    QString lineNumber=aktZastCil.linka.LineNumber;
    QString lineName=aktZastCil.linka.LineName;
    QString destinationRef=QString::number(docasnySeznamZastavek.at(indexAktZastavky).cil.cisloCis);
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
            ZastavkaCil pristi=docasnySeznamZastavek.at(indexAktZastavky+1);
            if (pristi.zastavka.nacestna==0)
            {
                dDisplayContent.appendChild(ViaPoint1_0(xmlko,pristi.zastavka,language));
            }

        }

        for (int j=indexAktZastavky+1;j<docasnySeznamZastavek.count() ;j++)
        {
            //qDebug()<<"Projizdim nacesty "<<docasnySeznamZastavek.at(j).nacestna<<" "<<docasnySeznamZastavek.at(j).StopName ;
            if(docasnySeznamZastavek.at(j).zastavka.nacestna == 1)
            {
                Zastavka nacestnaZastavka=docasnySeznamZastavek.at(j).zastavka;
                dDisplayContent.appendChild(ViaPoint1_0(xmlko,nacestnaZastavka,language));
            }
        }
    }
    else
    {
        if ((pridatPristi==true)&&((indexAktZastavky)<docasnySeznamZastavek.count()))
        {
            Zastavka pristi=docasnySeznamZastavek.at(indexAktZastavky).zastavka;
            if (pristi.nacestna==0)
            {
                dDisplayContent.appendChild(ViaPoint1_0(xmlko,pristi,language));
            }

        }

        for (int j=indexAktZastavky;j<docasnySeznamZastavek.count() ;j++)
        {
            //qDebug()<<"Projizdim nacesty "<<docasnySeznamZastavek.at(j).nacestna<<" "<<docasnySeznamZastavek.at(j).StopName ;
            if(docasnySeznamZastavek.at(j).zastavka.nacestna == 1)
            {
                Zastavka nacestnaZastavka=docasnySeznamZastavek.at(j).zastavka;
                dDisplayContent.appendChild(ViaPoint1_0(xmlko,nacestnaZastavka,language));
            }
        }
    }


    return dDisplayContent;
}

QDomElement xmlGenerator::DisplayContent2_2CZ1_0(QString tagName,QVector<ZastavkaCil> docasnySeznamZastavek, QString language,int iteracniIndex,int currentStopIndex)
{
    QDomDocument xmlko;
    ZastavkaCil aktZastavkaCil=docasnySeznamZastavek.at(iteracniIndex);
    QString lineNumber=aktZastavkaCil.linka.LineNumber;
    QString lineName=aktZastavkaCil.linka.LineName;
    QString destinationName=aktZastavkaCil.cil.StopName;


    bool pridatPristi=true;
    QDomElement dDisplayContent=xmlko.createElement(tagName);

    dDisplayContent.appendChild(ref("DisplayContentRef","1234"));

    QDomElement dLineInformation=xmlko.createElement("LineInformation");
    dDisplayContent.appendChild(dLineInformation);

    //dLineInformation.appendChild(ref("LineRef",lineNumber));



    if(lineName.length()>3)
    {
    lineName="v&#27;&amp;"+lineName;
    }
    QDomElement dLineName=internationalTextType("LineName",lineName,language);



    dLineInformation.appendChild(dLineName);

    QDomElement dLineNumber=xmlko.createElement("LineNumber");
    dLineNumber.appendChild(xmlko.createElement("Value"));
    dLineNumber.firstChildElement("Value").appendChild(xmlko.createTextNode(lineNumber));
    dLineInformation.appendChild(dLineNumber);

    QDomElement dDestination=xmlko.createElement("Destination");

    dDestination.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavkaCil.cil.naZnameni,"RequestStop"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavkaCil.cil.prestupLetadlo ,"Air"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavkaCil.cil.prestupPrivoz ,"Ferry"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavkaCil.cil.prestupMetroA ,"UndergroundA"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavkaCil.cil.prestupMetroB ,"UndergroundB"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavkaCil.cil.prestupMetroC ,"UndergroundC"));
    dDestination.appendChild(xxxProperty2_2CZ1_0("StopProperty",aktZastavkaCil.cil.prestupMetroD ,"UndergroundD"));
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


    //QDomElement dDestinationName=internationalTextType("DestinationName",destinationName,language);
    if (aktZastavkaCil.cil.NameFront2=="")
    {
        if (aktZastavkaCil.cil.NameFront.contains("|"))
        {

            QStringList predniCile=aktZastavkaCil.cil.NameFront.split("|");

            QString iteracniCil;

            foreach (iteracniCil, predniCile)
            {
                QDomElement dDestinationFrontName=internationalTextType("DestinationFrontName",iteracniCil,language);
                dDestination.appendChild(dDestinationFrontName);
            }





        }
        else
        {

            QDomElement dDestinationFrontName=internationalTextType("DestinationFrontName",aktZastavkaCil.cil.NameFront,language);
            dDestination.appendChild(dDestinationFrontName);
        }
    }
    else
    {
        QDomElement dDestinationFrontName=internationalTextType("DestinationFrontName",aktZastavkaCil.cil.NameFront,language);
        dDestination.appendChild(dDestinationFrontName);
        QDomElement dDestinationFrontName2=internationalTextType("DestinationFrontName",aktZastavkaCil.cil.NameFront2,language);
        dDestination.appendChild(dDestinationFrontName2);
    }


    QDomElement dDestinationSideName=internationalTextType("DestinationSideName",aktZastavkaCil.cil.NameSide,language);
    dDestination.appendChild(dDestinationSideName);
    QDomElement dDestinationRearName=internationalTextType("DestinationRearName",aktZastavkaCil.cil.NameRear,language);
    dDestination.appendChild(dDestinationRearName);
    QDomElement dDestinationLcdName=internationalTextType("DestinationLcdName",aktZastavkaCil.cil.NameLcd,language);
    dDestination.appendChild(dDestinationLcdName);
    QDomElement dDestinationInnerName=internationalTextType("DestinationInnerName",aktZastavkaCil.cil.NameInner,language);
    dDestination.appendChild(dDestinationInnerName);

    dDisplayContent.appendChild(dDestination);

    //badabum
    if ((pridatPristi==true)&&((currentStopIndex+1)<docasnySeznamZastavek.count()))
    {
        ZastavkaCil pristi=docasnySeznamZastavek.at(currentStopIndex+1);
        if (pristi.zastavka.nacestna==0)
        {
            dDisplayContent.appendChild(ViaPoint2_2CZ1_0(xmlko,pristi.zastavka,language));
        }

    }

    for (int j=currentStopIndex+1;j<docasnySeznamZastavek.count() ;j++)
    {
        //qDebug()<<"Projizdim nacesty "<<docasnySeznamZastavek.at(j).nacestna<<" "<<docasnySeznamZastavek.at(j).StopName ;
        if(docasnySeznamZastavek.at(j).zastavka.nacestna == 1)
        {
            ZastavkaCil nacestnaZastavka=docasnySeznamZastavek.at(j);
            dDisplayContent.appendChild(ViaPoint2_2CZ1_0(xmlko,nacestnaZastavka.zastavka,language));
        }
    }


    return dDisplayContent;
}

QDomElement xmlGenerator::ViaPoint1_0(QDomDocument xmlko, Zastavka nacestnaZastavka,QString language)
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

QDomElement xmlGenerator::ViaPoint2_2CZ1_0(QDomDocument xmlko, Zastavka nacestnaZastavka,QString language)
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
    QDomElement dPlaceName=internationalTextType("PlaceName",nacestnaZastavka.StopName,language);
    dViaPoint.appendChild(dPlaceName);

    QDomElement dPlaceSideName=internationalTextType("PlaceSideName",nacestnaZastavka.NameSide,language);
    dViaPoint.appendChild(dPlaceSideName);


    QDomElement dPlaceInnerName=internationalTextType("PlaceInnerName",nacestnaZastavka.NameInner,language);
    dViaPoint.appendChild(dPlaceInnerName);

    QDomElement dPlaceLcdName=internationalTextType("PlaceLcdName",nacestnaZastavka.NameLcd,language);
    dViaPoint.appendChild(dPlaceLcdName);





    //QDomElement dPlaceName=xmlko.createElement("PlaceName");
    /*
    dPlaceName.appendChild(xmlko.createElement("Value"));
    dPlaceName.firstChildElement("Value").appendChild(xmlko.createTextNode(nacestnaZastavka.StopName));
    dPlaceName.appendChild(xmlko.createElement("Language"));
    dPlaceName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
*/
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
    //qDebug()<<"xmlGenerator::internationalTextType";
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

QDomElement xmlGenerator::additionalTextMessage1_0(QString obsahZpravy)
{
    QDomDocument xmlko;
    QDomElement additionalTextMessage=xmlko.createElement("AdditionalTextMessage");

    QDomElement value=xmlko.createElement("Value");
    value.appendChild(xmlko.createTextNode(obsahZpravy));
    additionalTextMessage.appendChild(value);
    //<AdditionalTextMessage> <Value>$LS$This is additional text message Šg (Umlaute ÄÖÜäöüß), which could be long...</Value></AdditionalTextMessage>
    return additionalTextMessage;
}

QDomElement xmlGenerator::AllData_empty_1_0()
{
    QDomDocument xmlko;

    QDomElement vysledek;
    QString obsahPrazdny="<CustomerInformationService.GetAllDataResponse><AllData><TimeStamp><Value>2016-09-01T14:27:04</Value></TimeStamp><VehicleRef><Value>0</Value></VehicleRef><DefaultLanguage><Value>de</Value></DefaultLanguage><TripInformation><TripRef><Value>0</Value></TripRef><StopSequence><StopPoint><StopIndex><Value>0</Value></StopIndex><StopRef><Value>noRef</Value></StopRef><StopName><Value> </Value><Language>de</Language></StopName><DisplayContent><LineInformation><LineRef><Value>noRef</Value></LineRef></LineInformation><Destination><DestinationRef><Value>noRef</Value></DestinationRef></Destination></DisplayContent></StopPoint><StopPoint><StopIndex><Value>0</Value></StopIndex><StopRef><Value>noRef</Value></StopRef><StopName><Value> </Value><Language>de</Language></StopName><DisplayContent><LineInformation><LineRef><Value>noRef</Value></LineRef></LineInformation><Destination><DestinationRef><Value>noRef</Value></DestinationRef></Destination></DisplayContent></StopPoint></StopSequence></TripInformation><CurrentStopIndex><Value>0</Value></CurrentStopIndex><RouteDeviation>unknown</RouteDeviation><DoorState>AllDoorsClosed</DoorState><VehicleStopRequested><Value>false</Value></VehicleStopRequested><ExitSide>unknown</ExitSide></AllData></CustomerInformationService.GetAllDataResponse>";
    xmlko.setContent(obsahPrazdny);
    vysledek=xmlko.firstChildElement();

    return vysledek;
}
