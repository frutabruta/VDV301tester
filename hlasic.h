#ifndef HLASIC_H
#define HLASIC_H

#include <QObject>
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QBuffer>

#include <QFileInfo>

class Hlasic: public QObject
{
     Q_OBJECT
public:
    Hlasic();
    void gong();


    //nepouzite
    int vyhlasZastavku(int kodOis, int kodCis);
    int vyhlasZastavku2(int kodOis, int kodCis);


    QMediaPlaylist * playlist = new QMediaPlaylist;


    bool kompletZastavka(int cis1, int ois1, int cis2, int ois2);    
    bool kompletKonecna(int cis1, int ois1);

    QString cestaProgramu="";
    QString cesta=cestaProgramu+"/hlaseni";
    //+"/hlaseni";
    //QByteArray pridejDoBufferu(QString cesta, QByteArray pole);
//   QByteArray *pridejDoBufferu(QUrl cesta2, QByteArray *pole);
    QByteArray *pridejDoBufferu(QUrl cesta2, QByteArray *pole);
    /*QString dilciVyhlaseniString(int kodOis, int kodCis);*/
    QMediaPlayer * player =  new QMediaPlayer(NULL, QMediaPlayer::StreamPlayback);

    void nastavCestu(QString vstup);
    void zmenUmisteniProgramu(QString umisteni);
    void prehrajJedenZvuk(QUrl soubor2);
    void pridejDoFrontyVyhlas(QVector<QUrl> vstup);
    void kompletZmenaTarifnihoPasma();
public slots:
    void zmenaStavuHlaseni(QMediaPlayer::State state);
    void vyhodPolozkuZeSeznamu(QVector<QUrl> &zasobnikAdres);
private:
    bool souborExistuje(QString path);
    QUrl dilciVyhlaseni(int kodOis, int kodCis);

    void prehrajCelySeznamUrl(QVector<QUrl> zasobnikAdres);

    QUrl zvukPristiZastavka;
    QUrl zvukGong;
    QUrl zvukKonecna;
    QUrl zvukProsimeVystupte;
    QUrl zvukZmenaPasma;
    QUrl zvukProsimPozor;

    void aktualizujCestyZvuku(QString cestaVnitrni);
    void prehrajPolozkuZeSeznamu(QVector<QUrl> zasobnikAdres);
    QVector<QUrl> frontaZvuku;
};

#endif // HLASIC_H
