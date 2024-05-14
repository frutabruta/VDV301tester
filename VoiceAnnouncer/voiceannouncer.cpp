#include "voiceannouncer.h"
#include <QBuffer>


VoiceAnnouncer::VoiceAnnouncer()
{

    this->aktualizujCestyZvuku(cesta);

}

bool VoiceAnnouncer::souborExistuje(QString path)
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


QUrl VoiceAnnouncer::najdiCestuZastavka(int kodOis, int kodCis)
{
    qDebug() <<  Q_FUNC_INFO;
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
        else
        {
            qDebug()<<"file doesnt exist: CIS "<<kodCis<<" OIS "<<kodOis;
        }

    }
    return QUrl::fromLocalFile("");
}


QUrl VoiceAnnouncer::najdiCestuSpecial(QString nazevSouboru)
{
    qDebug() <<  Q_FUNC_INFO;
    QString slozka=cesta+"/special/";
    QString cestaSouboru="";

    cestaSouboru+=slozka;
    cestaSouboru+=nazevSouboru;

    if(souborExistuje(cestaSouboru))
    {

        qDebug()<<"soubor specHlaseniExistuje:"<<nazevSouboru;
        return QUrl::fromLocalFile(cestaSouboru);

    }

    return QUrl::fromLocalFile("");
}




bool VoiceAnnouncer::announceThisAndNextStop(StopPoint zastavka1, StopPoint zastavka2)
{
    qDebug() <<  Q_FUNC_INFO;

    qDebug()<<"zvuk gong adresa "<<zvukGong;

    QVector<QUrl> kratkaFronta;

    kratkaFronta.push_back(zvukGong);
    kratkaFronta.push_back(najdiCestuZastavka(zastavka1.idOis,zastavka1.idCis));
    kratkaFronta.append(priznakyDoSeznamu(zastavka1));
    kratkaFronta.push_back(zvukPristiZastavka);
    kratkaFronta.push_back(najdiCestuZastavka(zastavka2.idOis,zastavka2.idCis));

    if(zastavka2.onRequest)
    {
        kratkaFronta.push_back(zvukNaZnameni);
    }

    pridejDoFrontyVyhlas(kratkaFronta);

    return 1;
}

bool VoiceAnnouncer::announceThisStop(StopPoint thisStop)
{
    qDebug() <<  Q_FUNC_INFO;

    qDebug()<<"zvuk gong adresa "<<zvukGong;

    QVector<QUrl> kratkaFronta;

    kratkaFronta.push_back(zvukGong);
    kratkaFronta.push_back(najdiCestuZastavka(thisStop.idOis,thisStop.idCis));
    kratkaFronta.append(priznakyDoSeznamu(thisStop));

    pridejDoFrontyVyhlas(kratkaFronta);

    return 1;
}


bool VoiceAnnouncer::announceNextStop(StopPoint nextStop)
{
    qDebug() <<  Q_FUNC_INFO;

    qDebug()<<"zvuk gong adresa "<<zvukGong;

    QVector<QUrl> kratkaFronta;

    //kratkaFronta.push_back(zvukGong);
     kratkaFronta.push_back(zvukGongPristi);
    kratkaFronta.push_back(zvukPristiZastavka);
    kratkaFronta.push_back(najdiCestuZastavka(nextStop.idOis,nextStop.idCis));

    if(nextStop.onRequest)
    {
        kratkaFronta.push_back(zvukNaZnameni);
    }

    pridejDoFrontyVyhlas(kratkaFronta);

    return 1;
}

bool VoiceAnnouncer::kompletOdjezdPrvniZastavka(StopPoint zastavka2)
{
    qDebug() <<  Q_FUNC_INFO;

    qDebug()<<"zvuk gong adresa "<<zvukGong;

    QVector<QUrl> kratkaFronta;

    kratkaFronta.push_back(zvukPristiZastavka);
    kratkaFronta.push_back(najdiCestuZastavka(zastavka2.idOis,zastavka2.idCis));

    if(zastavka2.onRequest)
    {
        kratkaFronta.push_back(zvukNaZnameni);
    }

    pridejDoFrontyVyhlas(kratkaFronta);

    return 1;
}

QVector<QUrl> VoiceAnnouncer::priznakyDoSeznamu(StopPoint vstup)
{
    QVector<QUrl> vystup;
    if(vstup.onRequest)
    {
        vystup.push_back(zvukNaZnameni);
    }

    if(vstup.transferMetroA)
    {
        vystup.push_back(zvukPrestupNaMetro );

        if(vstup.transferMetroB)
        {
            vystup.push_back(zvukMAaB);
        }
        else if(vstup.transferMetroC)
        {
            vystup.push_back(zvukMAaC);
        }
        else if(vstup.transferMetroD)
        {
            vystup.push_back(zvukMAaD);
        }
        else
        {
            vystup.push_back(zvukMA);
        }
    }
    else if(vstup.transferMetroB)
    {
        vystup.push_back(zvukPrestupNaMetro );

        if(vstup.transferMetroC)
        {
            vystup.push_back(zvukMBaC);
        }
        else if(vstup.transferMetroD)
        {
            vystup.push_back(zvukMBaD);
        }
        else
        {
            vystup.push_back(zvukMB);
        }
    }
    else if(vstup.transferMetroC)
    {
        vystup.push_back(zvukPrestupNaMetro );
        if(vstup.transferMetroD)
        {
            vystup.push_back(zvukMCaD);
        }
        else
        {
            vystup.push_back(zvukMC);
        }
    }
    else if(vstup.transferMetroD)
    {
        vystup.push_back(zvukPrestupNaMetro );
        vystup.push_back(zvukMD);
    }


    if(vstup.transferTrain)
    {
        vystup.push_back(zvukPrestupNaLinkyS );
    }
    if(vstup.transferFerry)
    {
        vystup.push_back(zvukPrestupNaPrivoz );
    }




    return vystup;

}





