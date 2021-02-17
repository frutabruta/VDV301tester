#ifndef NEWHTTPSERVER_H
#define NEWHTTPSERVER_H

#include <QObject>
#include <QWidget>

#include <QtHttpServer>

class NewHttpServer: public QObject
{
    Q_OBJECT
public:
    NewHttpServer(quint16 ppp);
    QHttpServer httpServer;
    int proved();
    quint16 cisloPortu=0;
    void zapisDoPromenneGet(QByteArray vstup);
    void zapisDoSubscribe(QByteArray vstup);
    QByteArray obsahGet="obsahGet";
    QByteArray obsahSubscribe="obsahSubscribe";
    int route(QByteArray &intObsahGet);
    int listen();
    QByteArray bodyPozadavku="xx";

private:
signals:
    void zmenaObsahu(QByteArray vysledek) ;
    //void zmenaObsahu() ;
};

#endif // NEWHTTPSERVER_H
