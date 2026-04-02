#include "queuesoundplayer.h"

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
    connect(&player,&QMediaPlayer::playbackStateChanged,this,&QueueSoundPlayer::slotPlayStateChangedQt6);
    player.setAudioOutput(&audioOutput);
    audioOutput.setVolume(50);
#endif


}


bool QueueSoundPlayer::fileExists(QString path)
{
    qCDebug(QueueSoundPlayerLog) <<  Q_FUNC_INFO;
    QFileInfo check_file(path); //zdroj:: https://stackoverflow.com/questions/10273816/how-to-check-whether-file-exists-in-qt-in-c
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        qCDebug(QueueSoundPlayerLog)<<"soubor "<<path<<" existuje";
        return true;
    } else {
        qCDebug(QueueSoundPlayerLog)<<"soubor "<<path<<" neexistuje";
        return false;
    }
}


bool QueueSoundPlayer::fileExists(QUrl path)
{
    qCDebug(QueueSoundPlayerLog) <<  Q_FUNC_INFO;

    QString compoundPath=path.toLocalFile() ;
    QFileInfo check_file(compoundPath); //zdroj:: https://stackoverflow.com/questions/10273816/how-to-check-whether-file-exists-in-qt-in-c
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        qCDebug(QueueSoundPlayerLog)<<"soubor "<<compoundPath<<" existuje";
        return true;
    } else {
        qCDebug(QueueSoundPlayerLog)<<"soubor "<<compoundPath<<" neexistuje";
        return false;
    }
}


void QueueSoundPlayer::pridejDoFrontyVyhlas(QVector<QUrl> vstup)
{
    qCDebug(QueueSoundPlayerLog) <<  Q_FUNC_INFO;

    vstup=getOnlyExistingFiles(vstup);

    if(vstup.isEmpty())
    {
        qCDebug(QueueSoundPlayerLog)<<"no existing files in queue";

    }
    else
    {
        if (frontaZvuku.isEmpty())
        {
            qCDebug(QueueSoundPlayerLog)<<"fronta zvuku byla prazdna";
            frontaZvuku.append(vstup);
            internalPlayOneSoundFromList(frontaZvuku);
        }
        else

        {
            qCDebug(QueueSoundPlayerLog)<<"fronta zvuku nebyla prazdna";
            frontaZvuku.append(vstup);
        }
    }
}


QVector<QUrl> QueueSoundPlayer::getOnlyExistingFiles(QVector<QUrl> vstup)
{
    qCDebug(QueueSoundPlayerLog)<<Q_FUNC_INFO;
    QVector<QUrl> output;
    for (const QUrl &address : vstup) {
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
void QueueSoundPlayer::slotPlayStateChangedQt6(QMediaPlayer::PlaybackState state)
{
    qCDebug(QueueSoundPlayerLog) <<  Q_FUNC_INFO <<state;
    popSoundFromListQt6(frontaZvuku);
}




void QueueSoundPlayer::playOneSoundImmediately(QUrl soubor2)
{
    qCDebug(QueueSoundPlayerLog) << " " << soubor2.toString();

    if (fileExists(soubor2))
    {
        m_isStartingPlayback = true;  // guard against spurious StoppedState

        // Must clear source first — Qt6 QMediaPlayer treats setSource() with
        // the same URL as a no-op, causing play() to misbehave when the same
        // file appears consecutively in the queue (e.g. gong played twice).
        player.setSource(QUrl());
        player.setSource(soubor2);
        m_isStartingPlayback = false;
        player.play();
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

void QueueSoundPlayer::popSoundFromListQt6(QVector<QUrl> &soundList)
{
    qCDebug(QueueSoundPlayerLog) << Q_FUNC_INFO;
    qCDebug(QueueSoundPlayerLog) << "playback state " << player.playbackState();

    if (m_isStartingPlayback)  // ignore spurious signals during source change
    {
        qCDebug(QueueSoundPlayerLog) << "ignoring spurious StoppedState during source change";
        return;
    }

    if ((!soundList.isEmpty()) && (player.playbackState() == QMediaPlayer::StoppedState))
    {
        qCDebug(QueueSoundPlayerLog) << "pocet polozek " << soundList.size();
        soundList.removeFirst();
        internalPlayOneSoundFromList(soundList);
    }
    else if (soundList.isEmpty())
    {
        qCDebug(QueueSoundPlayerLog) << "sound list is empty";
    }
    else
    {
        qCDebug(QueueSoundPlayerLog) << "other condition";
    }
}


#endif
