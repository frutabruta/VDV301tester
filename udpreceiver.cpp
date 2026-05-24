#include "udpreceiver.h"


UdpReceiver::UdpReceiver(quint16 port)
{
    mPort=port;
    initSocket(mPort);
}



void UdpReceiver::initSocket(quint16 port)
{
    // = new QUdpSocket(this);
    udpSocket.bind(QHostAddress::LocalHost, port);
    connect(&udpSocket, &QUdpSocket::readyRead,
            this, &UdpReceiver::readPendingDatagrams);
}

int UdpReceiver::port() const
{
    return mPort;
}

void UdpReceiver::setPort(int newPort)
{
    mPort = newPort;
}

void UdpReceiver::readPendingDatagrams()
{
    qDebug()<<"wwwww";
    while (udpSocket.hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket.receiveDatagram();
        emit signalDatagram(datagram);
    }
}

