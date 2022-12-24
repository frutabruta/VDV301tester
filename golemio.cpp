#include "golemio.h"

/*
 * Instalace https://

1. Install OpenSSL from Maintenance Tool.

62270ee4-db0f-4054-903f-bc925d6f3afe-image.png

2. Independently of your compiler, go to C:\Qt\Tools\OpenSSL\Win_x64\bin (if you have 64 bits application).

3. Copy libcrypto-1_1-x64.dll and libssl-1_1-x64.dll and paste in your release or debug application executable.

https://forum.qt.io/topic/127049/connecttohostencrypted-tls-initialization-failed/6
*/
Golemio::Golemio(QByteArray klic)
{
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(requestReceived(QNetworkReply*)));

    mKlic=klic ;

    tabulka[0]=2; //tramvaj
    tabulka[1]=1; //metro
    tabulka[2]=13; //vlak
    tabulka[3]=3; //bus
    tabulka[4]=12; //privoz
    //tabulka[5]=; lanová tramvaj
    tabulka[6]=8; //lanovka
    tabulka[7]=8; //pozemní lanovka
    tabulka[11]=18; //trolejbus
    //  tabulka[12]=; //jednokolejka




}
Golemio::~Golemio()
{
}

void Golemio::naplnVstupDokument(QByteArray vstup)
{
    qDebug()<<Q_FUNC_INFO;
    QByteArray llooll = vstup;
    //  QString s = QString::fromUtf8(vstup);
    //  QString str =QString::fromUtf8(vstup);
    // s = QString::fromUtf8(str.toLatin1());

    //  vstupniDomDokument.setContent(llooll);
    vstupniJson=vstupniJson.fromJson(llooll);
}

QVector<PrestupMPV> Golemio::parsujDomDokument()
{
    qDebug()<<Q_FUNC_INFO;

    //   qDebug()<<"vstup:"<<vstupniJson["departures"];
    seznamPrestupu.clear();

    if(!vstupniJson["departures"].isArray())
    {
        return seznamPrestupu;
    }
    QJsonArray odjezdy=vstupniJson["departures"].toArray();

    if(odjezdy.isEmpty())
    {
        return seznamPrestupu;
    }



    foreach (auto var, odjezdy) {
        qDebug()<<"odjezd: "<<var["route"]["short_name"].toString() ;

        //var[""][""]

        PrestupMPV novy;


        if(var.toObject().contains("stop") )
        {
            novy.stan=var["stop"]["platform_code"].toString();
        }


        if(var.toObject().contains("route") )
        {
            novy.lin=var["route"]["short_name"].toString();
            novy.alias=var["route"]["short_name"].toString();
            novy.nad=var["route"]["is_substitute_transport"].toBool();
            qDebug()<<"bum1";
            int type=var["route"]["type"].toInt();
            qDebug()<<"bum2";



            if(type<14)
            {
                qDebug()<<" druh dopravy existuje:"<<QString::number(type);
                novy.dd=tabulka[type]; //zmenit ciselnik!
            }
            else
            {
                qDebug()<<"neznamy druh dopravy:"<<QString::number(type);
            }

        }



        if(var.toObject().contains("trip") )
        {

            novy.smer=var["trip"]["headsign"].toString();
            novy.np=var["trip"]["is_wheelchair_accessible"].toBool();
        }

        //     novy.t=nodes.at(i).attributes().namedItem("t").nodeValue();
        if(var.toObject().contains("delay") )
        {
            novy.zpoz=var["delay"]["minutes"].toInt();
            novy.sled=var["delay"]["is_available"].toBool();
        }


        novy.odj=PrestupMPV::qStringDoQDateTime(var["arrival_timestamp"]["scheduled"].toString());
        novy.odjReal=PrestupMPV::qStringDoQDateTime(var["arrival_timestamp"]["predicted"].toString());
        //  novy.spoj=nodes.at(i).attributes().namedItem("spoj").nodeValue().toInt();


        //  novy.smer_c=nodes.at(i).attributes().namedItem("smer_c").nodeValue().toInt();

        seznamPrestupu.append(novy);
        qDebug()<<novy.smer;
    }


    /*
    QDomElement root = vstupniDomDokument.firstChildElement();
    QDomNodeList nodes = root.elementsByTagName("t").at(0).toElement().elementsByTagName("o");
    seznamPrestupu.clear();
    for (int i=0; i<nodes.count();i++)
    {
        PrestupMPV novy;
        novy.stan=nodes.at(i).attributes().namedItem("stan").nodeValue();
        novy.lin=nodes.at(i).attributes().namedItem("lin").nodeValue();
        novy.alias=nodes.at(i).attributes().namedItem("alias").nodeValue();
        novy.spoj=nodes.at(i).attributes().namedItem("spoj").nodeValue().toInt();
        novy.smer=nodes.at(i).attributes().namedItem("smer").nodeValue();
        novy.zpoz=nodes.at(i).attributes().namedItem("zpoz").nodeValue().toInt();
        QDateTime odjezd=PrestupMPV::qStringDoQDateTime( nodes.at(i).attributes().namedItem("odj").nodeValue());
        novy.odj=odjezd;
        novy.odjReal=PrestupMPV::posunTimeStampZpozdeni( odjezd, novy.zpoz );
        novy.sled=nodes.at(i).attributes().namedItem("sled").nodeValue().toInt();
        if (nodes.at(i).attributes().namedItem("np").nodeValue()=="true")
        {novy.np=1;}
        else
        {novy.np=0;}
        novy.nad=nodes.at(i).attributes().namedItem("nad").nodeValue().toInt();
        novy.t=nodes.at(i).attributes().namedItem("t").nodeValue();
        novy.dd=nodes.at(i).attributes().namedItem("dd").nodeValue().toInt();
        novy.smer_c=nodes.at(i).attributes().namedItem("smer_c").nodeValue().toInt();
        seznamPrestupu.append(novy);
        qDebug()<<novy.smer;

    }

    */

    return seznamPrestupu;
}


