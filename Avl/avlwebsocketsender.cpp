#include "avlwebsocketsender.h"



AvlWebsocketSender::AvlWebsocketSender(quint16 port, QObject *parent)
    : QObject(parent),
    server(new QWebSocketServer(QStringLiteral("GNSS Server"),
                                QWebSocketServer::NonSecureMode, this)),
    timer(new QTimer(this))
{
    if (server->listen(QHostAddress::Any, port)) {
        connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    }

    connect(&timer, SIGNAL(timeout()), this, SLOT(sendGnssData()));
    timer.start(1000); // Send data every second
}

void AvlWebsocketSender::onNewConnection() {
    QWebSocket *clientSocket = server->nextPendingConnection();
    clients << clientSocket;

    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
}

void AvlWebsocketSender::onClientDisconnected() {
    QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());
    if (clientSocket) {
        clients.removeAll(clientSocket);
        clientSocket->deleteLater();
    }
}

void AvlWebsocketSender::sendGnssData() {
    /*
    QJsonObject gnssData;
    gnssData["latitude"]= latitude;
    gnssData["longitude"] = longitude;
    gnssData["center_map"] = centerMap;

    if(souradnicovySystem==MnozinaBodu::S_JTSK)
    {
        gnssData["coordinate_system"] = "S_JTSK";
    }
    else
    {
        gnssData["coordinate_system"] = "WGS84";
    }

    QJsonDocument doc(gnssData);
    QString jsonString = doc.toJson(QJsonDocument::Compact);
    */


    // for (QWebSocket *client : std::as_const(clients)) {  // didnt work for qt5
    for (QWebSocket *client : clients) {
        if (client->isValid()) {
            client->sendTextMessage(mData);
        }
    }
}

void AvlWebsocketSender::setData(QString data)
{
    /*
    latitude=newLatitude;
    longitude=newLongitude;
    souradnicovySystem=newCoordinateSystem;
    centerMap=newCenterMap;
    */
    mData=data;
    sendGnssData();
}


