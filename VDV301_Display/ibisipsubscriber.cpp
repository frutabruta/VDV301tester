#include "ibisipsubscriber.h"


IbisIpSubscriber::IbisIpSubscriber(QString nazevSluzby,QString typSluzby, int cisloPortu) : InstanceNovehoServeru(cisloPortu)
{
qDebug()<<"HttpSluzba::HttpSluzba";
cisloPortuInterni=cisloPortu;
nazevSluzbyInterni=nazevSluzby;
typSluzbyInterni=typSluzby;
connect(&InstanceNovehoServeru,&NewHttpServer::prijemDat,this,&IbisIpSubscriber::vypisObsahRequestu);
}


void IbisIpSubscriber::vypisObsahRequestu(QString vysledek)
{
    qDebug()<<"IbisIpSubscriber::vypisObsahRequestu";
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
    //emit pridejSubscribera(adresaurl);
    //qDebug()<<obsahBody;
    emit dataNahrana(vysledek);
}
/*

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
*/



QByteArray IbisIpSubscriber::vyrobHlavickuOk()
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
