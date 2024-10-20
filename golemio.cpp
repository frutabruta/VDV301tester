#include "golemio.h"
#include "VDV301publisher/VDV301DataStructures/connectiongolemio.h"

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

    //adresa+="&minutesBefore=10"
    mParametry+="&minutesAfter=180";
    //adresa+= "&timeFrom=2021-01-21T06%3A00%3A00"
    mParametry+="&includeMetroTrains=true";
    //adresa+= "&preferredTimezone=Europe%252FPrague"
    mParametry+="&mode=departures";
    mParametry+="&order=real";
    mParametry+="&filter=routeOnce";
    mParametry+="&skip=canceled";
    //adresa+="&limit=0"
    //adresa+="&total=0"
    //adresa+= "&offset=0";

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
    mVstupniJson=mVstupniJson.fromJson(llooll);
}

QVector<ConnectionGolemio> Golemio::parsujDomDokument()
{
    qDebug()<<Q_FUNC_INFO;

    //   qDebug()<<"vstup:"<<vstupniJson["departures"];
    seznamPrestupuGolemio.clear();

    if(!mVstupniJson["departures"].isArray())
    {
        return seznamPrestupuGolemio;
    }
    QJsonArray odjezdy=mVstupniJson["departures"].toArray();

    if(odjezdy.isEmpty())
    {
        return seznamPrestupuGolemio;
    }



    foreach (QJsonValue var, odjezdy) {
        qDebug()<<"odjezd: "<<var["route"]["short_name"].toString() ;

        //var[""][""]

        ConnectionGolemio novy;


        if(var.toObject().contains("stop") )
        {
            novy.stopPlatformCode=var["stop"]["platform_code"].toString();
        }


        if(var.toObject().contains("route") )
        {
            novy.routeShortName=var["route"]["short_name"].toString();

            novy.routeIsSubstituteTransport=var["route"]["is_substitute_transport"].toBool();
            novy.routeIsNight=var["route"]["is_night"].toBool();
            novy.routeIsRegional=var["route"]["is_regional"].toBool();


            int type=var["route"]["type"].toInt();


            if(type<14)
            {
                qDebug()<<" druh dopravy existuje:"<<QString::number(type);
                novy.routeType=var["route"]["type"].toInt();
            }
            else
            {
                qDebug()<<"neznamy druh dopravy:"<<QString::number(type);
            }

        }


        if(var.toObject().contains("trip") )
        {

            novy.tripHeadsign=var["trip"]["headsign"].toString();
            novy.tripIsWheelchairAccessible=var["trip"]["is_wheelchair_accessible"].toBool();
        }

        //     novy.t=nodes.at(i).attributes().namedItem("t").nodeValue();

        if(var.toObject().contains("delay") )
        {
            novy.delayMinutes=var["delay"]["minutes"].toInt();
            novy.delaySeconds=var["delay"]["seconds"].toInt();
            novy.delayIsAvailable=var["delay"]["is_available"].toBool();
        }

        novy.arrivalTimestampScheduled=ConnectionMPV::qStringDoQDateTime(var["arrival_timestamp"]["scheduled"].toString());
        novy.arrivalTimestampPredicted=ConnectionMPV::qStringDoQDateTime(var["arrival_timestamp"]["predicted"].toString());

        novy.departureTimestampScheduled=ConnectionMPV::qStringDoQDateTime(var["departure_timestamp"]["scheduled"].toString());
        novy.departureTimestampPredicted=ConnectionMPV::qStringDoQDateTime(var["departure_timestamp"]["predicted"].toString());


        seznamPrestupuGolemio.append(novy);

    }




    return seznamPrestupuGolemio;
}

void Golemio::setKlic(const QByteArray &newKlic)
{
    mKlic = newKlic;
}

void Golemio::setParametry(const QString &newParametry)
{
    mParametry = newParametry;
}

void Golemio::setAdresa(const QString &newAdresa)
{
    mAdresa = newAdresa;
}


// zdroj https://stackoverflow.com/questions/7218851/making-an-http-get-under-qt

void Golemio::stahniMpvXml(int cisloCis, QString Ids)
{
    qDebug()<<Q_FUNC_INFO;

    // QString adresa = "http://www.mpvnet.cz/"+Ids+"/x/"+QString::number(cisloCis)+"?unite=true&ko=12702&pocet=24&t=true";

    QString adresa=mAdresa;
    adresa+="?cisIds="+QString::number(cisloCis);
    adresa+=mParametry;


    qDebug()<<"golemio adresa dotazu: "<<adresa;
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

QVector<ConnectionMPV> Golemio::vyfiltrujPrestupy(QVector<ConnectionMPV> vstupniPrestupy, Line linka)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<ConnectionMPV> vyfiltrovanePrestupy;

    foreach(ConnectionMPV aktualniPrestup, vstupniPrestupy)
    {
        if(aktualniPrestup.alias!=linka.lineName)
        {
            if(!jePrestupNaSeznamu(aktualniPrestup,vyfiltrovanePrestupy))
            {
                vyfiltrovanePrestupy.push_back(aktualniPrestup);
            }
        }
    }
    return vyfiltrovanePrestupy;
}


bool Golemio::jePrestupNaSeznamu(ConnectionMPV prestup, QVector<ConnectionMPV> seznamPrestupu)
{
    qDebug()<<Q_FUNC_INFO;


    foreach(ConnectionMPV testPrestup, seznamPrestupu)
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





