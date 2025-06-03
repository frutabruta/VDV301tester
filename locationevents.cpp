#include "locationevents.h"

LocationEvents::LocationEvents() {}



void LocationEvents::slotGnssUpdate(MapaBod coordinates)
{

    if(isAtStop)
    {
        if(!coordinatesTools.isPointInsideCircle(coordinates.lat,coordinates.lng,expectedStopPointDestination.stopPoint.sx,expectedStopPointDestination.stopPoint.sy,expectedStopPointDestination.stopPoint.radius))
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
        if(coordinatesTools.isPointInsideCircle(coordinates.lat,coordinates.lng,expectedStopPointDestination.stopPoint.sx,expectedStopPointDestination.stopPoint.sy,expectedStopPointDestination.stopPoint.radius))
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
