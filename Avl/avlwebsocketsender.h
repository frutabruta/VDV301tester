
#ifndef AVLWEBSOCKETSENDER_H
#define AVLWEBSOCKETSENDER_H

#include <QObject>
#include <QWebSocket>
#include <QUrl>
#include <QString>
#include <QAbstractSocket>

class AvlWebsocketSender : public QObject
{
    Q_OBJECT

public:
    explicit AvlWebsocketSender(const QUrl &url, QObject *parent = nullptr);

    void start();
    void stop();
    void setUrl(const QUrl &url);
    bool isConnected() const;
    void setData(const QString &data); // on-demand send

private slots:
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError error);

private:
    void connectSocket();

private:
    QWebSocket *m_socket;
    QUrl m_url;
    QString m_pendingData;
    bool m_hasPendingData;
};

#endif // AVLWEBSOCKETSENDER_H
