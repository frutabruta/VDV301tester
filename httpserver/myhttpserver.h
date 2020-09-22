#ifndef MYHTTPSERVER
#define MYHTTPSERVER
#include <QCoreApplication>
#include <iostream>
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QIODevice>

class myHTTPserver : public QObject
{
    Q_OBJECT
public:
    myHTTPserver(quint16 ppp);
   // explicit myHTTPserver(QObject *parent = nullptr);
    ~myHTTPserver();
    QTcpSocket *socket ;
    void zapisDoPromenneGet(QByteArray vstup);
    void zapisDoSubscribe(QByteArray vstup);

    myHTTPserver();
public slots:
    void myConnection();
    void txRx();
    void closingClient();
private:
    qint64 bytesAvailable() const;
    QTcpServer *server;
    QByteArray obsahGet="";
    QByteArray obsahSubscribe="";

};
#endif // MYHTTPSERVER
