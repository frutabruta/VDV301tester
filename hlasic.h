#ifndef HLASIC_H
#define HLASIC_H

#include <QObject>
#include <QWidget>
#include <QMediaPlayer>
//#include <QMediaPlaylist>
#include <QBuffer>

#include <QFileInfo>
#include <VDV301DataStructures/additionalannoucement.h>
#include <VDV301DataStructures/stoppoint.h>


#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
//Qt5

#else
//Qt6
#include <QAudioOutput>
#endif



class Hlasic: public QObject
{
    Q_OBJECT
public:
    Hlasic();





    bool kompletKonecna(StopPoint vstup);
    void kompletZmenaTarifnihoPasma();
    bool kompletSpecialniHlaseni(AdditionalAnnoucement specialniHlaseni);
    bool kompletZastavka(StopPoint zastavka1, StopPoint zastavka2);

    QString cestaProgramu="";
    QString cesta=cestaProgramu+"/hlaseni";

    void nastavCestu(QString vstup);
    void zmenUmisteniProgramu(QString umisteni);
    void prehrajJedenZvuk(QUrl soubor2);
    void pridejDoFrontyVyhlas(QVector<QUrl> vstup);


    bool kompletOdjezdPrvniZastavka(StopPoint zastavka2);

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    //Qt5
    QMediaPlayer * player =  new QMediaPlayer(NULL, QMediaPlayer::StreamPlayback);
#else
    //Qt6
    QMediaPlayer *player =  new QMediaPlayer(NULL); //qt6
    QAudioOutput  *audioOutput = new QAudioOutput;
#endif


public slots:


#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    //Qt5
    void zmenaStavuHlaseni(QMediaPlayer::State state);
    void vyhodPolozkuZeSeznamu(QVector<QUrl> &zasobnikAdres);
#else
    //Qt6
    void zmenaStavuHlaseniQt6(QMediaPlayer::PlaybackState state);
    void vyhodPolozkuZeSeznamuQt6(QVector<QUrl> &zasobnikAdres);
#endif



private:
    bool souborExistuje(QString path);
    QUrl najdiCestuZastavka(int kodOis, int kodCis);

    QUrl zvukPristiZastavka;
    QUrl zvukGong;
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
    void prehrajPolozkuZeSeznamu(QVector<QUrl> zasobnikAdres);
    QVector<QUrl> frontaZvuku;
    QUrl najdiCestuSpecial(QString nazevSouboru);
    QVector<QUrl> priznakyDoSeznamu(StopPoint vstup);

    //qt6

};

#endif // HLASIC_H