// zdroj https://stackoverflow.com/questions/7218851/making-an-http-get-under-qt

void Golemio::stahniMpvXml(int cisloCis, QString Ids)
{
    qDebug()<<Q_FUNC_INFO;

    // QString adresa = "http://www.mpvnet.cz/"+Ids+"/x/"+QString::number(cisloCis)+"?unite=true&ko=12702&pocet=24&t=true";

    QString adresa = "https://api.golemio.cz/v2/pid/departureboards/";
    adresa+="?cisIds="+QString::number(cisloCis);
    //adresa+="&minutesBefore=10"
    adresa+="&minutesAfter=60";
    //adresa+= "&timeFrom=2021-01-21T06%3A00%3A00"
    adresa+="&includeMetroTrains=true";
    //adresa+= "&preferredTimezone=Europe%252FPrague"
    adresa+="&mode=departures";
    adresa+="&order=real";
    adresa+="&filter=routeOnce";
    adresa+="&skip=canceled";
    //adresa+="&limit=0"
    //adresa+="&total=0"
    //adresa+= "&offset=0";


    qDebug()<<adresa;
    QNetworkRequest novyPozadavek;
    novyPozadavek.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    novyPozadavek.setUrl(QUrl(adresa));
    novyPozadavek.setRawHeader("X-Access-Token",mKlic);

    manager->get(novyPozadavek);
    //manager->get(QNetworkRequest(QUrl(adresa)));
}


QByteArray Golemio::requestReceived(QNetworkReply* replyoo)
{
    qDebug()<<Q_FUNC_INFO;
    QByteArray rawData = replyoo->readAll();
    QString textData(rawData);
    //  qDebug() << textData;
    qDebug().noquote()<<"kod: "<<replyoo->error()<< "raw: "<<rawData;
    this->stazenaData=rawData;
    emit stazeniHotovo();
    return rawData;
}

QVector<PrestupMPV> Golemio::vyfiltrujPrestupy(QVector<PrestupMPV> vstupniPrestupy, Linka linka)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<PrestupMPV> vyfiltrovanePrestupy;

    foreach(PrestupMPV aktualniPrestup, vstupniPrestupy)
    {
        if(aktualniPrestup.alias!=linka.LineName)
        {
            if(!jePrestupNaSeznamu(aktualniPrestup,vyfiltrovanePrestupy))
            {
                vyfiltrovanePrestupy.push_back(aktualniPrestup);
            }
        }
    }
    return vyfiltrovanePrestupy;
}


bool Golemio::jePrestupNaSeznamu(PrestupMPV prestup, QVector<PrestupMPV> seznamPrestupu)
{
    qDebug()<<Q_FUNC_INFO;


    foreach(PrestupMPV testPrestup, seznamPrestupu)
    {
        if(testPrestup.alias==prestup.alias)
        {
            if(testPrestup.smer_c==prestup.smer_c)
            {
                return true;
            }
        }
    }
    return false;

}





