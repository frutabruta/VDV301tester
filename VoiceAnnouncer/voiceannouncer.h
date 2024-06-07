#ifndef VOICEANNOUNCER_H
#define VOICEANNOUNCER_H


#include <VDV301publisher/VDV301DataStructures/additionalannoucement.h>
#include <VDV301publisher/VDV301DataStructures/stoppoint.h>
#include "queuesoundplayer.h"

#include <QUrl>


class VoiceAnnouncer : public QueueSoundPlayer
{

public:
    VoiceAnnouncer();


    bool kompletKonecna(StopPoint vstup);
    void kompletZmenaTarifnihoPasma();
    bool kompletSpecialniHlaseni(AdditionalAnnoucement specialniHlaseni);
    bool announceThisAndNextStop(StopPoint zastavka1, StopPoint zastavka2);

    QString cestaProgramu="";
    QString cesta=cestaProgramu+"/hlaseni";

    void nastavCestu(QString vstup);
    void zmenUmisteniProgramu(QString umisteni);


    bool kompletOdjezdPrvniZastavka(StopPoint zastavka2);



    bool announceThisStop(StopPoint thisStop);
    bool announceNextStop(StopPoint nextStop);
public slots:





private:
    bool souborExistuje(QString path);
    QUrl najdiCestuZastavka(int kodOis, int kodCis);

    QUrl zvukPristiZastavka;
    QUrl zvukGong;
    QUrl zvukGongPristi;
    QUrl zvukKonecna;
    QUrl zvukProsimeVystupte;
    QUrl zvukZmenaPasma;
    QUrl zvukProsimPozor;

    QUrl zvukNaZnameni;
    QUrl zvukPrestupNaLinkyS;
    QUrl zvukPrestupNaMetro;
    QUrl zvukPrestupNaPrivoz;
    QUrl zvukMA;
    QUrl zvukMB;
    QUrl zvukMC;
    QUrl zvukMD;

    QUrl zvukMAaB;
    QUrl zvukMAaC;
    QUrl zvukMAaD;
    QUrl zvukMBaC;
    QUrl zvukMBaD;
    QUrl zvukMCaD;


    void aktualizujCestyZvuku(QString cestaVnitrni);


    QUrl najdiCestuSpecial(QString nazevSouboru);
    QVector<QUrl> priznakyDoSeznamu(StopPoint vstup);

    //qt6

};

#endif // VOICEANNOUNCER_H
