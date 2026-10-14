#ifndef GNSSLOCATIONSERVICESUBSCRIBERDUMMY_H
#define GNSSLOCATIONSERVICESUBSCRIBERDUMMY_H
#include <QPoint>

#include "udpreceiver.h"


class GnssLocationServiceSubscriberDummy : public UdpReceiver
{
    Q_OBJECT
public:
    GnssLocationServiceSubscriberDummy();

private:
    void processTheDatagram(QNetworkDatagram datagram);
    
signals:
    void signalCoordinatesReceived(QPointF result);
};

#endif // GNSSLOCATIONSERVICESUBSCRIBERDUMMY_H
