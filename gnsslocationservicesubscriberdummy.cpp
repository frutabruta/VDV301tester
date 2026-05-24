#include "gnsslocationservicesubscriberdummy.h"

#include <QDomDocument>

GnssLocationServiceSubscriberDummy::GnssLocationServiceSubscriberDummy() : UdpReceiver(7755)
{
    connect(this,&UdpReceiver::signalDatagram,this,&GnssLocationServiceSubscriberDummy::processTheDatagram);
}

void GnssLocationServiceSubscriberDummy::processTheDatagram(QNetworkDatagram datagram)
{
    qDebug().noquote()<<"datagram: "<<datagram.data();

    QDomDocument document;
    document.setContent(datagram.data());

    qreal x=document.firstChild().firstChildElement("longitude").firstChildElement("Degree").firstChildElement("Value").text().toDouble();
    qreal y=document.firstChild().firstChildElement("latitude").firstChildElement("Degree").firstChildElement("Value").text().toDouble();

    QPointF coordinates(x,y);

    qDebug()<<coordinates;

    emit signalCoordinatesReceived(coordinates);

}
