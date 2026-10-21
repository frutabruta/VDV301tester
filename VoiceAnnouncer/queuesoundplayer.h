#ifndef QUEUESOUNDPLAYER_H
#define QUEUESOUNDPLAYER_H

#include <QObject>
#include <QWidget>
#include <QMediaPlayer>
#include <QBuffer>
#include <QFileInfo>
#include <QLoggingCategory>
#include <QDir>
#include <QStandardPaths>
#include <QCryptographicHash>

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

    void playOneSoundImmediately(QUrl file);
    void playInQueue(QVector<QUrl> input);


    bool fileExists(QString path);
    bool fileExists(QUrl path);
    QVector<QUrl> getOnlyExistingFiles(QVector<QUrl> input);
protected:
    void internalPlayOneSoundFromList(QVector<QUrl> soundList);

    QVector<QUrl> soundQueue;

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

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
private slots:
    void slotPlayStateChangedQt6(QMediaPlayer::PlaybackState state);
    void onPlayerError(QMediaPlayer::Error error, const QString &errorString);
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void playNextFromQueue();

private:
    QUrl makeLocalCopy(const QUrl &source);
    bool startPlaybackQt6(const QUrl &source);
    void onCurrentItemFinished();
    bool m_currentItemFinished = true;
#endif

};

#endif // QUEUESOUNDPLAYER_H
