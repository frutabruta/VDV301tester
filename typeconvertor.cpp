#include "typeconvertor.h"

TypeConvertor::TypeConvertor() {}




Connection TypeConvertor::connectionGolemioToConnection(ConnectionGolemio input)
{
    qDebug()<<Q_FUNC_INFO;
    Connection output;

    output.connectionProperty="";
    output.connectionType="";

    output.line.lineName=input.routeShortName;
    output.destinationName=input.tripHeadsign;
    output.scheduledDepartureTime=input.departureTimestampScheduled;
    output.expectedDepartureTime=input.departureTimestampPredicted;
    output.platform=input.stopPlatformCode;



    if(input.tripIsWheelchairAccessible)
    {
        output.connectionProperty="Accessible";
    }


    switch(input.routeType)
    {
    case 0: //Tram, Streetcar, Light rail. Any light rail or street level system within a metropolitan area.
        output.mainMode="TramSubmode";

        if(input.routeIsRegional)
        {
            output.subMode="regionalTram";
        }
        else
        {
            output.subMode="localTram";
        }


        break;
    case 1: //Subway, Metro. Any underground rail system within a metropolitan area.
        output.mainMode="MetroSubmode";
        output.subMode="metro";

        break;
    case 2: //Rail. Used for intercity or long-distance travel.
        output.mainMode="RailSubmode";


        output.subMode="regionalRail";

        break;
    case 3: //Bus. Used for short- and long-distance bus routes.
        output.mainMode="BusSubmode";
        if(input.routeIsRegional)
        {
            output.subMode="regionalBus";
        }
        else
        {
            output.subMode="localBus";
        }


        break;
    case 4: //Ferry. Used for short- and long-distance boat service.
        output.mainMode="WaterSubmode";
        output.subMode="localPassengerFerry";

        break;
    case 5: //Cable tram. Used for street-level rail cars where the cable runs beneath the vehicle, e.g., cable car in San Francisco.

        output.mainMode="";
        output.subMode="";

        break;
    case 6: //Aerial lift, suspended cable car (e.g., gondola lift, aerial tramway). Cable transport where cabins, cars, gondolas or open chairs are suspended by means of one or more cables.
        output.mainMode="TelecabinSubmode";
        output.subMode="";

        break;


    case 7: //Funicular. Any rail system designed for steep inclines.

        output.mainMode="FunicularSubmode";
        output.subMode="";

        break;

    case 11: //Trolleybus. Electric buses that draw power from overhead wires using poles.

        output.mainMode="";
        output.subMode="";

        output.mainMode="TrolleybusSubmode";
        if(input.routeIsRegional)
        {
            output.subMode="regionalTrolleybus";
        }
        else
        {
            output.subMode="localTrolleybus";
        }

        break;


    case 12: //Monorail. Railway in which the track consists of a single rail or a beam.

        output.mainMode="";
        output.subMode="";

        break;


    default:
        output.mainMode="unknown";
        output.subMode="unknown";
        break;


    }

    //   QDateTime arrivalTimestampPredicted;
    //   QDateTime arrivalTimestampScheduled;

    //  bool delayIsAvailable=false;
    //  int delayMinutes=0;
    //  int delaySeconds=0;


    //   int routeType=0;
    //   bool routeIsNight=false;
    //   bool routeIsRegional=false;
    //   bool routeIsSubstituteTransport=false;

    //   QString stopPlatformCode="";

    //   bool tripIsCanceled=false;

    //   bool tripIsAtStop=false;
    return output;

}

