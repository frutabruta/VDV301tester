#ifndef VOICEANNOUNCER_H
#define VOICEANNOUNCER_H


#include <VDV301publisher/VDV301DataStructures/additionalannoucement.h>
#include <VDV301publisher/VDV301DataStructures/stoppointdestination.h>
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
    bool announceBlindPersonBoarding();
    bool announceLineAndDestination(StopPointDestination thisStop);

public slots:


private:
    QUrl getFilePathFromStopIds(int kodCis);

    QUrl zvukPristiZastavka; //this stop is
    QUrl zvukGong; // this stop chime
    QUrl zvukGongPristi; // chime next stop
    QUrl zvukKonecna; // final stop
    QUrl zvukProsimeVystupte; // please get off
    QUrl zvukZmenaPasma; // fare zone change
    QUrl zvukProsimPozor; // attention please
    QUrl zvukNastupNeboVystupNevidomeho; // visually impaired person boarding
    QUrl zvukLinka;
    QUrl zvukSmer;

    QUrl zvukNaZnameni; // stop is on request
    QUrl zvukPrestupNaLinkyS; // transfer to train
    QUrl zvukPrestupNaMetro; // transfer to metro
    QUrl zvukPrestupNaPrivoz; // transfer to a ferry
    QUrl zvukPrestupNaLetiste; // transfer to an airport line

    //metro line names combinations
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


    void updateSoundFilesPaths(QString cestaVnitrni);


    QUrl getFilePathSpecial(QString fileName);
    QVector<QUrl> stopAttributesToFileQurlList(StopPoint stopPoint);

    QVector<QUrl> lineNameCreate(QString lineName);

    //qt6

    QUrl getFilePathNumber(QString fileName);
};

#endif // VOICEANNOUNCER_H
