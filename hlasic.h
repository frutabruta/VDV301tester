#ifndef HLASIC_H
#define HLASIC_H

#include <QObject>
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <QFileInfo>

class Hlasic
{
public:
    Hlasic();
    void gong();
    int vyhlasZastavku(int kodOis, int kodCis);
    int vyhlasZastavku2(int kodOis, int kodCis);

    QMediaPlaylist * playlist = new QMediaPlaylist;
    bool kompletZastavka(int cis1, int ois1, int cis2, int ois2);    
    bool kompletKonecna(int cis1, int ois1);
private:
    bool souborExistuje(QString path);
    QUrl dilciVyhlaseni(int kodOis, int kodCis);

};

#endif // HLASIC_H
