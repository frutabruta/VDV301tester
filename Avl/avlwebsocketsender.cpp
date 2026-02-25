
#include "avlwebsocketsender.h"
#include <QDebug>

AvlWebsocketSender::AvlWebsocketSender(const QUrl &url, QObject *parent)
    : QObject(parent),
    m_socket(nullptr),
    m_url(QUrl()),
    m_pendingData(QString()),
    m_hasPendingData(false)
{
    // Assign inside body; add diagnostics
    if (!url.isValid())
    {
        qWarning() << "Sender: Invalid URL passed to constructor:" << url;
    }
    else
    {
        qInfo() << "Sender: URL passed to constructor:" << url.toString();
    }
    m_url = url;

    // Safe socket creation and parenting
    m_socket = new QWebSocket();
    m_socket->setParent(this);

    QObject::connect(m_socket, &QWebSocket::connected,
                     this, &AvlWebsocketSender::onConnected);

    QObject::connect(m_socket, &QWebSocket::disconnected,
                     this, &AvlWebsocketSender::onDisconnected);

    QObject::connect(m_socket, &QWebSocket::errorOccurred,
                     this, &AvlWebsocketSender::onErrorOccurred);
}

void AvlWebsocketSender::start()
{
    connectSocket();
}

void AvlWebsocketSender::stop()
{
    if (m_socket->state() == QAbstractSocket::ConnectedState ||
        m_socket->state() == QAbstractSocket::ConnectingState)
    {
        m_socket->close();
    }

    m_hasPendingData = false;
    m_pendingData.clear();
}

void AvlWebsocketSender::setUrl(const QUrl &url)
{
    if (!url.isValid())
    {
        qWarning() << "Sender: setUrl() received invalid QUrl:" << url;
    }
    m_url = url;
}

bool AvlWebsocketSender::isConnected() const
{
    return m_socket->state() == QAbstractSocket::ConnectedState;
}

void AvlWebsocketSender::setData(const QString &data)
{
    if (isConnected())
    {
        m_socket->sendTextMessage(data);
        qInfo().noquote() << "Sender: Sent message:" << data;
        return;
    }

    // Not connected: store one pending message and attempt to connect
    m_pendingData = data;
    m_hasPendingData = true;

    qInfo() << "Sender: Not connected, will send after connect. Connecting to"
            << m_url.toString();

    connectSocket();
}

void AvlWebsocketSender::connectSocket()
{
    if (!m_url.isValid())
    {
        qWarning() << "Sender: Cannot open WebSocket, invalid URL:" << m_url;
        return;
    }

    if (m_socket->state() == QAbstractSocket::UnconnectedState ||
        m_socket->state() == QAbstractSocket::ClosingState)
    {
        qInfo() << "Sender: Opening WebSocket to" << m_url.toString();
        m_socket->open(m_url);
    }
}

void AvlWebsocketSender::onConnected()
{
    qInfo() << "Sender: Connected to" << m_url.toString();

    if (m_hasPendingData && !m_pendingData.isEmpty())
    {
        m_socket->sendTextMessage(m_pendingData);
        qInfo().noquote() << "Sender: Sent pending message:" << m_pendingData;
        m_hasPendingData = false;
        m_pendingData.clear();
    }
}

void AvlWebsocketSender::onDisconnected()
{
    qInfo() << "Sender: Disconnected from" << m_url.toString();
}

void AvlWebsocketSender::onErrorOccurred(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error);
    qWarning() << "Sender: WebSocket error:" << m_socket->errorString();
}
