#include "xmlgenerator.h"
#include <QTime>

xmlGenerator::xmlGenerator(QWidget *parent) : QMainWindow(parent)
{

}

QByteArray xmlGenerator::AllData()
{
    QByteArray language="cz";
    QByteArray deflanguage="cz";
    QByteArray lineNumber="741";
    QByteArray lineName=lineNumber;
    QByteArray vehicleref="33";
    QByteArray currentStopIndex="5";
    QByteArray routeDeviation="onroute";
    QByteArray doorState="AllDoorsClosed";
    QByteArray vehicleStopRequested="0";
    QByteArray exitSide="right";
    QByteArray tripRef="3";
    QByteArray displayContentRef="1234";
    QByteArray destinationRef="22";
    QByteArray destinationName="Sportovní Hala";

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
    QByteArray xDestination="";
    QByteArray xDestinationRef="";
    QByteArray xDestinationName="";


    xTimeStamp="<TimeStamp>"+this->createTimestamp()+"</TimeStamp>";
    xVehicleRef="<VehicleRef><Value>"+vehicleref+"</Value></VehicleRef>";
    xDefaultLanguage="<DefaultLanguage><Value>"+deflanguage+"</Value></DefaultLanguage>";
    xTripRef="<TripRef><Value>"+tripRef+"</Value></TripRef>";

    xCurrentStopIndex="<CurrentStopIndex><Value>"+currentStopIndex+"</Value></CurrentStopIndex>";
    xRouteDeviation="<RouteDeviation>"+routeDeviation+"</RouteDeviation>";
    xDoorState="<DoorState>"+doorState+"</DoorState>";
    xVehicleStopRequested="<VehicleStopRequested><Value>"+vehicleStopRequested+"</Value></VehicleStopRequested>";
    xExitSide="<ExitSide>"+exitSide+"</ExitSide>";


    QByteArray cCurrentStopIndex="1";
    QByteArray cStopName="jmenoZastavky";
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


    xStopPoint="<StopPoint>"+xStopIndex+xStopRef+xStopName+xDisplayContent+"</StopPoint>";

    xStopSequence="<StopSequence>"+xStopPoint+"</StopSequence>";




    telo+=("<?xml version=\"1.0\" encoding=\"UTF-8\"?>  \r\n");
    xTripInformation="<TripInformation>"+xTripRef+xStopSequence+"</TripInformation>";
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

QByteArray xmlGenerator::devStatus()
{
    QByteArray pozadavek ="";
    QByteArray hlavicka="";
    QByteArray telo="";
    QByteArray deviceState="running";
    QByteArray TgetDeviceStatusResponse="";
    QByteArray TgetDeviceStatusResponseData="";
    QByteArray TtimeStamp="";
    QByteArray TdeviceState="";

/*
     QDateTime casovaZnacka = QDateTime::currentDateTime();
     QString casnaformatovanoString= casovaZnacka.toString("yyyy-MM-ddThh:mm:ss");

*/

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

    QDateTime casovaZnacka = QDateTime::currentDateTime();
    QString casnaformatovanoString= casovaZnacka.toString("yyyy-MM-ddThh:mm:ss");
    QByteArray dopole="";
    dopole.append(casnaformatovanoString);
    return dopole;
}




