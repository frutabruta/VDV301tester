#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>

class UdpReceiver : public QObject
{
    Q_OBJECT
public:
    UdpReceiver(quint16 port);
    void initSocket(quint16 port);

    int port() const;
    void setPort(int newPort);

private:
    QUdpSocket udpSocket;

    int mPort=0;

    void readPendingDatagrams();
signals:
    void signalDatagram(QNetworkDatagram data);
};

#endif // UDPRECEIVER_H
