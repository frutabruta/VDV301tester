#ifndef HLASIC_H
#define HLASIC_H

#include <QObject>
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QBuffer>

#include <QFileInfo>
#include <VDV301struktury/specialnihlaseni.h>
#include <VDV301struktury/zastavka.h>

class Hlasic: public QObject
{
     Q_OBJECT
public:
    Hlasic();

    QMediaPlayer * player =  new QMediaPlayer(NULL, QMediaPlayer::StreamPlayback);


    bool kompletKonecna(Zastavka vstup);
    void kompletZmenaTarifnihoPasma();
    bool kompletSpecialniHlaseni(SpecialniHlaseni specialniHlaseni);
    bool kompletZastavka(Zastavka zastavka1, Zastavka zastavka2);

    QString cestaProgramu="";
    QString cesta=cestaProgramu+"/hlaseni";

    void nastavCestu(QString vstup);
    void zmenUmisteniProgramu(QString umisteni);
    void prehrajJedenZvuk(QUrl soubor2);
    void pridejDoFrontyVyhlas(QVector<QUrl> vstup);


    bool kompletOdjezdPrvniZastavka(Zastavka zastavka2);
public slots:
    void zmenaStavuHlaseni(QMediaPlayer::State state);
    void vyhodPolozkuZeSeznamu(QVector<QUrl> &zasobnikAdres);
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
    QVector<QUrl> priznakyDoSeznamu(Zastavka vstup);
};

#endif // HLASIC_H
