#include "queuesoundplayer.h"

#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QTimer>

Q_LOGGING_CATEGORY(QueueSoundPlayerLog, "QueueSoundPlayer");


QueueSoundPlayer::QueueSoundPlayer()
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    : player(nullptr, QMediaPlayer::StreamPlayback)
#else
    : player(), audioOutput()
#endif
{


#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    //qt5
    connect(&player,&QMediaPlayer::stateChanged,this,&QueueSoundPlayer::zmenaStavuHlaseni);

#else
    //qt6
    player.setAudioOutput(&audioOutput);
    audioOutput.setVolume(1.0f); // Qt6: range is 0.0 - 1.0, not 0 - 100

    // playback state is only logged; queue advancing is driven by media status / errors
    connect(&player, &QMediaPlayer::playbackStateChanged, this, &QueueSoundPlayer::slotPlayStateChangedQt6);
    connect(&player, &QMediaPlayer::errorOccurred, this, &QueueSoundPlayer::onPlayerError);
    connect(&player, &QMediaPlayer::mediaStatusChanged, this, &QueueSoundPlayer::onMediaStatusChanged);

#endif


}


bool QueueSoundPlayer::fileExists(QString path)
{
    qCDebug(QueueSoundPlayerLog) <<  Q_FUNC_INFO;
    QFileInfo check_file(path); //zdroj:: https://stackoverflow.com/questions/10273816/how-to-check-whether-file-exists-in-qt-in-c
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile())
    {
        qCDebug(QueueSoundPlayerLog)<<"file "<<path<<" exists";
        return true;
    }
    else
    {
        qCDebug(QueueSoundPlayerLog)<<"file "<<path<<" does not exist";
        return false;
    }
}


bool QueueSoundPlayer::fileExists(QUrl path)
{
    qCDebug(QueueSoundPlayerLog) <<  Q_FUNC_INFO;
    return fileExists(path.toLocalFile());
}


void QueueSoundPlayer::playInQueue(QVector<QUrl> input)
{
    qCDebug(QueueSoundPlayerLog) <<  Q_FUNC_INFO;

    input=getOnlyExistingFiles(input);

    if(input.isEmpty())
    {
        qCDebug(QueueSoundPlayerLog)<<"no existing files in queue";
    }
    else
    {
        if (soundQueue.isEmpty())
        {
            qCDebug(QueueSoundPlayerLog)<<"sound queue was empty";
            soundQueue.append(input);
            internalPlayOneSoundFromList(soundQueue);
        }
        else

        {
            qCDebug(QueueSoundPlayerLog)<<"sound que was not empty";
            soundQueue.append(input);
        }
    }
}


QVector<QUrl> QueueSoundPlayer::getOnlyExistingFiles(QVector<QUrl> input)
{
    qCDebug(QueueSoundPlayerLog)<<Q_FUNC_INFO;
    QVector<QUrl> output;
    for (const QUrl &address : input)
    {
        if(fileExists(address))
        {
            output<<address;
            qCDebug(QueueSoundPlayerLog)<<"file does exist: "<<address;
        }
        else
        {
            qCDebug(QueueSoundPlayerLog)<<"file does NOT exist: "<<address;
        }
    }
    return output;
}





#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
//Qt5
void QueueSoundPlayer::vyhodPolozkuZeSeznamu(QVector<QUrl> &zasobnikAdres)
{
    qCDebug(QueueSoundPlayerLog) <<  Q_FUNC_INFO;
    if(!zasobnikAdres.isEmpty()&&(player.state()==QMediaPlayer::StoppedState) )
    {
        qCDebug(QueueSoundPlayerLog)<<"pocet polozek "<<zasobnikAdres.size();
        zasobnikAdres.removeFirst();
        internalPlayOneSoundFromList(zasobnikAdres);

    }
}

void QueueSoundPlayer::playOneSoundImmediately(QUrl soubor2)
{
    qCDebug(QueueSoundPlayerLog) <<  Q_FUNC_INFO<<" "<<soubor2.toString();
    player.setMedia(soubor2);

    player.play();
}

void QueueSoundPlayer::internalPlayOneSoundFromList(QVector<QUrl> soundList)
{
    qCDebug(QueueSoundPlayerLog) <<  Q_FUNC_INFO;
    if(!soundList.isEmpty())
    {
        playOneSoundImmediately(soundList.first());
    }
}

void QueueSoundPlayer::zmenaStavuHlaseni(QMediaPlayer::State state)
{
    qCDebug(QueueSoundPlayerLog) <<  Q_FUNC_INFO <<state;
    vyhodPolozkuZeSeznamu(frontaZvuku);

}



#else
//Qt6

