#include "httpsluzba.h"

#include "qtzeroconf/qzeroconf.h"


HttpSluzba::HttpSluzba(QString nazevSluzby,QString typSluzby, int cisloPortu):HHserver(cisloPortu)
{
    qDebug()<<"HttpSluzba::HttpSluzba";
cisloPortuInterni=cisloPortu;
nazevSluzbyInterni=nazevSluzby;
typSluzbyInterni=typSluzby;
bonjourStartKomplet();
hlavickaInterni=vyrobHlavickuGet();
}

int HttpSluzba::nastavObsah(QByteArray vstup)
{
    qDebug()<<"HttpSluzba::nastavObsah";
    obsahInterni=vstup;
    this->nastavHttpObsah(vstup);
    return 1;
}

int HttpSluzba::nastavHlavicku(QByteArray vstup)
{
    qDebug()<<"HttpSluzba::nastavHlavicku";
    hlavickaInterni=vstup;
    return 1;
}


int HttpSluzba::nastavHttpObsah(QByteArray argumentXMLserveru)
{
    qDebug()<<"HttpSluzba::nastavHttpObsah";
    HHserver.zapisDoPromenneGet(argumentXMLserveru);
    return 1;
}

int HttpSluzba::zkombinujHlavickaTeloGet(QByteArray hlavicka,QByteArray telo)
{
    qDebug()<<"HttpSluzba::zkombinujHlavickaTelo()";
    QByteArray argumentXMLserveru="";

    argumentXMLserveru.append(hlavicka);
    argumentXMLserveru.append(telo);

    HHserver.zapisDoPromenneGet(argumentXMLserveru);

    return 1;
}

int HttpSluzba::zkombinujHlavickaTeloSubscribe(QByteArray hlavicka, QByteArray telo)
{
    qDebug()<<"HttpSluzba::zkombinujHlavickaTeloSubscribe()";
    QByteArray argumentXMLserveru="";

    argumentXMLserveru.append(hlavicka);
    argumentXMLserveru.append(telo);

    HHserver.zapisDoSubscribe(argumentXMLserveru);
    return 1;
}

int HttpSluzba::aktualizuj()
{
    qDebug()<<"HttpSluzba::aktualizuj()";
    //zkombinujHlavickaTeloGet(hlavickaInterni,vyrobGetResponseBody());
    zkombinujHlavickaTeloGet(vyrobHlavickuGet(),vyrobGetResponseBody());
    zkombinujHlavickaTeloSubscribe(vyrobHlavickuSubscribe(),vyrobSubscribeResponseBody(1));
    return 1;
}

QByteArray HttpSluzba::vyrobHlavickuGet()
{
    qDebug()<<"HttpSluzba::vyrobHlavicku()";
    QByteArray hlavicka;
    this->hlavickaInterni="";
    QByteArray argumentXMLserveru = "";
    hlavicka+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    hlavicka+=("Content-Type: application/xml\r\n");
    hlavicka+=("Connection: close\r\n");
    hlavicka+=("Pragma: no-cache\r\n");
    hlavicka+=("\r\n");
    return hlavicka;
}

QByteArray HttpSluzba::vyrobHlavickuSubscribe()
{
    qDebug()<<"HttpSluzba::vyrobHlavicku()";
    QByteArray hlavicka;
    this->hlavickaInterni="";
    QByteArray argumentXMLserveru = "";
    hlavicka+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    hlavicka+=("Content-Type: text/xml\r\n");
    hlavicka+=("Connection: close\r\n");
    hlavicka+=("Pragma: no-cache\r\n");
    hlavicka+=("\r\n");
    return hlavicka;
}


void HttpSluzba::bonjourStartKomplet()
{
    qDebug()<<"HttpSluzba::bonjourStartKomplet";
    //zeroConf.clearServiceTxtRecords();

    this->bonjourStartPublish(this->nazevSluzbyInterni,this->typSluzbyInterni,this->cisloPortuInterni,zeroConf);
    //this->bonjourStartPublish2("DeviceManagementService","_ibisip_http._tcp",47475,zeroConf2);
}



void HttpSluzba::bonjourStartPublish(QString nazevSluzby, QString typSluzby,int port, QZeroConf &instanceZeroConf)
{
    qDebug()<<"HttpSluzba::bonjourStartPublish"<<nazevSluzby;

    instanceZeroConf.addServiceTxtRecord("ver", "1.0");
    //zeroConf.addServiceTxtRecord("ZeroConf is nice too");
    instanceZeroConf.startServicePublish(nazevSluzby.toUtf8(), typSluzby.toUtf8(), "local", port);

}

QByteArray HttpSluzba::vyrobSubscribeResponseBody(int vysledek)
{
    qDebug()<<"HttpSluzba::vyrobSubscribeResponseBody";
    QByteArray textVysledek="true";
    if (vysledek!=1)
    {
        textVysledek="false";
    }
    QByteArray odpoved ="";
    odpoved+="<?xml version=\"1.0\" encoding=\"utf-16\"?>";
    odpoved+="<SubscribeResponse xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">";
    //odpoved+="<Active><Value>true</Value></Active>";
    odpoved+="<Active><Value>";
    odpoved+=textVysledek;
    odpoved+="</Value></Active>";
    odpoved+="</SubscribeResponse>";
    return odpoved;
}

QByteArray HttpSluzba::vyrobGetResponseBody()
{
    qDebug()<<"HttpSluzba::vyrobGetResponseBody()";
    return obsahInterni;

}