void VoiceAnnouncer::kompletZmenaTarifnihoPasma()
{
    qDebug() <<  Q_FUNC_INFO;
    QVector<QUrl> kratkaFronta;
    kratkaFronta.push_back(zvukProsimPozor);
    kratkaFronta.push_back(zvukZmenaPasma);

    pridejDoFrontyVyhlas(kratkaFronta);



}


bool VoiceAnnouncer::kompletSpecialniHlaseni(AdditionalAnnoucement specialniHlaseni)
{
    qDebug() <<  Q_FUNC_INFO <<" segmentu:"<<QString::number(specialniHlaseni.mp3.count());
    QVector<QUrl> seznamAdres;


    foreach(QString segment, specialniHlaseni.mp3)
    {
        QUrl adresa= najdiCestuSpecial(segment);
        if(!adresa.isEmpty())
        {
            seznamAdres.push_back(adresa);
        }
    }

    if(seznamAdres.isEmpty())
    {
        return 0;
    }
    pridejDoFrontyVyhlas(seznamAdres);
    return 1;

}


bool VoiceAnnouncer::kompletKonecna(StopPoint vstup)
{
    qDebug() <<  Q_FUNC_INFO;

    QVector<QUrl> zasobnikAdres;

    zasobnikAdres.push_back(zvukGong);
    zasobnikAdres.push_back(najdiCestuZastavka(vstup.idOis, vstup.idCis));
    zasobnikAdres.append(priznakyDoSeznamu(vstup));
    zasobnikAdres.push_back(zvukKonecna);
    zasobnikAdres.push_back(zvukProsimeVystupte);

    pridejDoFrontyVyhlas(zasobnikAdres);
    // prehrajCelySeznamUrl(zasobnikAdres);


    return 1;
}



void VoiceAnnouncer::nastavCestu(QString vstup)
{
    qDebug() <<  Q_FUNC_INFO;
    cesta=vstup;
    aktualizujCestyZvuku(cesta);
}
void VoiceAnnouncer::aktualizujCestyZvuku(QString cestaVnitrni)
{
    qDebug() <<  Q_FUNC_INFO;
    zvukPristiZastavka=QUrl::fromLocalFile(cestaVnitrni+"/special/H001.mp3");
    zvukGong=QUrl::fromLocalFile(cestaVnitrni+"/special/H000.mp3");
    zvukGongPristi=QUrl::fromLocalFile(cestaVnitrni+"/special/H242.mp3");
    zvukKonecna= QUrl::fromLocalFile(cestaVnitrni+"/special/H113.mp3");
    zvukProsimeVystupte= QUrl::fromLocalFile(cestaVnitrni+"/special/H114.mp3");
    zvukZmenaPasma= QUrl::fromLocalFile(cestaVnitrni+"/special/H170.mp3");
    zvukProsimPozor= QUrl::fromLocalFile(cestaVnitrni+"/special/H178.mp3");

    zvukNaZnameni= QUrl::fromLocalFile(cestaVnitrni+"/special/H002.mp3");
    zvukPrestupNaLinkyS=QUrl::fromLocalFile(cestaVnitrni+"/special/H184.mp3");
    zvukPrestupNaMetro=QUrl::fromLocalFile(cestaVnitrni+"/special/H103.mp3");
    zvukPrestupNaPrivoz=QUrl::fromLocalFile(cestaVnitrni+"/special/H274.mp3");
    zvukMA=QUrl::fromLocalFile(cestaVnitrni+"/special/H104.mp3");
    zvukMB=QUrl::fromLocalFile(cestaVnitrni+"/special/H105.mp3");
    zvukMC=QUrl::fromLocalFile(cestaVnitrni+"/special/H106.mp3");
    zvukMD=QUrl::fromLocalFile(cestaVnitrni+"/special/HXXX.mp3"); //MP3 zatím neexistuje!


    zvukMAaB=QUrl::fromLocalFile(cestaVnitrni+"/special/H107.mp3");
    zvukMAaC=QUrl::fromLocalFile(cestaVnitrni+"/special/H108.mp3");
    zvukMAaD=QUrl::fromLocalFile(cestaVnitrni+"/special/HXXX.mp3");
    zvukMBaC=QUrl::fromLocalFile(cestaVnitrni+"/special/H109.mp3");
    zvukMBaD=QUrl::fromLocalFile(cestaVnitrni+"/special/HXXX.mp3");
    zvukMCaD=QUrl::fromLocalFile(cestaVnitrni+"/special/HXXX.mp3");


    //H178 prosím pozor
    //H170 změna tarifního pásma
    //H143 nástup postiženého
    // 144 linka
    //145 směr



}


void VoiceAnnouncer::zmenUmisteniProgramu(QString umisteni)
{
    qDebug() <<  Q_FUNC_INFO;
    cestaProgramu=umisteni;
    cesta=cestaProgramu+"/hlaseni";
    aktualizujCestyZvuku(cesta);
}




