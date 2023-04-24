#include "mapavykresleni.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


MapaVykresleni::MapaVykresleni()
{

}


QJsonObject MapaVykresleni::slozRadek(QString title, QString content, QString lat, QString lng)
{
    qDebug()<<Q_FUNC_INFO;
    QString vystup="";

    QJsonObject recordObject;
    recordObject.insert("title", QJsonValue::fromVariant(title));
    recordObject.insert("cont", QJsonValue::fromVariant(content));
    recordObject.insert("lat", QJsonValue::fromVariant(lat));
    recordObject.insert("lng", QJsonValue::fromVariant(lng));


    QJsonDocument doc(recordObject);
    qDebug() << doc.toJson();
    vystup=doc.toJson();
    return recordObject;
}

void MapaVykresleni::pridejMnozinu(QVector<MapaBod> seznamBodu , bool vykresliBody, bool vykresliSpojnici, bool vykresliTrasu, MnozinaBodu::SouradnicovySystem souradnicovySystem)
{
    qDebug()<<Q_FUNC_INFO;
    //QVector<ZastavkaCil> seznam
    MnozinaBodu mnozinaBodu;
    mnozinaBodu.seznamMapaBodu=seznamBodu;
    mnozinaBodu.vykresliBody=vykresliBody;
    mnozinaBodu.vykresliSpojnici=vykresliSpojnici;
    mnozinaBodu.vykresliTrasu=vykresliTrasu;
    mnozinaBodu.souradnicovySystem=souradnicovySystem;
    seznamMnozin.push_back(mnozinaBodu);
}

void MapaVykresleni::seznamMnozinDoJson(QVector<MnozinaBodu> seznamMnozin)
{
    qDebug()<<Q_FUNC_INFO;
    QJsonArray jRoot;


    foreach(MnozinaBodu polozkaMnozina, seznamMnozin)
    {
        QJsonObject jPolozka;
        jPolozka.insert("vykresliBody", QJsonValue::fromVariant(polozkaMnozina.vykresliBody));
        jPolozka.insert("vykresliSpojnici", QJsonValue::fromVariant(polozkaMnozina.vykresliSpojnici));
        jPolozka.insert("vykresliTrasu", QJsonValue::fromVariant(polozkaMnozina.vykresliTrasu));
        if(polozkaMnozina.souradnicovySystem==MnozinaBodu::J_STSK)
        {
          jPolozka.insert("souradnicovySystem", QJsonValue::fromVariant("J_STSK"));
         }
        else
        {
            jPolozka.insert("souradnicovySystem", QJsonValue::fromVariant("WGS84"));
        }

        QJsonArray radkyJSonArray;

        foreach(MapaBod polozkaZastavka, polozkaMnozina.seznamMapaBodu)
        {

            QJsonObject recordObject;
            recordObject.insert("title", QJsonValue::fromVariant(polozkaZastavka.hlavicka));
            recordObject.insert("cont", QJsonValue::fromVariant(polozkaZastavka.obsah));
            recordObject.insert("lat", QJsonValue::fromVariant(polozkaZastavka.lat));
            recordObject.insert("lng", QJsonValue::fromVariant(polozkaZastavka.lng));
            radkyJSonArray.append(recordObject);

        }
        jPolozka.insert("data", radkyJSonArray);
        jRoot.push_back(jPolozka);
    }


    QJsonDocument doc(jRoot);
    qDebug() << doc.toJson();

    qstringDoSouboru("data2.js","var dataj='"+doc.toJson(QJsonDocument::Compact)+"';");



    QDesktopServices::openUrl(QUrl("mapa.html", QUrl::TolerantMode));
}

MapaBod MapaVykresleni::zastavkaCilToMapaBod(ZastavkaCil polozka)
{
    qDebug()<<Q_FUNC_INFO;
    MapaBod vystup;
    vystup.obsah="cis:"+QString::number(polozka.zastavka.cisloCis);
    vystup.hlavicka=polozka.zastavka.NameLcd;
    vystup.lat=polozka.zastavka.lat;
    vystup.lng=polozka.zastavka.lng;

    return vystup;
}


QVector<MapaBod> MapaVykresleni::seznamZastavkaCilToSeznamMapaBod(QVector<ZastavkaCil> seznamZastavek)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<MapaBod> vystup;

    foreach(ZastavkaCil polozka, seznamZastavek)
    {
        MapaBod nacteno=zastavkaCilToMapaBod(polozka);
        vystup.push_back(nacteno);
    }
    return vystup;
}

void MapaVykresleni::vypisGpsDoHtml(QVector<ZastavkaCil> seznam, bool vykresliBody, bool vykresliSpojnici, bool vykresliTrasu, MnozinaBodu::SouradnicovySystem souradnicovySystem)
{
    qDebug()<<Q_FUNC_INFO;



    QJsonObject jRoot;


   jRoot.insert("vykresliBody", QJsonValue::fromVariant(vykresliBody));
   jRoot.insert("vykresliSpojnici", QJsonValue::fromVariant(vykresliSpojnici));
   jRoot.insert("vykresliTrasu", QJsonValue::fromVariant(vykresliTrasu));
   if(souradnicovySystem==MnozinaBodu::J_STSK)
   {
     jRoot.insert("souradnicovySystem", QJsonValue::fromVariant("J_STSK"));
    }
   else
   {
       jRoot.insert("souradnicovySystem", QJsonValue::fromVariant("WGS84"));
   }

    QJsonArray radkyJSonArray;

    foreach(ZastavkaCil polozka, seznam)
    {
        QString obsah="cis:"+QString::number(polozka.zastavka.cisloCis);
        QString title=polozka.zastavka.NameLcd;
        QJsonObject radekZnacka=slozRadek(title,obsah,polozka.zastavka.lat, polozka.zastavka.lng);
       // znackyList<<radekZnacka;

        radkyJSonArray.push_back(radekZnacka);

    }

   // qDebug().noquote().nospace()<<znackyList.join(",\n");

    jRoot.insert("data", radkyJSonArray);


    QJsonDocument doc(jRoot);
    qDebug() << doc.toJson();

    qstringDoSouboru("data2.js",doc.toJson(QJsonDocument::Compact));



    QDesktopServices::openUrl(QUrl("mapa.html", QUrl::TolerantMode));
}

QString MapaVykresleni::zkompletujHtml(QStringList body  )
{
    QString html;

    html+="var znacky = [\n";
    html+=body.join(",\n");
    html+="];";

    return html;
}

void MapaVykresleni::qstringDoSouboru(QString cesta, QString obsah)
{
    qDebug()<<Q_FUNC_INFO;

    QFile data(cesta);
    if (data.open(QFile::WriteOnly | QFile::Truncate))
    {
        qDebug()<<"soubor se povedlo otevrit";
        QTextStream out(&data);
        // out.setEncoding(QStringConverter::System);

        out<<obsah;
    }
    else
    {
        qDebug()<<"soubor se nepovedlo otevrit";
    }
}
