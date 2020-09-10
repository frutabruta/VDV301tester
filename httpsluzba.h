#ifndef HTTPSLUZBA_H
#define HTTPSLUZBA_H

#include <QObject>
#include "qzeroconf.h"
#include "httpserver/myhttpserver.h"

class HttpSluzba
{
public:
    HttpSluzba(QString nazevSluzby, QString typSluzby, int cisloPortu);
    int nastavObsah(QByteArray vstup);
    int nastavHlavicku(QByteArray vstup);
    void bonjourStartKomplet();
    int aktualizuj();
private:
    QZeroConf zeroConf;
    myHTTPserver HHserver;
    int cisloPortuInterni=0;
    QString nazevSluzbyInterni="";
    QByteArray obsahInterni="";
    QByteArray hlavickaInterni="";
    int delkaObsahu=0;
    void bonjourStartPublish(QString nazevSluzby, QString typSluzby, int port, QZeroConf &instanceZeroConf);
    QString typSluzbyInterni="_ibisip_http._tcp";
    int nastavHttpObsah(QByteArray argumentXMLserveru);
    QByteArray vyrobHlavicku();
    int zkombinujHlavickaTelo(QByteArray hlavicka, QByteArray telo);
};

#endif // HTTPSLUZBA_H
