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

xmlGenerator::xmlGenerator(QWidget *parent) : QMainWindow(parent)
{
    qDebug()<<"xmlGenerator::xmlGenerator";
    QDomDocument dokument;
}



QString xmlGenerator::AllData2(int poradi,  QVector <SeznamZastavek> docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections )
{
    SeznamZastavek cilovaZastavka=docasnySeznamZastavek.last();
    qDebug()<<" xmlGenerator::AllData2 ";

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
    dTripInformation.appendChild(StopSequence1_0(xmlko,docasnySeznamZastavek,language,lineNumber,lineName,destinationName,currentStopIndex,Connections));
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


QString xmlGenerator::AllDataRopid(int poradi, QVector <SeznamZastavek> docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections )
{
    qDebug()<<" xmlGenerator::AllDataRopid ";

    QString  vysledekMpvnetu ="";
    QString testVysledek="<TBL cas=\"2019-08-10T23:12:41\" ver=\"1.0.7145.21217\" text=\"Ověřovací provoz. Bez záruky.\"><t id=\"62887\" stan=\"A,B,M1,M2\" zast=\"Národní třída\"><o stan=\"A\" lin=\"9\" alias=\"9\" spoj=\"77\" smer=\"Praha,Spojovací\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27891\"/><o stan=\"B\" lin=\"18\" alias=\"18\" spoj=\"15\" smer=\"Praha,Nádraží Podbaba\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"63414\"/><o stan=\"A\" lin=\"22\" alias=\"22\" spoj=\"273\" smer=\"Praha,Nádraží Strašnice\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"57696\"/><o stan=\"M1\" lin=\"B\" alias=\"B\" spoj=\"32\" smer=\"Praha,Zličín\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Metro\" dd=\"1\" smer_c=\"28037\"/><o stan=\"B\" lin=\"22\" alias=\"22\" spoj=\"161\" smer=\"Praha,Bílá Hora\" odj=\"2019-08-10T23:17:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27908\"/></t></TBL>";


    qDebug()<<"  ";
    QString  language="cz";
    QString  deflanguage="cz";
    QString  lineNumber=QByteArray::number(docasLinka);
    QString  lineName=lineNumber.right(3);
    QString  vehicleref="33";
    QString  currentStopIndex= QByteArray::number(poradi);
    QString  routeDeviation="onroute";
    QString  vehicleStopRequested="0";
    QString  exitSide="right";
    QString  tripRef="3";
    QString  displayContentRef="1234";
    QString  destinationRef="22";
    QString destinationName="";
    destinationName+=docasnySeznamZastavek[poradi].DestinationName;
    qDebug()<<"nazev cile2"<<destinationName;
    QByteArray dotaz="";
    QByteArray hlavicka="";
    //QByteArray telo="";
    QDomDocument xmlko;
    QDomProcessingInstruction dHlavicka=xmlko.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\" ");
    xmlko.appendChild(dHlavicka);
    QDomElement dCustomerInformationService=xmlko.createElement("CustomerInformationService.GetAllDataResponse");
    QDomElement dAllData=xmlko.createElement("AllData");
    xmlko.appendChild(dCustomerInformationService);
    dCustomerInformationService.appendChild(dAllData);
    QDomElement dTimeStamp=xmlko.createElement("TimeStamp");
    dTimeStamp.setNodeValue(this->createTimestamp());
    dAllData.appendChild(dTimeStamp);
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

    QDomElement dLocationState=xmlko.createElement("LocationState");
    dLocationState.appendChild(xmlko.createTextNode( locationState));
    dTripInformation.appendChild(dLocationState);

    QDomElement dTripRef=xmlko.createElement("TripRef");
    dTripRef.appendChild(xmlko.createElement("Value"));
    dTripRef.firstChildElement("Value").appendChild(xmlko.createTextNode(tripRef));
    dTripInformation.appendChild(dTripRef);

    QDomElement dStopSequence=xmlko.createElement("StopSequence");
    dTripInformation.appendChild(dStopSequence);
    for (int i=0 ; i<docasnySeznamZastavek.count();i++)
    {
        QString cCurrentStopIndex=QString::number(docasnySeznamZastavek[i].StopIndex);
        QString  cStopName="";
        cStopName+= docasnySeznamZastavek[i].StopName;
        QString  xDestination="";
        QString  xDestinationRef="";
        QString  xDestinationName="";
        xDestinationName+= docasnySeznamZastavek[i].DestinationName;
        //STOP
        QDomElement dStopPoint=xmlko.createElement("StopPoint");
        dStopSequence.appendChild(dStopPoint);
        QDomElement dStopIndex=xmlko.createElement("StopIndex");
        dStopIndex.appendChild(xmlko.createElement("Value"));
        dStopIndex.firstChildElement("Value").appendChild(xmlko.createTextNode(cCurrentStopIndex ));
        dStopPoint.appendChild(dStopIndex);

        QDomElement dStopRef=xmlko.createElement("StopRef");
        dStopRef.appendChild(xmlko.createElement("Value"));
        dStopRef.firstChildElement("Value").appendChild(xmlko.createTextNode("Ref:"+cCurrentStopIndex));
        dStopPoint.appendChild(dStopRef);

        QDomElement dStopName=xmlko.createElement("StopName");
        dStopName.appendChild(xmlko.createElement("Value"));
        dStopName.firstChildElement("Value").appendChild(xmlko.createTextNode(cStopName));
        dStopName.appendChild(xmlko.createElement("Language"));
        dStopName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
        dStopPoint.appendChild(dStopName);

        QDomElement dDisplayContent=xmlko.createElement("DisplayContent");
        dStopPoint.appendChild(dDisplayContent);

        QDomElement dDisplayContentRef=xmlko.createElement("DisplayContentRef");
        dDisplayContentRef.appendChild(xmlko.createElement("Value"));
        dDisplayContentRef.firstChildElement("Value").appendChild(xmlko.createTextNode("1234"));
        dDisplayContent.appendChild(dDisplayContentRef);

        QDomElement dLineInformation=xmlko.createElement("LineInformation");
        dDisplayContent.appendChild(dLineInformation);
        QDomElement dLineRef=xmlko.createElement("LineRef");
        dLineRef.appendChild(xmlko.createElement("Value"));
        dLineRef.firstChildElement("Value").appendChild(xmlko.createTextNode(lineNumber));
        dLineInformation.appendChild(dLineRef);
        QDomElement dLineName=xmlko.createElement("LineName");
        dLineName.appendChild(xmlko.createElement("Value"));
        dLineName.firstChildElement("Value").appendChild(xmlko.createTextNode(lineName));
        dLineInformation.appendChild(dLineName);
        dLineName.appendChild(xmlko.createElement("Language"));
        dLineName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
        QDomElement dLineNumber=xmlko.createElement("LineNumber");
        dLineNumber.appendChild(xmlko.createElement("Value"));
        dLineNumber.firstChildElement("Value").appendChild(xmlko.createTextNode(lineNumber));
        dLineInformation.appendChild(dLineNumber);
        QDomElement dDestination=xmlko.createElement("Destination");
        dDisplayContent.appendChild(dDestination);
        QDomElement dDestinationRef=xmlko.createElement("DestinationRef");
        dDestinationRef.appendChild(xmlko.createElement("Value"));
        dDestinationRef.firstChildElement("Value").appendChild(xmlko.createTextNode(destinationRef));
        dDestination.appendChild(dDestinationRef);

        QDomElement dDestinationName=xmlko.createElement("DestinationName");
        dDestinationName.appendChild(xmlko.createElement("Value"));
        dDestinationName.firstChildElement("Value").appendChild(xmlko.createTextNode(destinationName));
        dDestinationName.appendChild(xmlko.createElement("Language"));
        dDestinationName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
        dDestination.appendChild(dDestinationName);

        if (cCurrentStopIndex==currentStopIndex)
        {
            qDebug()<<" prestupy "<<Connections.toString();

            QDomNodeList seznamPrestupu = Connections.elementsByTagName("Connection");
            for (int j=0;j<seznamPrestupu.count();j++)
            {
                dStopPoint.appendChild(seznamPrestupu.at(i).toElement() );
            }
        }
    }

    QDomElement dCurrentStopIndex=xmlko.createElement("CurrentStopIndex");
    dCurrentStopIndex.appendChild(xmlko.createElement("Value")).appendChild(xmlko.createTextNode(currentStopIndex));
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
    return xmlko.toString();
}



