#include "hlasic.h"
#include <QBuffer>

Hlasic::Hlasic()
{
    //  connect(&customerInformationService1_0,&HttpSluzba::vypisSubscriberu,this,&MainWindow::vypisSubscribery);
    // connect(m_player, &QMediaPlayer::stateChanged, this, &Player::stateChanged);
    connect(player,&QMediaPlayer::stateChanged,this,&Hlasic::zmenaStavuHlaseni);
   //connect(player,&QMediaPlayer::stateChanged,this,&Hlasic::prehrajPolozkuZeSeznamu);
    this->aktualizujCestyZvuku(cesta);


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
/*
QString Hlasic::dilciVyhlaseniString(int kodOis, int kodCis)
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
        return testCis;

    }
    else
    {
        if (souborExistuje(testOis))
        {
            qDebug()<<"soubor  cis "<<testCis<<" neexistuje, pouzivam cislo OIS:"<<testOis;
            return testOis;
        }


    }
    return "";
}
*/

bool Hlasic::kompletZastavka(int cis1,int ois1, int cis2, int ois2)
{
    qDebug()<<"Hlasic::kompletZastavka";



    // QMediaPlayer * player =  new QMediaPlayer(NULL, QMediaPlayer::StreamPlayback);




  //  QUrl zvukPristiZastavka=QUrl::fromLocalFile(cesta+"/special/H001.mp3");
  //  QUrl zvukGong=QUrl::fromLocalFile(cesta+"/special/H000.mp3");
/*
    QVector<QUrl> zasobnikAdres;
    zasobnikAdres.push_back(zvukGong);
    zasobnikAdres.push_back(dilciVyhlaseni(ois1,cis1));
    zasobnikAdres.push_back(zvukPristiZastavka);
    zasobnikAdres.push_back(dilciVyhlaseni(ois2,cis2));
    prehrajCelySeznamUrl(zasobnikAdres);
*/
    qDebug()<<"zvuk gong adresa "<<zvukGong;

   QVector<QUrl> kratkaFronta;

    kratkaFronta.push_back(zvukGong);
    kratkaFronta.push_back(dilciVyhlaseni(ois1,cis1));
   kratkaFronta.push_back(zvukPristiZastavka);
    kratkaFronta.push_back(dilciVyhlaseni(ois2,cis2));


    if (frontaZvuku.isEmpty())
    {
       frontaZvuku.append(kratkaFronta);
      prehrajPolozkuZeSeznamu(frontaZvuku);
    }
    else

    {
        frontaZvuku.append(kratkaFronta);
    }







    return 1;
}

bool Hlasic::kompletKonecna(int cis1,int ois1)
{
    qDebug()<<"Hlasic::kompletKonecna";

    QVector<QUrl> zasobnikAdres;

    zasobnikAdres.append(zvukGong);
    zasobnikAdres.append(dilciVyhlaseni(ois1,cis1));
    zasobnikAdres.append(zvukKonecna);
    zasobnikAdres.append(zvukProsimeVystupte);

    prehrajCelySeznamUrl(zasobnikAdres);


    /*
    playlist->clear();

    playlist->addMedia(QUrl::fromLocalFile(cesta+"/special/H000.mp3"));
    playlist->addMedia(dilciVyhlaseni(ois1,cis1));
    playlist->addMedia(QUrl::fromLocalFile(cesta+"/special/H113.mp3"));
    playlist->addMedia(QUrl::fromLocalFile(cesta+"/special/H114.mp3"));

    playlist->setCurrentIndex(1);

    QMediaPlayer * player = new QMediaPlayer;
    player->setPlaylist(playlist);
    player->play();
    */

    return 1;
}


QByteArray* Hlasic::pridejDoBufferu(QUrl cesta2, QByteArray *pole)
{
    qDebug()<<"Hlasic::pridejDoBufferu";
    QFile file(cesta2.toLocalFile());
    qDebug()<<"název MP3 souboru "<<cesta2;
    file.open(QIODevice::ReadOnly);
    pole->append(file.readAll());
    file.close();
    return pole;
}

void Hlasic::zmenaStavuHlaseni(QMediaPlayer::State state)
{
    qDebug()<<"stav hlaseni"<<state;
    vyhodPolozkuZeSeznamu(frontaZvuku);

}

void Hlasic::prehrajCelySeznamUrl(QVector<QUrl> zasobnikAdres)
{
    // https://stackoverflow.com/questions/48167960/what-is-the-fastest-way-to-start-playing-audio-in-qt-application

    qDebug()<<"Hlasic::prehrajCelySeznamUrl";
    QByteArray *ba = new QByteArray();
    for(int i=0;i<zasobnikAdres.count();i++)
    {
        ba=this->pridejDoBufferu(zasobnikAdres.at(i),ba);
    }


    QBuffer *buffer = new QBuffer(ba);
    buffer->open(QIODevice::ReadOnly);
    buffer->reset();  // same as buffer.seek(0);
    qDebug() << "Buffer size:" << buffer->size(); // is the file loaded
    player->setMedia(QMediaContent(), buffer);
    player->play();
}

void Hlasic::prehrajPolozkuZeSeznamu(QVector<QUrl> zasobnikAdres)
{
    qDebug()<<"Hlasic::prehrajPolozkuZeSeznamu";
    if(!zasobnikAdres.isEmpty())
    {
        prehrajJedenZvuk(zasobnikAdres.first());
    }
}



void Hlasic::vyhodPolozkuZeSeznamu(QVector<QUrl> &zasobnikAdres)
{
    qDebug()<<"Hlasic::vyhodPolozkuZeSeznamu";
    if(!zasobnikAdres.isEmpty()&&(player->state()==QMediaPlayer::StoppedState) )
    {
    qDebug()<<"pocet polozek "<<zasobnikAdres.size();
    zasobnikAdres.removeFirst();
    prehrajPolozkuZeSeznamu(zasobnikAdres);

    }
}
void Hlasic::prehrajJedenZvuk(QUrl soubor2)
{
    qDebug()<<"Hlasic::prehrajJedenZvuk";
    player->setMedia(soubor2);
    player->play();
}



void Hlasic::nastavCestu(QString vstup)
{
    qDebug()<<"Hlasic::nastavCestu";
    cesta=vstup;
    aktualizujCestyZvuku(cesta);
}
void Hlasic::aktualizujCestyZvuku(QString cestaVnitrni)
{
    qDebug()<<"Hlasic::aktualizujCestyZvuku";
    zvukPristiZastavka=QUrl::fromLocalFile(cestaVnitrni+"/special/H001.mp3");
    zvukGong=QUrl::fromLocalFile(cestaVnitrni+"/special/H000.mp3");
    zvukKonecna= QUrl::fromLocalFile(cestaVnitrni+"/special/H113.mp3");
    zvukProsimeVystupte= QUrl::fromLocalFile(cestaVnitrni+"/special/H114.mp3");
}


void Hlasic::zmenUmisteniProgramu(QString umisteni)
{
    qDebug()<<"Hlasic::zmenUmisteniProgramu";
    cestaProgramu=umisteni;
    cesta=cestaProgramu+"/hlaseni";
    aktualizujCestyZvuku(cesta);
}
