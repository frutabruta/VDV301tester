#include "mapavykresleni.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


MapaVykresleni::MapaVykresleni()
{

}



void MapaVykresleni::pridejMnozinu(QVector<MapaBod> seznamBodu , bool vykresliBody, bool vykresliSpojnici, bool vykresliTrasu, bool vykresliRadius, MnozinaBodu::SouradnicovySystem souradnicovySystem)
{
    qDebug()<<Q_FUNC_INFO;
    //QVector<ZastavkaCil> seznam
    MnozinaBodu mnozinaBodu;
    mnozinaBodu.seznamMapaBodu=seznamBodu;
    mnozinaBodu.vykresliBody=vykresliBody;
    mnozinaBodu.vykresliSpojnici=vykresliSpojnici;
    mnozinaBodu.vykresliTrasu=vykresliTrasu;
    mnozinaBodu.vykresliRadius=vykresliRadius;
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
        jPolozka.insert("vykresliRadius", QJsonValue::fromVariant(polozkaMnozina.vykresliRadius));
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
            recordObject.insert("radius", QJsonValue::fromVariant(polozkaZastavka.radius));
            radkyJSonArray.append(recordObject);

        }
        jPolozka.insert("data", radkyJSonArray);
        jRoot.push_back(jPolozka);
    }


    QJsonDocument doc(jRoot);
    qDebug().noquote() << doc.toJson();

    qstringDoSouboru("data.js","var dataj='"+doc.toJson(QJsonDocument::Compact)+"';");



    QDesktopServices::openUrl(QUrl("mapa.html", QUrl::TolerantMode));
}

MapaBod MapaVykresleni::zastavkaCilToMapaBod(ZastavkaCil polozka)
{
    qDebug()<<Q_FUNC_INFO;
    MapaBod vystup;
    vystup.obsah="cis:"+QString::number(polozka.zastavka.cisloCis)+"<br>";
    vystup.obsah+="ASW zast.:"+QString::number(polozka.zastavka.cisloU)+"<br>";
    vystup.obsah+="ASW slp.:"+QString::number(polozka.zastavka.cisloZ)+"<br>";
    vystup.obsah+="radius:"+QString::number(polozka.zastavka.radius)+"<br>";
    vystup.hlavicka=polozka.zastavka.NameLcd;
    vystup.lat=polozka.zastavka.lat;
    vystup.lng=polozka.zastavka.lng;
    vystup.radius=polozka.zastavka.radius;

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




void MapaVykresleni::qstringDoSouboru(QString cesta, QString obsah)
{
    qDebug()<<Q_FUNC_INFO;

    QFile data(cesta);
    if (data.open(QFile::WriteOnly | QFile::Truncate))
    {
        qDebug()<<"soubor se povedlo otevrit";
        QTextStream out(&data);
        out.setCodec("UTF-8");
        // out.setAutoDetectUnicode(true);
        // out.setEncoding(QStringConverter::System);

        out<<obsah;
    }
    else
    {
        qDebug()<<"soubor se nepovedlo otevrit";
    }
}