QString xmlGenerator::CurrentDisplayContent1_0(int poradi, QVector <SeznamZastavek> docasnySeznamZastavek, int docasLinka )
{
    qDebug()<<"xmlGenerator::CurrentDisplayContent1_0";
    SeznamZastavek aktualniZastavka=docasnySeznamZastavek[poradi];

    qDebug()<<"  ";
    QString  language="cz";
    QString  lineNumber=QByteArray::number(docasLinka);
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


    dCurrentDisplayContentData.appendChild(DisplayContent1_0("CurrentDisplayContent",xmlko,docasnySeznamZastavek,lineNumber,lineName,language,destinationRef,destinationName,currentStopIndex));
    dCustomerInformationService.appendChild(dCurrentDisplayContentData);
    xmlko.appendChild(dCustomerInformationService);






    return xmlko.toString();
}


QDomElement xmlGenerator::StopSequence1_0(QDomDocument xmlko,QVector<SeznamZastavek> docasnySeznamZastavek,QString language,QString lineNumber,QString lineName,QString destinationName, int currentStopIndex, QDomDocument Connections)
{
    QDomElement dStopSequence=xmlko.createElement("StopSequence");
    //dTripInformation.appendChild(dStopSequence);
    for (int i=0 ; i<docasnySeznamZastavek.count();i++)
    {
        SeznamZastavek prochazenaZastavka=docasnySeznamZastavek.at(i);
        QByteArray cCurrentStopIndex=QByteArray::number(docasnySeznamZastavek[i].StopIndex);
        QString cStopName= docasnySeznamZastavek[i].StopName;
        //QByteArray xDestination="";
        //QByteArray xDestinationRef=docasnySeznamZastavek[]
        QString xDestinationName= docasnySeznamZastavek.at(i).DestinationName;
        QString xDestinationCis=QString::number(docasnySeznamZastavek.at(i).DestinationCis);
        //STOP
        QDomElement dStopPoint=xmlko.createElement("StopPoint");
        dStopSequence.appendChild(dStopPoint);
        QDomElement dStopIndex=xmlko.createElement("StopIndex");
        dStopIndex.appendChild(xmlko.createElement("Value"));
        dStopIndex.firstChildElement("Value").appendChild(xmlko.createTextNode(cCurrentStopIndex ));
        dStopPoint.appendChild(dStopIndex);

        QDomElement dStopRef=xmlko.createElement("StopRef");
        dStopRef.appendChild(xmlko.createElement("Value"));
        dStopRef.firstChildElement("Value").appendChild(xmlko.createTextNode("Ref:"+cCurrentStopIndex));
        dStopPoint.appendChild(dStopRef);

        QDomElement dStopName=xmlko.createElement("StopName");
        dStopName.appendChild(xmlko.createElement("Value"));
        dStopName.firstChildElement("Value").appendChild(xmlko.createTextNode(cStopName));
        dStopName.appendChild(xmlko.createElement("Language"));
        dStopName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
        dStopPoint.appendChild(dStopName);

        //DisplayContent

        //xDestinationCis


        QDomElement dDisplayContent=DisplayContent1_0("DisplayContent",xmlko,docasnySeznamZastavek, lineNumber,lineName,language,xDestinationCis,destinationName,currentStopIndex);
        dStopPoint.appendChild(dDisplayContent);


        if (cCurrentStopIndex.toInt()==currentStopIndex)
        {
            qDebug()<<" prestupy "<<Connections.toString();

            QDomNodeList seznamPrestupu = Connections.elementsByTagName("Connection");
            for (int j=0;j<seznamPrestupu.count();j++)
            {
                dStopPoint.appendChild(seznamPrestupu.at(i).toElement() );
            }
        }
    }
    return dStopSequence;
}


