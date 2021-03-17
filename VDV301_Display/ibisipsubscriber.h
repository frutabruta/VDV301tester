#ifndef IBISIPSUBSCRIBER_H
#define IBISIPSUBSCRIBER_H

#include <QObject>
#include <QtHttpServer>
#include <QtXml>
#include "../newhttpserver.h"

class IbisIpSubscriber : public QObject
{
    Q_OBJECT
public:
    explicit IbisIpSubscriber(QObject *parent = nullptr);

    IbisIpSubscriber(QString nazevSluzby, QString typSluzby, int cisloPortu);
    QByteArray vyrobHlavickuOk();
private:
    NewHttpServer InstanceNovehoServeru;
    int cisloPortuInterni=0;
    QString nazevSluzbyInterni="";
    QString obsahInterni="";
    QString hlavickaInterni="";
    QString typSluzbyInterni="_ibisip_http._tcp";

signals:
    int dataNahrana (QString vysledek);

public slots:
    //void vypisObsahRequestu();
    void vypisObsahRequestu(QString vysledek);

};

#endif // IBISIPSUBSCRIBER_H
