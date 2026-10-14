#include "locationevents.h"

Q_LOGGING_CATEGORY(LocationEventsLog, "LocationEvents");

LocationEvents::LocationEvents() {}


void LocationEvents::slotGnssUpdateSjtsk(QPointF coordinates)
{
    qCDebug(LocationEventsLog)<<Q_FUNC_INFO;
    if(isAtStop)
    {

        //using S-JTSK radius
        if(!coordinatesTools.isPointInsideCircleSjtsk(coordinates,QPointF(expectedStopPointDestination.stopPoint.sx,expectedStopPointDestination.stopPoint.sy),expectedStopPointDestination.stopPoint.radius))
        {
            isAtStop=false;
            emit signalDepartedStop(expectedStopPointDestination);
            //   eventDeparture();
        }
        else
        {
            isAtStop=true;
        }


    }
    else
    {

        // no polygon, using radius

        //using S-JTSK radius
        if(coordinatesTools.isPointInsideCircleSjtsk(coordinates,QPointF(expectedStopPointDestination.stopPoint.sx,expectedStopPointDestination.stopPoint.sy),expectedStopPointDestination.stopPoint.radius))
        {
            isAtStop=true;
            emit signalArrivedAtStop(expectedStopPointDestination);
            //   eventDeparture();
        }
        else
        {
            isAtStop=false;
        }

    }
}

void LocationEvents::slotGnssUpdateWgs84(QPointF coordinates)
{
    qCDebug(LocationEventsLog)<<Q_FUNC_INFO;
    if(isAtStop)
    {

        if(!expectedStopPointDestination.stopPoint.polygonWgs84_out.isEmpty())
        {
            //using polygon
            if(!expectedStopPointDestination.stopPoint.polygonWgs84_out.containsPoint(coordinates,Qt::OddEvenFill))
            {
                isAtStop=false;
                emit signalDepartedStop(expectedStopPointDestination);
                //   eventDeparture();
            }
            else
            {
                isAtStop=true;
            }
        }
        else
        {
            //using WGS84 radius
            if(!coordinatesTools.isPointInsideCircleWgs84(coordinates.y(),coordinates.x(),expectedStopPointDestination.stopPoint.lat,expectedStopPointDestination.stopPoint.lng,expectedStopPointDestination.stopPoint.radius))
            {
                isAtStop=false;
                emit signalDepartedStop(expectedStopPointDestination);
                //   eventDeparture();
            }
            else
            {
                isAtStop=true;
            }
        }
    }
    else
    {

        if(!expectedStopPointDestination.stopPoint.polygonWgs84.isEmpty())
        {
            //using polygon
            if(expectedStopPointDestination.stopPoint.polygonWgs84.containsPoint(coordinates,Qt::OddEvenFill))
            {
                isAtStop=true;
                emit signalArrivedAtStop(expectedStopPointDestination);
                //   eventDeparture();
            }
            else
            {
                isAtStop=false;
            }
        }
        else
        {
            //using WGS84 radius
            if(coordinatesTools.isPointInsideCircleWgs84(coordinates.y(),coordinates.x(),expectedStopPointDestination.stopPoint.lat,expectedStopPointDestination.stopPoint.lng,expectedStopPointDestination.stopPoint.radius))
            {
                isAtStop=true;
                emit signalArrivedAtStop(expectedStopPointDestination);
                //   eventDeparture();
            }
            else
            {
                isAtStop=false;
            }
        }
    }
}
