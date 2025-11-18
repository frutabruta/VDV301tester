#include "queuesoundplayer.h"


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
    qDebug() <<  Q_FUNC_INFO;
    QFileInfo check_file(path); //zdroj:: https://stackoverflow.com/questions/10273816/how-to-check-whether-file-exists-in-qt-in-c
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        qDebug()<<"soubor "<<path<<" existuje";
        return true;
    } else {
        qDebug()<<"soubor "<<path<<" neexistuje";
        return false;
    }
}


bool QueueSoundPlayer::fileExists(QUrl path)
{
    qDebug() <<  Q_FUNC_INFO;

    QString compoundPath=path.toLocalFile() ;
    QFileInfo check_file(compoundPath); //zdroj:: https://stackoverflow.com/questions/10273816/how-to-check-whether-file-exists-in-qt-in-c
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        qDebug()<<"soubor "<<compoundPath<<" existuje";
        return true;
    } else {
        qDebug()<<"soubor "<<compoundPath<<" neexistuje";
        return false;
    }
}


void QueueSoundPlayer::pridejDoFrontyVyhlas(QVector<QUrl> vstup)
{
    qDebug() <<  Q_FUNC_INFO;



    if (frontaZvuku.isEmpty())
    {
        qDebug()<<"fronta zvuku byla prazdna";
        frontaZvuku.append(vstup);
        internalPlayOneSoundFromList(frontaZvuku);
    }
    else

    {
        qDebug()<<"fronta zvuku nebyla prazdna";
        frontaZvuku.append(vstup);
    }
}





#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
//Qt5
void QueueSoundPlayer::vyhodPolozkuZeSeznamu(QVector<QUrl> &zasobnikAdres)
{
    qDebug() <<  Q_FUNC_INFO;
    if(!zasobnikAdres.isEmpty()&&(player.state()==QMediaPlayer::StoppedState) )
    {
        qDebug()<<"pocet polozek "<<zasobnikAdres.size();
        zasobnikAdres.removeFirst();
        internalPlayOneSoundFromList(zasobnikAdres);

    }
}

void QueueSoundPlayer::playOneSoundImmediately(QUrl soubor2)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<soubor2.toString();
    player.setMedia(soubor2);

    player.play();
}

void QueueSoundPlayer::internalPlayOneSoundFromList(QVector<QUrl> soundList)
{
    qDebug() <<  Q_FUNC_INFO;
    if(!soundList.isEmpty())
    {
        playOneSoundImmediately(soundList.first());
    }
}

void QueueSoundPlayer::zmenaStavuHlaseni(QMediaPlayer::State state)
{
    qDebug() <<  Q_FUNC_INFO <<state;
    vyhodPolozkuZeSeznamu(frontaZvuku);

}



#else
//Qt6
void QueueSoundPlayer::slotPlayStateChangedQt6(QMediaPlayer::PlaybackState state)
{
    qDebug() <<  Q_FUNC_INFO <<state;
    popSoundFromListQt6(frontaZvuku);
}


void QueueSoundPlayer::playOneSoundImmediately(QUrl soubor2)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<soubor2.toString();

    if(fileExists(soubor2))
    {
        player.setSource(soubor2);
        player.play();
    }
    else
    {
        slotPlayStateChangedQt6(QMediaPlayer::StoppedState);
    }



}


void QueueSoundPlayer::internalPlayOneSoundFromList(QVector<QUrl> soundList)
{
    qDebug() <<  Q_FUNC_INFO;
    if(!soundList.isEmpty())
    {
        playOneSoundImmediately(soundList.first());
    }
}

void QueueSoundPlayer::popSoundFromListQt6(QVector<QUrl> &soundList)
{
    qDebug() <<  Q_FUNC_INFO;
    if(!soundList.isEmpty()&&(player.playbackState()==QMediaPlayer::StoppedState) )
    {
        qDebug()<<"pocet polozek "<<soundList.size();
        soundList.removeFirst();
        internalPlayOneSoundFromList(soundList);

    }
}






#endif