/*
Vdv301Connection TypeConvertor::toVdv301Connection()
{
    qDebug()<<Q_FUNC_INFO;
    Vdv301Connection output;

    Vdv301DisplayContent displayContent;


    QString language="cs";



    displayContent.lineInformation.lineNameList<<Vdv301InternationalText(routeShortName,language);
    displayContent.destination.destinationNameList<<Vdv301InternationalText(tripHeadsign,language);

    output.vdv301displayContentList<<displayContent;

    output.scheduledDepartureTime=departureTimestampScheduled;
    output.expectedDepartureTime=departureTimestampPredicted;
    output.platform=stopPlatformCode;



    if(tripIsWheelchairAccessible)
    {
        // output.connectionProperty="Accessible";
    }


    switch(routeType)
    {
    case 0: //Tram, Streetcar, Light rail. Any light rail or street level system within a metropolitan area.
        output.mainMode="TramSubmode";

        if(routeIsRegional)
        {
            output.subMode="regionalTram";
        }
        else
        {
            output.subMode="localTram";
        }


        break;
    case 1: //Subway, Metro. Any underground rail system within a metropolitan area.
        output.mainMode="MetroSubmode";
        output.subMode="metro";

        break;
    case 2: //Rail. Used for intercity or long-distance travel.
        output.mainMode="RailSubmode";


        output.subMode="regionalRail";

        break;
    case 3: //Bus. Used for short- and long-distance bus routes.
        output.mainMode="BusSubmode";
        if(routeIsRegional)
        {
            output.subMode="regionalBus";
        }
        else
        {
            output.subMode="localBus";
        }


        break;
    case 4: //Ferry. Used for short- and long-distance boat service.
        output.mainMode="WaterSubmode";
        output.subMode="localPassengerFerry";

        break;
    case 5: //Cable tram. Used for street-level rail cars where the cable runs beneath the vehicle, e.g., cable car in San Francisco.

        output.mainMode="";
        output.subMode="";

        break;
    case 6: //Aerial lift, suspended cable car (e.g., gondola lift, aerial tramway). Cable transport where cabins, cars, gondolas or open chairs are suspended by means of one or more cables.
        output.mainMode="TelecabinSubmode";
        output.subMode="";

        break;


    case 7: //Funicular. Any rail system designed for steep inclines.

        output.mainMode="FunicularSubmode";
        output.subMode="";

        break;

    case 11: //Trolleybus. Electric buses that draw power from overhead wires using poles.

        output.mainMode="";
        output.subMode="";

        output.mainMode="BusSubmode";
        if(routeIsRegional)
        {
            output.subMode="regionalBus";
        }
        else
        {
            output.subMode="localBus";
        }

        break;


    case 12: //Monorail. Railway in which the track consists of a single rail or a beam.

        output.mainMode="";
        output.subMode="";

        break;


    default:
        output.mainMode="unknown";
        output.subMode="unknown";
        break;


    }

    //   QDateTime arrivalTimestampPredicted;
    //   QDateTime arrivalTimestampScheduled;

    //  bool delayIsAvailable=false;
    //  int delayMinutes=0;
    //  int delaySeconds=0;


    //   int routeType=0;
    //   bool routeIsNight=false;
    //   bool routeIsRegional=false;
    //   bool routeIsSubstituteTransport=false;

    //   QString stopPlatformCode="";

    //   bool tripIsCanceled=false;

    //   bool tripIsAtStop=false;
    return output;

}
*/

