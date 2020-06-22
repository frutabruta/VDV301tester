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

QByteArray xmlGenerator::AllData(int poradi, int pocetZastavek, SeznamZastavek *docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QByteArray Connections)
{
    qDebug()<<"xmlGenerator::AllData";
    // Connections="<Connection><StopRef><Value>&lt;StopProperty&gt;&lt;/StopProperty&gt;</Value></StopRef><ConnectionRef><Value>&lt;ConnectionProperty&gt;&lt;/ConnectionProperty&gt;</Value></ConnectionRef><ConnectionType>Interchange</ConnectionType><DisplayContent><DisplayContentRef><Value>2234</Value></DisplayContentRef><LineInformation><LineRef><Value>&lt;LineProperty&gt;Day&lt;/LineProperty&gt;</Value></LineRef><LineName><Value>9</Value><Language>cz</Language></LineName><LineShortName><Value>9</Value><Language>cz</Language></LineShortName><LineNumber><Value>9</Value></LineNumber></LineInformation><Destination><DestinationRef><Value>&lt;DestinationProperty&gt;&lt;/DestinationProperty&gt;</Value></DestinationRef><DestinationName><Value>Praha,Spojovací</Value><Language>cz</Language></DestinationName></Destination></DisplayContent><Platform><Value>A</Value></Platform><ConnectionMode><PtMainMode>TramSubmode</PtMainMode><TramSubmode>localTram</TramSubmode></ConnectionMode><ExpectedDepatureTime><Value>2019-01-28T10:30:00</Value></ExpectedDepatureTime></Connection><Connection><StopRef><Value>&lt;StopProperty&gt;&lt;/StopProperty&gt;</Value></StopRef><ConnectionRef><Value>&lt;ConnectionProperty&gt;&lt;/ConnectionProperty&gt;</Value></ConnectionRef><ConnectionType>Interchange</ConnectionType><DisplayContent><DisplayContentRef><Value>2234</Value></DisplayContentRef><LineInformation><LineRef><Value>&lt;LineProperty&gt;Day&lt;/LineProperty&gt;</Value></LineRef><LineName><Value>18</Value><Language>cz</Language></LineName><LineShortName><Value>18</Value><Language>cz</Language></LineShortName><LineNumber><Value>18</Value></LineNumber></LineInformation><Destination><DestinationRef><Value>&lt;DestinationProperty&gt;&lt;/DestinationProperty&gt;</Value></DestinationRef><DestinationName><Value>Praha,Nádraží Podbaba</Value><Language>cz</Language></DestinationName></Destination></DisplayContent><Platform><Value>B</Value></Platform><ConnectionMode><PtMainMode>TramSubmode</PtMainMode><TramSubmode>localTram</TramSubmode></ConnectionMode><ExpectedDepatureTime><Value>2019-01-28T16:15:00</Value></ExpectedDepatureTime></Connection><Connection><StopRef><Value>&lt;StopProperty&gt;&lt;/StopProperty&gt;</Value></StopRef><ConnectionRef><Value>&lt;ConnectionProperty&gt;&lt;/ConnectionProperty&gt;</Value></ConnectionRef><ConnectionType>Interchange</ConnectionType><DisplayContent><DisplayContentRef><Value>2234</Value></DisplayContentRef><LineInformation><LineRef><Value>&lt;LineProperty&gt;Day&lt;/LineProperty&gt;</Value></LineRef><LineName><Value>22</Value><Language>cz</Language></LineName><LineShortName><Value>22</Value><Language>cz</Language></LineShortName><LineNumber><Value>22</Value></LineNumber></LineInformation><Destination><DestinationRef><Value>&lt;DestinationProperty&gt;&lt;/DestinationProperty&gt;</Value></DestinationRef><DestinationName><Value>Praha,Nádraží Strašnice</Value><Language>cz</Language></DestinationName></Destination></DisplayContent><Platform><Value>A</Value></Platform><ConnectionMode><PtMainMode>TramSubmode</PtMainMode><TramSubmode>localTram</TramSubmode></ConnectionMode><ExpectedDepatureTime><Value>2019-01-28T16:15:00</Value></ExpectedDepatureTime></Connection><Connection><StopRef><Value>&lt;StopProperty&gt;&lt;/StopProperty&gt;</Value></StopRef><ConnectionRef><Value>&lt;ConnectionProperty&gt;&lt;/ConnectionProperty&gt;</Value></ConnectionRef><ConnectionType>Interchange</ConnectionType><DisplayContent><DisplayContentRef><Value>2234</Value></DisplayContentRef><LineInformation><LineRef><Value>&lt;LineProperty&gt;Day&lt;/LineProperty&gt;</Value></LineRef><LineName><Value>B</Value><Language>cz</Language></LineName><LineShortName><Value>B</Value><Language>cz</Language></LineShortName><LineNumber><Value>199003</Value></LineNumber></LineInformation><Destination><DestinationRef><Value>&lt;DestinationProperty&gt;&lt;/DestinationProperty&gt;</Value></DestinationRef><DestinationName><Value>Praha,Zličín</Value><Language>cz</Language></DestinationName></Destination></DisplayContent><Platform><Value>M1</Value></Platform><ConnectionMode><PtMainMode>TramSubmode</PtMainMode><TramSubmode>localTram</TramSubmode></ConnectionMode><ExpectedDepatureTime><Value>2019-01-28T16:15:00</Value></ExpectedDepatureTime></Connection><Connection><StopRef><Value>&lt;StopProperty&gt;&lt;/StopProperty&gt;</Value></StopRef><ConnectionRef><Value>&lt;ConnectionProperty&gt;&lt;/ConnectionProperty&gt;</Value></ConnectionRef><ConnectionType>Interchange</ConnectionType><DisplayContent><DisplayContentRef><Value>2234</Value></DisplayContentRef><LineInformation><LineRef><Value>&lt;LineProperty&gt;Day&lt;/LineProperty&gt;</Value></LineRef><LineName><Value>22</Value><Language>cz</Language></LineName><LineShortName><Value>22</Value><Language>cz</Language></LineShortName><LineNumber><Value>22</Value></LineNumber></LineInformation><Destination><DestinationRef><Value>&lt;DestinationProperty&gt;&lt;/DestinationProperty&gt;</Value></DestinationRef><DestinationName><Value>Praha,Bílá Hora</Value><Language>cz</Language></DestinationName></Destination></DisplayContent><Platform><Value>B</Value></Platform><ConnectionMode><PtMainMode>TramSubmode</PtMainMode><TramSubmode>localTram</TramSubmode></ConnectionMode><ExpectedDepatureTime><Value>2019-01-28T16:15:00</Value></ExpectedDepatureTime></Connection>";
    QByteArray language="cz";
    QByteArray deflanguage="cz";
    QByteArray lineNumber=QByteArray::number(docasLinka);
    QByteArray lineName=lineNumber;
    QByteArray vehicleref="33";
    QByteArray currentStopIndex= QByteArray::number(poradi);
    QByteArray routeDeviation="onroute";
    QByteArray vehicleStopRequested="0";
    QByteArray exitSide="right";
    QByteArray tripRef="3";
    QByteArray displayContentRef="1234";
    QByteArray destinationRef="22";
    QByteArray destinationName="";
    destinationName+=docasnySeznamZastavek[poradi].DestinationName;
    QByteArray dotaz="";
    QByteArray hlavicka="";
    QByteArray telo="";
    QByteArray xGetAllDataResponse="";
    QByteArray xAllData="";
    QByteArray xTimeStamp="";
    QByteArray xVehicleRef="";
    QByteArray xDefaultLanguage="";
    QByteArray xTripInformation="";
    QByteArray xTripRef="";
    QByteArray xLocationState="";
    xLocationState+="<LocationState>"+locationState+"</LocationState>";
    QByteArray xStopSequence="";
    QByteArray xCurrentStopIndex="";
    QByteArray xRouteDeviation="";
    QByteArray xDoorState="";
    QByteArray xVehicleStopRequested="";
    QByteArray xExitSide="";
    // Pro každou zastávku zvlášť
    QByteArray xStopPoint="";
    QByteArray xStopIndex="";
    QByteArray xStopRef="";
    QByteArray xStopName="";
    QByteArray xDisplayContent="";
    QByteArray xDisplayContentRef="";
    QByteArray xLineInformation="";
    QByteArray xLineRef="";
    QByteArray xLineName="";
    QByteArray xLineNumber="";
    /*

      XML dokument bude prepsan usporneji pomoci specializovanych funkci, zatim zbytecne vytvarim promenne zabirajici misto v pameti.
      */

    xTimeStamp="<TimeStamp>"+this->createTimestamp()+"</TimeStamp>";
    xVehicleRef="<VehicleRef><Value>"+vehicleref+"</Value></VehicleRef>";
    xDefaultLanguage="<DefaultLanguage><Value>"+deflanguage+"</Value></DefaultLanguage>";
    xTripRef="<TripRef><Value>"+tripRef+"</Value></TripRef>";
    xCurrentStopIndex="<CurrentStopIndex><Value>"+currentStopIndex+"</Value></CurrentStopIndex>";
    xRouteDeviation="<RouteDeviation>"+routeDeviation+"</RouteDeviation>";
    xDoorState+="<DoorState>"+doorState+"</DoorState>";
    xVehicleStopRequested="<VehicleStopRequested><Value>"+vehicleStopRequested+"</Value></VehicleStopRequested>";
    xExitSide="<ExitSide>"+exitSide+"</ExitSide>";
    for (int i=1 ; i<=pocetZastavek;i++)
    {

        QByteArray cCurrentStopIndex=QByteArray::number(docasnySeznamZastavek[i].StopIndex);
        QByteArray cStopName="";
        cStopName+= docasnySeznamZastavek[i].StopName;
        QByteArray xDestination="";
        QByteArray xDestinationRef="";
        QByteArray xDestinationName="";
        xDestinationName+= docasnySeznamZastavek[i].DestinationName;
        //STOP
        xStopIndex="<StopIndex><Value>"+ cCurrentStopIndex +"</Value></StopIndex>";
        xStopRef="<StopRef><Value>Ref:"+currentStopIndex+"</Value></StopRef>";
        xStopName="<StopName><Value>"+cStopName+"</Value><Language>"+language+"</Language></StopName>";
        //DISPLAY CONTENT
        xDisplayContentRef="<DisplayContentRef><Value>"+displayContentRef+"</Value></DisplayContentRef>";
        xLineRef="<LineRef><Value>"+lineNumber+"</Value></LineRef>";
        xLineName="<LineName><Value>"+lineName+"</Value><Language>"+language+"</Language></LineName>";
        xLineNumber="<LineNumber><Value>"+lineNumber+"</Value></LineNumber>";
        xLineInformation="<LineInformation>"+xLineRef+xLineName+xLineNumber+"</LineInformation>";
        xDestinationRef="<DestinationRef><Value>"+destinationRef+"</Value></DestinationRef>";
        xDestinationName="<DestinationName><Value>"+destinationName+"</Value><Language>"+language+"</Language> </DestinationName>";
        xDestination="<Destination>"+xDestinationRef+xDestinationName+"</Destination>";
        xDisplayContent="<DisplayContent>"+xDisplayContentRef+xLineInformation+xDestination+"</DisplayContent>";

        xStopPoint+="<StopPoint>"+xStopIndex+xStopRef+xStopName+xDisplayContent+Connections+"</StopPoint>";
    }
    xStopSequence="<StopSequence>"+xStopPoint+"</StopSequence>";
    telo+=("<?xml version=\"1.0\" encoding=\"UTF-8\"?>  \r\n");
    xTripInformation="<TripInformation>"+xLocationState+xTripRef+xStopSequence+"</TripInformation>";
    xAllData="<AllData>"+xTimeStamp+xVehicleRef+xDefaultLanguage+xTripInformation+xCurrentStopIndex+xRouteDeviation+xDoorState+xVehicleStopRequested+xExitSide+"</AllData>";
    xGetAllDataResponse+=("<CustomerInformationService.GetAllDataResponse>"+xAllData+"</CustomerInformationService.GetAllDataResponse>");

    hlavicka+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    hlavicka+=("Content-Type: application/xml\r\n");
    hlavicka+=("Connection: close\r\n");
    hlavicka+=("Pragma: no-cache\r\n");
    hlavicka+=("\r\n");
    telo+=xGetAllDataResponse;
    dotaz+=hlavicka+telo;
    return dotaz;
}