QDomElement xmlGenerator::DisplayContent1_0(QString tagName,QDomDocument xmlko,QVector<SeznamZastavek> docasnySeznamZastavek, QString lineNumber, QString lineName, QString language, QString destinationRef, QString destinationName,int currentStopIndex)
{
    QDomElement dDisplayContent=xmlko.createElement(tagName);


    QDomElement dDisplayContentRef=xmlko.createElement("DisplayContentRef");
    dDisplayContentRef.appendChild(xmlko.createElement("Value"));
    dDisplayContentRef.firstChildElement("Value").appendChild(xmlko.createTextNode("1234"));
    dDisplayContent.appendChild(dDisplayContentRef);

    QDomElement dLineInformation=xmlko.createElement("LineInformation");
    dDisplayContent.appendChild(dLineInformation);
    QDomElement dLineRef=xmlko.createElement("LineRef");
    dLineRef.appendChild(xmlko.createElement("Value"));
    dLineRef.firstChildElement("Value").appendChild(xmlko.createTextNode(lineNumber));
    dLineInformation.appendChild(dLineRef);
    QDomElement dLineName=xmlko.createElement("LineName");
    dLineName.appendChild(xmlko.createElement("Value"));
    dLineName.firstChildElement("Value").appendChild(xmlko.createTextNode(lineName));
    dLineInformation.appendChild(dLineName);
    dLineName.appendChild(xmlko.createElement("Language"));
    dLineName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
    QDomElement dLineNumber=xmlko.createElement("LineNumber");
    dLineNumber.appendChild(xmlko.createElement("Value"));
    dLineNumber.firstChildElement("Value").appendChild(xmlko.createTextNode(lineNumber));
    dLineInformation.appendChild(dLineNumber);

    QDomElement dDestination=xmlko.createElement("Destination");
    QDomElement dDestinationRef=xmlko.createElement("DestinationRef");
    dDestinationRef.appendChild(xmlko.createElement("Value"));
    dDestinationRef.firstChildElement("Value").appendChild(xmlko.createTextNode(destinationRef));
    dDestination.appendChild(dDestinationRef);

    QDomElement dDestinationName=xmlko.createElement("DestinationName");
    dDestinationName.appendChild(xmlko.createElement("Value"));
    dDestinationName.firstChildElement("Value").appendChild(xmlko.createTextNode(destinationName));
    dDestinationName.appendChild(xmlko.createElement("Language"));
    dDestinationName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));

    dDestination.appendChild(dDestinationName);
    dDisplayContent.appendChild(dDestination);

    for (int j=currentStopIndex+1;j<docasnySeznamZastavek.count() ;j++)
    {
        //qDebug()<<"Projizdim nacesty "<<docasnySeznamZastavek.at(j).nacestna<<" "<<docasnySeznamZastavek.at(j).StopName ;
        if(docasnySeznamZastavek.at(j).nacestna == 1)
        {
            SeznamZastavek nacestnaZastavka=docasnySeznamZastavek.at(j);
            dDisplayContent.appendChild(ViaPoint1_0(xmlko,nacestnaZastavka,language));
        }
    }
    return dDisplayContent;
}

QDomElement xmlGenerator::ViaPoint1_0(QDomDocument xmlko, SeznamZastavek nacestnaZastavka,QString language)
{
    qDebug()<<"nacestaNalezena";


    QDomElement dViaPoint=xmlko.createElement("ViaPoint");
    QDomElement dViaPointRef=xmlko.createElement("ViaPointRef");
    dViaPointRef.appendChild(xmlko.createElement("Value"));
    dViaPointRef.firstChildElement("Value").appendChild(xmlko.createTextNode(QString::number(nacestnaZastavka.cisloCis)));
    dViaPoint.appendChild(dViaPointRef);
    QDomElement dPlaceName=xmlko.createElement("PlaceName");
    dPlaceName.appendChild(xmlko.createElement("Value"));
    dPlaceName.firstChildElement("Value").appendChild(xmlko.createTextNode(nacestnaZastavka.StopName));
    dPlaceName.appendChild(xmlko.createElement("Language"));
    dPlaceName.firstChildElement("Language").appendChild(xmlko.createTextNode(language));
    dViaPoint.appendChild(dPlaceName);

    qDebug()<<"nacestna zastavka "<<nacestnaZastavka.StopName<<""<<nacestnaZastavka.cisloCis;
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
