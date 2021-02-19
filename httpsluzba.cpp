#include "httpsluzba.h"

#include "qtzeroconf/qzeroconf.h"




HttpSluzba::HttpSluzba(QString nazevSluzby,QString typSluzby, int cisloPortu):InstanceNovehoServeru(cisloPortu)
{
    qDebug()<<"HttpSluzba::HttpSluzba";
    cisloPortuInterni=cisloPortu;
    nazevSluzbyInterni=nazevSluzby;
    typSluzbyInterni=typSluzby;
    bonjourStartKomplet();
    hlavickaInterni=vyrobHlavickuGet();
    //connect(&InstanceNovehoServeru,SIGNAL(zmenaObsahu()),this,SLOT(vypisObsahRequestu()));
    connect(&InstanceNovehoServeru,&NewHttpServer::zmenaObsahu,this,&HttpSluzba::vypisObsahRequestu);
}

int HttpSluzba::nastavObsah(QString vstup)
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


int HttpSluzba::nastavHttpObsah(QString argumentXMLserveru)
{
    qDebug()<<"HttpSluzba::nastavHttpObsah";
    InstanceNovehoServeru.zapisDoPromenneGet(argumentXMLserveru);
    return 1;
}

int HttpSluzba::aktualizuj()
{
    qDebug()<<"HttpSluzba::aktualizuj()";
    InstanceNovehoServeru.zapisDoPromenneGet(vyrobGetResponseBody());
    InstanceNovehoServeru.zapisDoSubscribe(vyrobSubscribeResponseBody(1));
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

QString HttpSluzba::vyrobHlavickuSubscribe()
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
}



void HttpSluzba::bonjourStartPublish(QString nazevSluzby, QString typSluzby,int port, QZeroConf &instanceZeroConf)
{
    qDebug()<<"HttpSluzba::bonjourStartPublish"<<nazevSluzby;
    instanceZeroConf.addServiceTxtRecord("ver", "1.0");
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
    odpoved+="<Active><Value>";
    odpoved+=textVysledek;
    odpoved+="</Value></Active>";
    odpoved+="</SubscribeResponse>";
    return odpoved;
}

QString HttpSluzba::vyrobGetResponseBody()
{
    qDebug()<<"HttpSluzba::vyrobGetResponseBody()";
    return obsahInterni;

}

void HttpSluzba::vypisObsahRequestu(QByteArray vysledek)
{
    QByteArray posledniRequest=InstanceNovehoServeru.bodyPozadavku;
    QDomDocument xmlrequest;
    xmlrequest.setContent(vysledek);
    QString adresa= xmlrequest.elementsByTagName("Client-IP-Address").at(0).toElement().firstChildElement().text() ;
    QString port= xmlrequest.elementsByTagName("ReplyPort").at(0).toElement().firstChildElement().text() ;
    qDebug()<<"prvni element "<<adresa<<" "<<port;
    qDebug()<<"body pozadavku"<<posledniRequest;
    qDebug()<<"vysledek"<<vysledek;
    QString kompletadresa="http://"+adresa+":"+port;
    QUrl adresaurl=kompletadresa;
    emit pridejSubscribera(adresaurl);
    //qDebug()<<obsahBody;
}
