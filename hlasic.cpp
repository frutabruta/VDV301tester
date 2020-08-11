#include "hlasic.h"


Hlasic::Hlasic()
{

}


void Hlasic::gong()
{
    QMediaPlayer * player = new QMediaPlayer;
    //player->setMedia(QUrl::fromLocalFile("mp3/gong.mp3"));
    player->setMedia(QUrl::fromLocalFile("C:/Users/Adam/Desktop/tmx_zaloha/aktualni_data/HLASENI/zastavky/1141.mp3"));
    //player->
    player->play();
    player->playlist();
}


int Hlasic::vyhlasZastavku(int kodOis, int kodCis)
{
    QString slozka="C:/Users/Adam/Desktop/tmx_zaloha/aktualni_data/HLASENI/zastavky/";
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
        qDebug()<<"soubor  cis "<<QString::number(kodCis)<<" nexistuje, pouzivam cislo OIS:"<<QString::number(kodOis);
        QMediaPlayer * player = new QMediaPlayer;
        player->setMedia(QUrl::fromLocalFile(testOis));
        //player->
        player->play();

    }




    return 1;
}


int Hlasic::vyhlasZastavku2(int kodOis, int kodCis)
{
    QString slozka="C:/Users/Adam/Desktop/tmx_zaloha/aktualni_data/HLASENI/zastavky/";
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
        qDebug()<<"soubor  cis "<<QString::number(kodCis)<<" nexistuje, pouzivam cislo OIS:"<<QString::number(kodOis);
        QMediaPlayer * player = new QMediaPlayer;

        /*

        player->setMedia(QUrl::fromLocalFile(testOis));
        player->play();
        */

    }




    return 1;
}




bool Hlasic::souborExistuje(QString path)
{

    QFileInfo check_file(path); //zdroj:: https://stackoverflow.com/questions/10273816/how-to-check-whether-file-exists-in-qt-in-c
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}
