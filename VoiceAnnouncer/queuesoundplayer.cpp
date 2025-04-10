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


bool QueueSoundPlayer::souborExistuje(QString path)
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


bool QueueSoundPlayer::souborExistuje(QUrl path)
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

    if(souborExistuje(soubor2))
    {
        player->setSource(soubor2);
        player->play();
    }
    else
    {
        zmenaStavuHlaseniQt6(QMediaPlayer::StoppedState);
    }



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
