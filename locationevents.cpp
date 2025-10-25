#include "locationevents.h"

LocationEvents::LocationEvents() {}


/*
Only works for S_JTSK!
*/
void LocationEvents::slotGnssUpdate(MapaBod coordinates)
{
    if(isAtStop)
    {
        if(!coordinatesTools.isPointInsideCircle(coordinates.x,coordinates.y,expectedStopPointDestination.stopPoint.sx,expectedStopPointDestination.stopPoint.sy,expectedStopPointDestination.stopPoint.radius))
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
        if(coordinatesTools.isPointInsideCircle(coordinates.x,coordinates.y,expectedStopPointDestination.stopPoint.sx,expectedStopPointDestination.stopPoint.sy,expectedStopPointDestination.stopPoint.radius))
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
