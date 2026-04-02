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

    bool composeFirstStopDeparture(StopPoint stopPoint2);
    bool composeLastStopAnnouncement(StopPoint vstup);
    void composeFareZoneChange();
    bool composeSpecialAnnouncement(AdditionalAnnoucement additionalAnnouncement);
    bool announceThisAndNextStop(StopPoint stopPoint1, StopPoint stopPoint2);

    QString applicationDirectory="";
    QString announcmentSoundFolderPath=applicationDirectory+"/hlaseni";

    void setPath(QString vstup); //unused
    void setApplicationDirectory(QString umisteni);


    bool announceThisStop(StopPoint thisStop);
    bool announceNextStop(StopPoint nextStop);
public slots:





private:
    QUrl getFilePathFromStopIds(int kodCis);

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
    QUrl zvukPrestupNaLetiste;
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
    QVector<QUrl> stopAttributesToFileQurlList(StopPoint stopPoint);

    //qt6

};

#endif // VOICEANNOUNCER_H
