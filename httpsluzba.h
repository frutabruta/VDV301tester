#ifndef HTTPSLUZBA_H
#define HTTPSLUZBA_H

#include <QObject>
#include <QtXml>
#include "qzeroconf.h"

#include <QtHttpServer>
#include "newhttpserver.h"

class HttpSluzba: public QObject
{
    Q_OBJECT
public:
    HttpSluzba(QString nazevSluzby, QString typSluzby, int cisloPortu);
    int nastavObsah(QString vstup);
    int nastavHlavicku(QByteArray vstup);
    void bonjourStartKomplet();
    int aktualizuj();
    QByteArray vyrobSubscribeResponseBody(int vysledek);
private:
    QZeroConf zeroConf;

    NewHttpServer InstanceNovehoServeru;
    int cisloPortuInterni=0;
    QString nazevSluzbyInterni="";
    QString obsahInterni="";
    QString hlavickaInterni="";
    int delkaObsahu=0;
    void bonjourStartPublish(QString nazevSluzby, QString typSluzby, int port, QZeroConf &instanceZeroConf);
    QString typSluzbyInterni="_ibisip_http._tcp";
    int nastavHttpObsah(QString argumentXMLserveru);
    QByteArray vyrobHlavickuGet();
    /*
    int zkombinujHlavickaTeloGet(QString hlavicka, QString telo);

    int zkombinujHlavickaTeloSubscribe(QString hlavicka, QString telo);
    */
    QString vyrobGetResponseBody();
    QString vyrobHlavickuSubscribe();

public slots:
    //void vypisObsahRequestu();
    void vypisObsahRequestu(QByteArray vysledek);

signals:
    void pridejSubscribera(QUrl adresaSubscribera);

};

#endif // HTTPSLUZBA_H