QByteArray xmlGenerator::AllData2(int poradi, int pocetZastavek, SeznamZastavek *docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections, bool poslatHlavicku )
{
    qDebug()<<" xmlGenerator::AllData2 ";

    QByteArray vysledekMpvnetu ="";
    QString testVysledek="<TBL cas=\"2019-08-10T23:12:41\" ver=\"1.0.7145.21217\" text=\"Ověřovací provoz. Bez záruky.\"><t id=\"62887\" stan=\"A,B,M1,M2\" zast=\"Národní třída\"><o stan=\"A\" lin=\"9\" alias=\"9\" spoj=\"77\" smer=\"Praha,Spojovací\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27891\"/><o stan=\"B\" lin=\"18\" alias=\"18\" spoj=\"15\" smer=\"Praha,Nádraží Podbaba\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"63414\"/><o stan=\"A\" lin=\"22\" alias=\"22\" spoj=\"273\" smer=\"Praha,Nádraží Strašnice\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"57696\"/><o stan=\"M1\" lin=\"B\" alias=\"B\" spoj=\"32\" smer=\"Praha,Zličín\" odj=\"2019-08-10T23:16:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Metro\" dd=\"1\" smer_c=\"28037\"/><o stan=\"B\" lin=\"22\" alias=\"22\" spoj=\"161\" smer=\"Praha,Bílá Hora\" odj=\"2019-08-10T23:17:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27908\"/></t></TBL>";


    qDebug()<<"  ";
    QByteArray language="cz";
    QByteArray deflanguage="cz";
    QByteArray lineNumber=QByteArray::number(docasLinka);
    QByteArray lineName=lineNumber.right(3);
    QByteArray vehicleref="33";
    QByteArray currentStopIndex= QByteArray::number(poradi);
    QByteArray routeDeviation="onroute";
    QByteArray vehicleStopRequested="0";
    QByteArray exitSide="right";
    QByteArray tripRef="3";
    QByteArray displayContentRef="1234";
    QByteArray destinationRef="22";
    QByteArray destinationName="";
    destinationName+=docasnySeznamZastavek[poradi].DestinationName;
    qDebug()<<"nazev cile2"<<destinationName;
    QByteArray dotaz="";
    QByteArray hlavicka="";
    QByteArray telo="";
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
    for (int i=1 ; i<=pocetZastavek;i++)
    {
        QByteArray cCurrentStopIndex=QByteArray::number(docasnySeznamZastavek[i].StopIndex);
        QByteArray cStopName="";
        cStopName+= docasnySeznamZastavek[i].StopName;
        QByteArray xDestination="";
        QByteArray xDestinationRef="";
        QByteArray xDestinationName="";
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
    telo="";
    telo+=xmlko.toString();
    return telo;
}

QByteArray xmlGenerator::devStatus()
{
    qDebug()<<" xmlGenerator::devStatus ";
    qDebug()<<"  ";
    QByteArray pozadavek ="";
    QByteArray hlavicka="";
    QByteArray telo="";
    QByteArray deviceState="running";
    QByteArray TgetDeviceStatusResponse="";
    QByteArray TgetDeviceStatusResponseData="";
    QByteArray TtimeStamp="";
    QByteArray TdeviceState="";

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

QByteArray xmlGenerator::createTimestamp()
{
    qDebug()<<" xmlGenerator::createTimestamp  ";
    QDateTime casovaZnacka = QDateTime::currentDateTime();
    QString casnaformatovanoString= casovaZnacka.toString("yyyy-MM-ddThh:mm:ss");
    QByteArray dopole="";
    dopole.append(casnaformatovanoString);
    return dopole;
}




