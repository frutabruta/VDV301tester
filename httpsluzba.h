#ifndef HTTPSLUZBA_H
#define HTTPSLUZBA_H

#include <QObject>
#include <QtXml>
#include "qzeroconf.h"
#include "httpserver/myhttpserver.h"

#include <QtHttpServer>
#include "newhttpserver.h"

class HttpSluzba: public QObject
{
    Q_OBJECT
public:
    HttpSluzba(QString nazevSluzby, QString typSluzby, int cisloPortu);
    int nastavObsah(QByteArray vstup);
    int nastavHlavicku(QByteArray vstup);
    void bonjourStartKomplet();
    int aktualizuj();
    QByteArray vyrobSubscribeResponseBody(int vysledek);
private:
    QZeroConf zeroConf;
    myHTTPserver HHserver;

    NewHttpServer InstanceNovehoServeru;
    int cisloPortuInterni=0;
    QString nazevSluzbyInterni="";
    QByteArray obsahInterni="";
    QByteArray hlavickaInterni="";
    int delkaObsahu=0;
    void bonjourStartPublish(QString nazevSluzby, QString typSluzby, int port, QZeroConf &instanceZeroConf);
    QString typSluzbyInterni="_ibisip_http._tcp";
    int nastavHttpObsah(QByteArray argumentXMLserveru);
    QByteArray vyrobHlavickuGet();
    int zkombinujHlavickaTeloGet(QByteArray hlavicka, QByteArray telo);

    int zkombinujHlavickaTeloSubscribe(QByteArray hlavicka, QByteArray telo);
    QByteArray vyrobGetResponseBody();
    QByteArray vyrobHlavickuSubscribe();

public slots:
    //void vypisObsahRequestu();
    void vypisObsahRequestu(QByteArray vysledek);

signals:
    void pridejSubscribera(QUrl adresaSubscribera);

};

#endif // HTTPSLUZBA_H