QVector<Connection> TypeConvertor::ConnectionGolemioV4ListToConnectionList(QVector<ConnectionGolemioV4> inputList)
{
    QVector<Connection> output;
    for (const ConnectionGolemioV4 &input : inputList)
    {
        Connection temporaryConnection;

        temporaryConnection.connectionProperty="";
        temporaryConnection.connectionType="";

        temporaryConnection.line.lineName=input.routeShortName;
        temporaryConnection.destinationName=input.tripHeadsign;
        temporaryConnection.scheduledDepartureTime=input.departureTimestampScheduled;
        temporaryConnection.expectedDepartureTime=input.departureTimestampPredicted;
        temporaryConnection.platform=input.stopPlatformCode;





        if(input.tripIsWheelchairAccessible)
        {
            temporaryConnection.connectionProperty="Accessible";
        }


        switch(input.routeType)
        {
        case 0: //Tram, Streetcar, Light rail. Any light rail or street level system within a metropolitan area.
            temporaryConnection.mainMode="TramSubmode";

            if(input.routeIsRegional)
            {
                temporaryConnection.subMode="regionalTram";
            }
            else
            {
                temporaryConnection.subMode="localTram";
            }


            break;
        case 1: //Subway, Metro. Any underground rail system within a metropolitan area.
            temporaryConnection.mainMode="MetroSubmode";
            temporaryConnection.subMode="metro";

            break;
        case 2: //Rail. Used for intercity or long-distance travel.
            temporaryConnection.mainMode="RailSubmode";


            temporaryConnection.subMode="regionalRail";

            break;
        case 3: //Bus. Used for short- and long-distance bus routes.
            temporaryConnection.mainMode="BusSubmode";
            if(input.routeIsRegional)
            {
                temporaryConnection.subMode="regionalBus";
            }
            else
            {
                temporaryConnection.subMode="localBus";
            }


            break;
        case 4: //Ferry. Used for short- and long-distance boat service.
            temporaryConnection.mainMode="WaterSubmode";
            temporaryConnection.subMode="localPassengerFerry";

            break;
        case 5: //Cable tram. Used for street-level rail cars where the cable runs beneath the vehicle, e.g., cable car in San Francisco.

            temporaryConnection.mainMode="";
            temporaryConnection.subMode="";

            break;
        case 6: //Aerial lift, suspended cable car (e.g., gondola lift, aerial tramway). Cable transport where cabins, cars, gondolas or open chairs are suspended by means of one or more cables.
            temporaryConnection.mainMode="TelecabinSubmode";
            temporaryConnection.subMode="";

            break;


        case 7: //Funicular. Any rail system designed for steep inclines.

            temporaryConnection.mainMode="FunicularSubmode";
            temporaryConnection.subMode="";

            break;

        case 11: //Trolleybus. Electric buses that draw power from overhead wires using poles.

            temporaryConnection.mainMode="";
            temporaryConnection.subMode="";

            temporaryConnection.mainMode="BusSubmode";
            if(input.routeIsRegional)
            {
                temporaryConnection.subMode="regionalBus";
            }
            else
            {
                temporaryConnection.subMode="localBus";
            }

            break;


        case 12: //Monorail. Railway in which the track consists of a single rail or a beam.

            temporaryConnection.mainMode="";
            temporaryConnection.subMode="";

            break;


        default:
            temporaryConnection.mainMode="unknown";
            temporaryConnection.subMode="unknown";
            break;


        }

        //   QDateTime arrivalTimestampPredicted;
        //   QDateTime arrivalTimestampScheduled;

        //  bool delayIsAvailable=false;
        //  int delayMinutes=0;
        //  int delaySeconds=0;


        //   int routeType=0;
        //   bool routeIsNight=false;
        //   bool routeIsRegional=false;
        //   bool routeIsSubstituteTransport=false;

        //   QString stopPlatformCode="";

        //   bool tripIsCanceled=false;

        //   bool tripIsAtStop=false;
        output<<  temporaryConnection;

        if(input.departureTimestampMinutes.count()>0)
        {
            for(const QString &minuteValue :input.departureTimestampMinutes)
            {
                temporaryConnection.scheduledDepartureTime=minutesToTimestamp(QDateTime::currentDateTime(), minuteValue);
                output<<temporaryConnection;
            }
        }
        else
        {
            output<<  temporaryConnection;
        }
    }

}



QDateTime TypeConvertor::minutesToTimestamp(QDateTime referenceDateTime,QString minutesString)
{
    if(minutesString.toInt()>0)
    {
        return referenceDateTime.addSecs(minutesString.toInt()*60);
    }
    else
    {
        return referenceDateTime;
    }

}

QString TypeConvertor::idUidZtoMpvNumber(int idu, int idz)
{
    QString number = QStringLiteral("%1%2").arg(idu, 4, 10, QLatin1Char('0')).arg(idz, 4, 10, QLatin1Char('0'));
    return number;
}




QString TypeConvertor::qTimeToMpvDatetime(QTime input)
{
    QDateTime output;
    output=QDateTime::currentDateTime();
    output.setTime(input);
    return output.toUTC().toString("yyyy-MM-ddThh:mm:ss");
}
