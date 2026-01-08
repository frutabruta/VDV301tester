#ifndef AVLWEBSOCKETSENDER_H
#define AVLWEBSOCKETSENDER_H

#include <QWebSocketServer>
#include <QWebSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>
#include <QObject>

class AvlWebsocketSender : public QObject
{
    Q_OBJECT
public:
    AvlWebsocketSender(quint16 port, QObject *parent);
    void setData(QString data);

public slots:
    void sendGnssData();
private slots:
    void onNewConnection();
    void onClientDisconnected();
private:
    QWebSocketServer *server;
    QList<QWebSocket *> clients;
    QTimer timer;
    QString mData="";
};

#endif // AVLWEBSOCKETSENDER_H
