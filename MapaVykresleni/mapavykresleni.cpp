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

void MapaVykresleni::seznamMnozinDoJson(QVector<MnozinaBodu> seznamMnozin,  QString popis)
{
    qDebug()<<Q_FUNC_INFO;
    //QJsonObject jRoot;
    QJsonArray jSeznamPolozek;
    QJsonObject jRoot;




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
            recordObject.insert("kapka", QJsonValue::fromVariant(polozkaZastavka.kapka ));
            radkyJSonArray.append(recordObject);

        }
        jPolozka.insert("data", radkyJSonArray);
        jSeznamPolozek.push_back(jPolozka);
    }

    jRoot.insert("polozky",jSeznamPolozek);
    jRoot.insert("popis",popis);


    QJsonDocument doc(jRoot);

    //   qDebug().noquote() << doc.toJson();

    qstringDoSouboru("data.js","var dataj='"+doc.toJson(QJsonDocument::Compact)+"';");



    QDesktopServices::openUrl(QUrl("mapa.html", QUrl::TolerantMode));
}

MapaBod MapaVykresleni::zastavkaCilToMapaBod(ZastavkaCil polozka, QString kapka)
{
    qDebug()<<Q_FUNC_INFO;
    MapaBod vystup;

    vystup.obsah+="<table>";
    vystup.obsah+="<tr>";
    vystup.obsah+="<td>popis</td><td> "+polozka.zastavka.StopName+"</td>";
    vystup.obsah+="</tr>";
    vystup.obsah+="<tr>";
    vystup.obsah+="<td>cis</td><td> "+QString::number(polozka.zastavka.cisloCis)+"</td>";
    vystup.obsah+="</tr>";
    vystup.obsah+="<tr>";
    vystup.obsah+="<td>ASW zast. </td><td> "+QString::number(polozka.zastavka.cisloU)+"</td>";
    vystup.obsah+="</tr>";
    vystup.obsah+="<tr>";
    vystup.obsah+="<td>ASW slp.</td><td> "+QString::number(polozka.zastavka.cisloZ)+"</td>";
    vystup.obsah+="</tr>";
    vystup.obsah+="<tr>";
    vystup.obsah+="<td>radius</td><td> "+QString::number(polozka.zastavka.radius)+"</td>";
    vystup.obsah+="</tr>";
    vystup.obsah+="<tr>";
    vystup.obsah+="<td>nástupiště</td><td> "+polozka.zastavka.nastupiste+"</td>";
    vystup.obsah+="</tr>";
    vystup.obsah+="<tr>";
    vystup.obsah+="<td>odjezd</td><td> "+polozka.zastavka.odjezdQTime().toString("h:mm:ss")+"</td>";
    vystup.obsah+="</tr>";

    vystup.obsah+="</table>";

    /*
    vystup.obsah+="ASW zast.: "+QString::number(polozka.zastavka.cisloU)+"<br>";
    vystup.obsah+="ASW slp.: "+QString::number(polozka.zastavka.cisloZ)+"<br>";
    vystup.obsah+="radius: "+QString::number(polozka.zastavka.radius)+"<br>";
    vystup.obsah+="nástupiště: "+polozka.zastavka.nastupiste+"<br>";
    vystup.obsah+="odjezd: "+polozka.zastavka.odjezdQTime().toString("h:mm:ss")+"<br>";
*/
    vystup.hlavicka="<b>"+polozka.zastavka.NameLcd+"</b>";
    vystup.lat=polozka.zastavka.lat;
    vystup.lng=polozka.zastavka.lng;
    vystup.radius=polozka.zastavka.radius;
    vystup.kapka=kapka;

    return vystup;
}

QString MapaVykresleni::htmlTag(QString vstup, QString tag)
{
    return "<"+tag+">"+vstup+"</"+tag+">";
}

QString MapaVykresleni::spojDoTabulky(Spoj vstup)
{
    qDebug()<<Q_FUNC_INFO;
    QString vystup="<h1>vykreslení spoje</h1>";
    vystup+="<table>";
    vystup+="<tr><td>číslo linky ASW</td><td>"+QString::number(vstup.linka.c)+"</td></tr>";
    vystup+="<tr><td>alias linky</td><td>"+vstup.linka.LineName+"</td></tr>";
    vystup+="<tr><td>licenční číslo</td><td>"+vstup.linka.LineNumber+"</td></tr>";
    vystup+="<tr><td>spoj ROPID</td><td>"+QString::number(vstup.cisloRopid)+"</td></tr>";
     vystup+="<tr><td>spoj ID</td><td>"+QString::number(vstup.cislo)+"</td></tr>";
    if(!vstup.globalniSeznamZastavek.isEmpty())
    {
        qDebug()<<"pocetZastavek ve vektoru:"<<vstup.globalniSeznamZastavek.length();
        vystup+="<tr><td>ze zastávky</td><td>"+vstup.globalniSeznamZastavek.first().zastavka.NameLcd+"</td></tr>";
        vystup+="<tr><td>do zastávky</td><td>"+vstup.globalniSeznamZastavek.last().zastavka.NameLcd+"</td></tr>";

    }


    vystup+="</table>";
    return vystup;
}

QString MapaVykresleni::uzelDoTabulky(Zastavka vstup)
{
    QString vystup="<h1>vykreslení uzlu</h1>";
    vystup+="<table>";
    vystup+="<tr><td>uzel</td><td>"+QString::number(vstup.cisloU)+"</td></tr>";
    vystup+="<tr><td>sloupek</td><td>"+QString::number(vstup.cisloZ)+"</td></tr>";
    vystup+="<tr><td>název</td><td>"+vstup.NameLcd+"</td></tr>";
    vystup+="</table>";
    return vystup;
}

QVector<MapaBod> MapaVykresleni::seznamZastavkaCilToSeznamMapaBod(QVector<ZastavkaCil> seznamZastavek, bool poradi)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<MapaBod> vystup;
    int counter=1;

    foreach(ZastavkaCil polozka, seznamZastavek)
    {
        QString kapka="";
        if(poradi)
        {
            kapka=QString::number(counter);
        }
        else
        {
            kapka=QString::number(polozka.zastavka.cisloZ);
        }
        MapaBod nacteno=zastavkaCilToMapaBod(polozka,kapka);
        vystup.push_back(nacteno);
        counter++;
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

        out.setCodec("UTF-8"); //Qt5
         out.setAutoDetectUnicode(true);
        //out.setEncoding(QStringConverter::Utf8); //Qt6

        out<<obsah;
    }
    else
    {
        qDebug()<<"soubor se nepovedlo otevrit";
    }
}
