#include "hlasic.h"


Hlasic::Hlasic()
{

}


void Hlasic::gong()
{
    qDebug()<<"Hlasic::gong()";
    QMediaPlayer * player = new QMediaPlayer;
    //player->setMedia(QUrl::fromLocalFile("mp3/gong.mp3"));
    //player->setMedia(QUrl::fromLocalFile("C:/Users/Adam/Desktop/tmx_zaloha/aktualni_data/HLASENI/zastavky/1141.mp3"));
    player->setMedia(QUrl::fromLocalFile(cesta+"1141.mp3"));
    player->play();
    player->playlist();
}


int Hlasic::vyhlasZastavku(int kodOis, int kodCis)
{
    qDebug()<<"Hlasic::vyhlasZastavku";
    //QString slozka="C:/Users/Adam/Desktop/tmx_zaloha/aktualni_data/HLASENI/zastavky/";
    QString slozka="D:/zastavky/";
    slozka=cesta;
    QString testOis="";
    QString testCis="";

    testOis+=slozka;
    testOis+=QString::number(kodOis);
    testOis+=".mp3";

    testCis+=slozka;
    testCis+=QString::number(kodOis);
    testCis+=".mp3";

    if(souborExistuje(testCis))
    {

        qDebug()<<"soubor s cis existuje,cislo:"<<QString::number(kodCis);
        QMediaPlayer * player = new QMediaPlayer;
        player->setMedia(QUrl::fromLocalFile(testCis));
        //player->
        player->play();

    }
    else
    {
        if(souborExistuje(testOis))
        {
            qDebug()<<"soubor  cis "<<QString::number(kodCis)<<" nexistuje, pouzivam cislo OIS:"<<QString::number(kodOis);
            QMediaPlayer * player = new QMediaPlayer;
            player->setMedia(QUrl::fromLocalFile(testOis));
            //player->
            player->play();
        }
        {
            qDebug()<<"soubor ois "<<QString::number(kodCis)<<" nexistuje";
        }

    }




    return 1;
}


int Hlasic::vyhlasZastavku2(int kodOis, int kodCis)
{
    qDebug()<<"Hlasic::vyhlasZastavku2";
    //QString slozka="C:/Users/Adam/Desktop/tmx_zaloha/aktualni_data/HLASENI/zastavky/";
    QString slozka=cesta+"/zastavky/";

    QString testOis="";
    QString testCis="";

    testOis+=slozka;
    testOis+=QString::number(kodOis);
    testOis+=".mp3";

    testCis+=slozka;
    testCis+=QString::number(kodOis);
    testCis+=".mp3";

    if(souborExistuje(testCis))
    {

        qDebug()<<"soubor s cis existuje,cislo:"<<QString::number(kodCis);
        QMediaPlayer * player = new QMediaPlayer;
        player->setMedia(QUrl::fromLocalFile(testCis));
        //player->
        player->play();

        // ------------------------------------------------


        playlist->addMedia(QUrl::fromLocalFile(testCis));
        playlist->addMedia(QUrl::fromLocalFile(testCis));
        playlist->addMedia(QUrl::fromLocalFile(testCis));

        playlist->setCurrentIndex(1);

        player = new QMediaPlayer;
        player->setPlaylist(playlist);

        /*  videoWidget = new QVideoWidget;
        player->setVideoOutput(videoWidget);
        videoWidget->show(); */

        player->play();

    }
    else
    {
        if(souborExistuje(testOis))
        {


            qDebug()<<"soubor  cis "<<testCis<<" nexistuje, pouzivam cislo OIS:"<<QString::number(kodOis);
            QMediaPlayer * player = new QMediaPlayer;
            player->setMedia(QUrl::fromLocalFile(testOis));
            //player->
            player->play();}
        else
        {
            qDebug()<<"soubor  cis "<<testOis<<" nexistuje";
        }

    }
    return 1;
}




bool Hlasic::souborExistuje(QString path)
{
    qDebug()<<"Hlasic::souborExistuje";
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




QUrl Hlasic::dilciVyhlaseni(int kodOis, int kodCis)
{
    qDebug()<<"Hlasic::dilciVyhlaseni";
    // QString slozka="C:/Users/Adam/Desktop/tmx_zaloha/aktualni_data/HLASENI/zastavky/";
    QString slozka=cesta+"/zastavky/";
    QString testOis="";
    QString testCis="";

    testOis+=slozka;
    testOis+=QString::number(kodOis);
    testOis+=".mp3";

    testCis+=slozka;
    testCis+=QString::number(kodCis);
    testCis+=".mp3";

    if(souborExistuje(testCis))
    {

        qDebug()<<"soubor s cis existuje,cislo:"<<QString::number(kodCis);
        return QUrl::fromLocalFile(testCis);

    }
    else
    {
        if (souborExistuje(testOis))
        {
            qDebug()<<"soubor  cis "<<testCis<<" neexistuje, pouzivam cislo OIS:"<<testOis;
            return QUrl::fromLocalFile(testOis);
        }


    }
    return QUrl::fromLocalFile("");
}


bool Hlasic::kompletZastavka(int cis1,int ois1, int cis2, int ois2)
{
    playlist->clear();

    playlist->addMedia(QUrl::fromLocalFile(cesta+"/special/H000.mp3"));
    playlist->addMedia(dilciVyhlaseni(ois1,cis1));
    playlist->addMedia(QUrl::fromLocalFile(cesta+"/special/H001.mp3"));
    playlist->addMedia(dilciVyhlaseni(ois2,cis2));
    playlist->setCurrentIndex(1);



    QMediaPlayer * player = new QMediaPlayer;
    player->setPlaylist(playlist);
    player->play();
    return 1;
}

bool Hlasic::kompletKonecna(int cis1,int ois1)
{
    playlist->clear();

    playlist->addMedia(QUrl::fromLocalFile(cesta+"/special/H000.mp3"));
    playlist->addMedia(dilciVyhlaseni(ois1,cis1));
    playlist->addMedia(QUrl::fromLocalFile(cesta+"/special/H113.mp3"));
    playlist->addMedia(QUrl::fromLocalFile(cesta+"/special/H114.mp3"));

    playlist->setCurrentIndex(1);

    QMediaPlayer * player = new QMediaPlayer;
    player->setPlaylist(playlist);
    player->play();

    return 1;
}
