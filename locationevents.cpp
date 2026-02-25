#include "locationevents.h"

LocationEvents::LocationEvents() {}


/*
Only works for S_JTSK!
*/
void LocationEvents::slotGnssUpdate(MapaBod coordinates)
{
    if(isAtStop)
    {
        if(coordinates.x==0.0) //check for sjtsk coordinates
        {
            if(!coordinatesTools.isPointInsideCircleWgs84(coordinates.lat,coordinates.lng,expectedStopPointDestination.stopPoint.lat,expectedStopPointDestination.stopPoint.lng,expectedStopPointDestination.stopPoint.radius))
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
            if(!coordinatesTools.isPointInsideCircleSjtsk(coordinates.x,coordinates.y,expectedStopPointDestination.stopPoint.sx,expectedStopPointDestination.stopPoint.sy,expectedStopPointDestination.stopPoint.radius))
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
        if(coordinates.x==0.0) //check for sjtsk coordinates
        {

            if(coordinatesTools.isPointInsideCircleWgs84(coordinates.lat,coordinates.lng,expectedStopPointDestination.stopPoint.lat,expectedStopPointDestination.stopPoint.lng,expectedStopPointDestination.stopPoint.radius))
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

            if(coordinatesTools.isPointInsideCircleSjtsk(coordinates.x,coordinates.y,expectedStopPointDestination.stopPoint.sx,expectedStopPointDestination.stopPoint.sy,expectedStopPointDestination.stopPoint.radius))
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
