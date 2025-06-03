#ifndef LOCATIONEVENTS_H
#define LOCATIONEVENTS_H

#include <QObject>
#include "MapaVykresleni/mapabod.h"
#include "VDV301publisher/VDV301DataStructures/stoppointdestination.h"
#include "MapaVykresleni/coordinatestools.h"

class LocationEvents : public QObject
{
    Q_OBJECT
public:
    LocationEvents();

    StopPointDestination expectedStopPointDestination;

    CoordinatesTools coordinatesTools;

    bool isAtStop=false;
public slots:
    void slotGnssUpdate(MapaBod coordinates);
signals:
    void signalArrivedAtStop(StopPointDestination output);
    void signalDepartedStop(StopPointDestination output);
};

#endif // LOCATIONEVENTS_H
