#ifndef QUEUESOUNDPLAYER_H
#define QUEUESOUNDPLAYER_H

#include <QObject>
#include <QWidget>
#include <QMediaPlayer>
#include <QBuffer>
#include <QFileInfo>


#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
//Qt5

#else
//Qt6
#include <QAudioOutput>
#endif


class QueueSoundPlayer : public QObject
{
       Q_OBJECT
public:
    QueueSoundPlayer();





    void prehrajJedenZvuk(QUrl soubor2);
     void pridejDoFrontyVyhlas(QVector<QUrl> vstup);


protected:
void prehrajPolozkuZeSeznamu(QVector<QUrl> zasobnikAdres);

QVector<QUrl> frontaZvuku;


#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    //Qt5
    QMediaPlayer * player =  new QMediaPlayer(NULL, QMediaPlayer::StreamPlayback);
#else
    //Qt6
    QMediaPlayer *player =  new QMediaPlayer(NULL); //qt6
    QAudioOutput  *audioOutput = new QAudioOutput;
#endif

private slots:


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



};

#endif // QUEUESOUNDPLAYER_H
