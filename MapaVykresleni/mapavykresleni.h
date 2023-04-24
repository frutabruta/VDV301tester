#ifndef MAPAVYKRESLENI_H
#define MAPAVYKRESLENI_H

#include <QVector>
#include <QString>
#include <QDebug>
#include <QUrl>
#include <QDesktopServices>
#include <QFile>
#include "VDV301struktury/cestaudaje.h"
#include "mnozinabodu.h"






class MapaVykresleni
{
public:

    MapaVykresleni();
    QVector<MnozinaBodu> seznamMnozin;
    void vypisGpsDoHtml(QVector<ZastavkaCil> seznam, bool vykreslitZnacku, bool vykresliSpojnici, bool vykresliTrasu,MnozinaBodu::SouradnicovySystem souradnicovySystem);

    void qstringDoSouboru(QString cesta, QString obsah);
    static MapaBod zastavkaCilToMapaBod(ZastavkaCil polozka);
    static QVector<MapaBod> seznamZastavkaCilToSeznamMapaBod(QVector<ZastavkaCil> seznamZastavek);
    void pridejMnozinu(QVector<MapaBod> seznamBodu, bool vykresliBody, bool vykresliSpojnici, bool vykresliTrasu, MnozinaBodu::SouradnicovySystem souradnicovySystem);
    void seznamMnozinDoJson(QVector<MnozinaBodu> seznamMnozin);
private:
    QString zkompletujHtml(QStringList body);
    QJsonObject slozRadek(QString title, QString content, QString lat, QString lng);
};



#endif // MAPAVYKRESLENI_H