// Copies a file reachable by QFile (including Android content:// URIs from the
// Storage Access Framework) into the app cache and returns a normal
// file:// URL. QMediaPlayer on Android cannot open SAF content URIs
// directly, but it can open a plain local file.
QUrl QueueSoundPlayer::makeLocalCopy(const QUrl &source)
{
    // Use toLocalFile(), NOT toString(): toString() keeps the double
    // encoding (%253A) of "file:content://...", which QFile cannot open.
    QString sourcePath;
    if (source.isLocalFile())
    {
        sourcePath = source.toLocalFile();
    }
    else
    {
        sourcePath = source.toString();
    }

    // Regular filesystem path (desktop, or real file on Android): use as is
    if (!sourcePath.startsWith(QStringLiteral("content://")))
    {
        return QUrl::fromLocalFile(sourcePath);
    }

    const QFileInfo sourceInfo(sourcePath);
    const qint64 sourceSize = sourceInfo.size();

    const QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+QStringLiteral("/sounds");
    QDir().mkpath(cacheDir);

    const QString hash = QString::fromLatin1(QCryptographicHash::hash(sourcePath.toUtf8(), QCryptographicHash::Md5).toHex());
    const QString localPath = cacheDir+QLatin1Char('/')+hash+QLatin1Char('.')+sourceInfo.suffix();

    // Reuse the cached copy only if it still has the same size as the source
    const QFileInfo localInfo(localPath);
    if (localInfo.exists() && sourceSize > 0 && localInfo.size() == sourceSize)
    {
        return QUrl::fromLocalFile(localPath);
    }

    QFile inputFile(sourcePath);
    if (!inputFile.open(QIODevice::ReadOnly))
    {
        qCWarning(QueueSoundPlayerLog) << "cannot open source" << sourcePath << inputFile.errorString();
        return QUrl();
    }

    const QByteArray data = inputFile.readAll();
    inputFile.close();

    if (data.isEmpty())
    {
        qCWarning(QueueSoundPlayerLog) << "source is empty" << sourcePath;
        return QUrl();
    }

    QFile outputFile(localPath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qCWarning(QueueSoundPlayerLog) << "cannot open cache file" << localPath << outputFile.errorString();
        return QUrl();
    }

    const qint64 written = outputFile.write(data);
    outputFile.close();

    if (written != data.size())
    {
        qCWarning(QueueSoundPlayerLog) << "cache write incomplete" << localPath;
        QFile::remove(localPath);
        return QUrl();
    }

    qCDebug(QueueSoundPlayerLog) << "copied" << sourcePath << "->" << localPath;
    return QUrl::fromLocalFile(localPath);
}


bool QueueSoundPlayer::startPlaybackQt6(const QUrl &source)
{
    // a new item begins; failures below must still be able to advance the queue
    m_currentItemFinished = false;

    if (!fileExists(source))
    {
        qCWarning(QueueSoundPlayerLog) << "file does not exist" << source;
        return false;
    }

    const QUrl playableUrl = makeLocalCopy(source);
    if (playableUrl.isEmpty())
    {
        return false;
    }

    qCDebug(QueueSoundPlayerLog) << "playing" << playableUrl;

    // Must clear source first - Qt6 QMediaPlayer treats setSource() with
    // the same URL as a no-op (same file twice in a row, e.g. gong).
    player.stop();
    player.setSource(QUrl());
    player.setSource(playableUrl);
    player.play();
    return true;
}


void QueueSoundPlayer::playOneSoundImmediately(QUrl file)
{
    qCDebug(QueueSoundPlayerLog) << Q_FUNC_INFO << " " << file.toString();

    if (!startPlaybackQt6(file))
    {
        // could not start: do not block the queue
        onCurrentItemFinished();
    }
}

void QueueSoundPlayer::internalPlayOneSoundFromList(QVector<QUrl> soundList)
{
    qCDebug(QueueSoundPlayerLog) <<  Q_FUNC_INFO;
    if(!soundList.isEmpty())
    {
        playOneSoundImmediately(soundList.first());
    }
}


// Called (once per item) when the current item ended or failed.
// The actual advance is deferred to the event loop, so we never change the
// source from inside a QMediaPlayer signal handler.
void QueueSoundPlayer::onCurrentItemFinished()
{
    if (m_currentItemFinished)
    {
        return; // errorOccurred and InvalidMedia both fire for one failure
    }
    m_currentItemFinished = true;
    QTimer::singleShot(0, this, &QueueSoundPlayer::playNextFromQueue);
}


// The head of soundQueue is the item that was just played: drop it and
// start the next playable one.
void QueueSoundPlayer::playNextFromQueue()
{
    qCDebug(QueueSoundPlayerLog) << Q_FUNC_INFO << "items:" << soundQueue.size();

    if (!soundQueue.isEmpty())
    {
        soundQueue.removeFirst();
    }

    while (!soundQueue.isEmpty())
    {
        if (startPlaybackQt6(soundQueue.first()))
        {
            return;
        }
        qCWarning(QueueSoundPlayerLog) << "skipping unplayable item" << soundQueue.first();
        soundQueue.removeFirst();
    }

    qCDebug(QueueSoundPlayerLog) << "sound queue finished";
}


void QueueSoundPlayer::slotPlayStateChangedQt6(QMediaPlayer::PlaybackState state)
{
    qCDebug(QueueSoundPlayerLog) << Q_FUNC_INFO << state;
}


void QueueSoundPlayer::onPlayerError(QMediaPlayer::Error error, const QString &errorString)
{
    qCWarning(QueueSoundPlayerLog) << "player error" << error << errorString;
    onCurrentItemFinished();
}


void QueueSoundPlayer::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    qCDebug(QueueSoundPlayerLog) << "media status" << status;

    if ((status == QMediaPlayer::EndOfMedia) || (status == QMediaPlayer::InvalidMedia))
    {
        onCurrentItemFinished();
    }
}

#endif