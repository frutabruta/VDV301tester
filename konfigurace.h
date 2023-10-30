#ifndef KONFIGURACE_H
#define KONFIGURACE_H

#include <QObject>
#include <QtXml>
#include <VDV301DataStructures/additionalannoucement.h>

class Konfigurace: public QObject
{
     Q_OBJECT


public:
    Konfigurace(QString cestaProgramu);
    void otevriSoubor();

    void vytvorDefaultniKonfiguraci();
    QString cestaHlaseni="";
    QVector<AdditionalAnnoucement> specialniHlaseni;
    int natahniSpecialniHlaseni(QDomDocument xmlko);


    int trvaniZobrazeniPasma=10000;
    int intervalStahovaniPrestupu=20000;
    int intervalAfterStopToBetweenStop=20000;
    int trvaniZobrazeniOznameni=10000;
signals:
    void odesliChybovouHlasku(QString chybovaHlaska);

private:
    QString cesta="";
    QString hlaseniDefaultniCesta="/hlaseni";



    bool souborExistuje(QString path);
    QString natahniCestaHlaseni(QDomDocument xmlko);
};

#endif // KONFIGURACE_H
