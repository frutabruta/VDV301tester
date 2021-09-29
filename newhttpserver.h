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
    void zapisDoPromenneGet(QString vstup);
    void zapisDoSubscribe(QString vstup);
    QString obsahGet="obsahGet";
    QString obsahSubscribe="<SubscribeResponse xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><Active><Value>true</Value></Active></SubscribeResponse>";
    int route(QString &intObsahGet, QMap<QString, QString> &obsahyBody);
    int listen();
    QByteArray bodyPozadavku="xx";
    QString obsahRoot="";


    int nastavObsahTela(QMap<QString, QString> vstup);
private:
    QString vyrobHlavickuOk();
    QMap<QString,QString> obsahTelaPole;
signals:
    void zmenaObsahu(QByteArray vysledek,QString struktura) ;
    void prijemDat(QString vysledek) ;
    //void zmenaObsahu() ;
};

#endif // NEWHTTPSERVER_H
