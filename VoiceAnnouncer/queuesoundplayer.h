#ifndef QUEUESOUNDPLAYER_H
#define QUEUESOUNDPLAYER_H

#include <QObject>
#include <QWidget>
#include <QMediaPlayer>
#include <QBuffer>
#include <QFileInfo>
#include <QLoggingCategory>


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

    void playOneSoundImmediately(QUrl soubor2);
    void pridejDoFrontyVyhlas(QVector<QUrl> vstup);


    bool fileExists(QString path);
    bool fileExists(QUrl path);
    QVector<QUrl> getOnlyExistingFiles(QVector<QUrl> vstup);
protected:
    void internalPlayOneSoundFromList(QVector<QUrl> soundList);

    QVector<QUrl> frontaZvuku;

    bool m_isStartingPlayback = false;


#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    //Qt5
    QMediaPlayer player;
  //  QMediaPlayer * player =  new QMediaPlayer(NULL, QMediaPlayer::StreamPlayback);
#else
    //Qt6
    QMediaPlayer player; //qt6
    //QMediaPlayer *player =  new QMediaPlayer(NULL); //qt6

    QAudioOutput  audioOutput;

    //QAudioOutput  *audioOutput = new QAudioOutput;
#endif

private slots:


public slots:
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
              //Qt5
    void zmenaStavuHlaseni(QMediaPlayer::State state);
    void vyhodPolozkuZeSeznamu(QVector<QUrl> &zasobnikAdres);
#else
    //Qt6
    void slotPlayStateChangedQt6(QMediaPlayer::PlaybackState state);
    void popSoundFromListQt6(QVector<QUrl> &soundList);
#endif



};

#endif // QUEUESOUNDPLAYER_H
