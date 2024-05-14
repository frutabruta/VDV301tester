#include "queuesoundplayer.h"

QueueSoundPlayer::QueueSoundPlayer() {






#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    //qt5
    connect(player,&QMediaPlayer::stateChanged,this,&QueueSoundPlayer::zmenaStavuHlaseni);

#else
    //qt6
    connect(player,&QMediaPlayer::playbackStateChanged,this,&QueueSoundPlayer::zmenaStavuHlaseniQt6);
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);
#endif


}





void QueueSoundPlayer::pridejDoFrontyVyhlas(QVector<QUrl> vstup)
{
    qDebug() <<  Q_FUNC_INFO;
    if (frontaZvuku.isEmpty())
    {
        qDebug()<<"fronta zvuku byla prazdna";
        frontaZvuku.append(vstup);
        prehrajPolozkuZeSeznamu(frontaZvuku);
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
    if(!zasobnikAdres.isEmpty()&&(player->state()==QMediaPlayer::StoppedState) )
    {
        qDebug()<<"pocet polozek "<<zasobnikAdres.size();
        zasobnikAdres.removeFirst();
        prehrajPolozkuZeSeznamu(zasobnikAdres);

    }
}

void QueueSoundPlayer::prehrajJedenZvuk(QUrl soubor2)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<soubor2.toString();
    player->setMedia(soubor2);

    player->play();
}

void QueueSoundPlayer::prehrajPolozkuZeSeznamu(QVector<QUrl> zasobnikAdres)
{
    qDebug() <<  Q_FUNC_INFO;
    if(!zasobnikAdres.isEmpty())
    {
        prehrajJedenZvuk(zasobnikAdres.first());
    }
}

void QueueSoundPlayer::zmenaStavuHlaseni(QMediaPlayer::State state)
{
    qDebug() <<  Q_FUNC_INFO <<state;
    vyhodPolozkuZeSeznamu(frontaZvuku);

}



#else
//Qt6
void QueueSoundPlayer::zmenaStavuHlaseniQt6(QMediaPlayer::PlaybackState state)
{
    qDebug() <<  Q_FUNC_INFO <<state;
    vyhodPolozkuZeSeznamuQt6(frontaZvuku);
}


void QueueSoundPlayer::prehrajJedenZvuk(QUrl soubor2)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<soubor2.toString();

    player->setSource(soubor2);

    player->play();
}


void QueueSoundPlayer::prehrajPolozkuZeSeznamu(QVector<QUrl> zasobnikAdres)
{
    qDebug() <<  Q_FUNC_INFO;
    if(!zasobnikAdres.isEmpty())
    {
        prehrajJedenZvuk(zasobnikAdres.first());
    }
}

void QueueSoundPlayer::vyhodPolozkuZeSeznamuQt6(QVector<QUrl> &zasobnikAdres)
{
    qDebug() <<  Q_FUNC_INFO;
    if(!zasobnikAdres.isEmpty()&&(player->playbackState()==QMediaPlayer::StoppedState) )
    {
        qDebug()<<"pocet polozek "<<zasobnikAdres.size();
        zasobnikAdres.removeFirst();
        prehrajPolozkuZeSeznamu(zasobnikAdres);

    }
}






#endif
