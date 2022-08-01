#ifndef HLASIC_H
#define HLASIC_H

#include <QObject>
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QBuffer>

#include <QFileInfo>
#include <VDV301struktury/specialnihlaseni.h>

class Hlasic: public QObject
{
     Q_OBJECT
public:
    Hlasic();

    QMediaPlayer * player =  new QMediaPlayer(NULL, QMediaPlayer::StreamPlayback);

    bool kompletZastavka(int cis1, int ois1, int cis2, int ois2);    
    bool kompletKonecna(int cis1, int ois1);
    void kompletZmenaTarifnihoPasma();
    bool kompletSpecialniHlaseni(SpecialniHlaseni specialniHlaseni);

    QString cestaProgramu="";
    QString cesta=cestaProgramu+"/hlaseni";

    void nastavCestu(QString vstup);
    void zmenUmisteniProgramu(QString umisteni);
    void prehrajJedenZvuk(QUrl soubor2);
    void pridejDoFrontyVyhlas(QVector<QUrl> vstup);

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

    void aktualizujCestyZvuku(QString cestaVnitrni);
    void prehrajPolozkuZeSeznamu(QVector<QUrl> zasobnikAdres);
    QVector<QUrl> frontaZvuku;
    QUrl najdiCestuSpecial(QString nazevSouboru);
};

#endif // HLASIC_H
