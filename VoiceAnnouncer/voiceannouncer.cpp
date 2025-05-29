#include "voiceannouncer.h"
#include <QBuffer>


VoiceAnnouncer::VoiceAnnouncer()
{

    this->aktualizujCestyZvuku(announcmentSoundFolderPath);

}




QUrl VoiceAnnouncer::getFilePathFromStopIds(int kodOis, int kodCis)
{
    qDebug() <<  Q_FUNC_INFO;
    QString folder=announcmentSoundFolderPath+"/zastavky/";
    QString testOis="";
    QString testCis="";

    testOis+=folder;
    testOis+=QString::number(kodOis);
    testOis+=".mp3";

    testCis+=folder;
    testCis+=QString::number(kodCis);
    testCis+=".mp3";

    if(fileExists(testCis))
    {
        qDebug()<<"soubor s cis existuje,cislo:"<<QString::number(kodCis);
        return QUrl::fromLocalFile(testCis);
    }
    else
    {

        if (fileExists(testOis))
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
    QString slozka=announcmentSoundFolderPath+"/special/";
    QString cestaSouboru="";

    cestaSouboru+=slozka;
    cestaSouboru+=nazevSouboru;

    if(fileExists(cestaSouboru))
    {

        qDebug()<<"soubor specHlaseniExistuje:"<<nazevSouboru;
        return QUrl::fromLocalFile(cestaSouboru);

    }

    return QUrl::fromLocalFile("");
}




bool VoiceAnnouncer::announceThisAndNextStop(StopPoint stopPoint1, StopPoint stopPoint2)
{
    qDebug() <<  Q_FUNC_INFO;

    qDebug()<<"zvuk gong adresa "<<zvukGong;

    QVector<QUrl> subQueue;

    subQueue.push_back(zvukGong);
    subQueue.push_back(getFilePathFromStopIds(stopPoint1.idOis,stopPoint1.idCis));
    subQueue.append(stopAttributesToFileQurlList(stopPoint1));
    subQueue.push_back(zvukPristiZastavka);
    subQueue.push_back(getFilePathFromStopIds(stopPoint2.idOis,stopPoint2.idCis));

    if(stopPoint2.onRequest&&(!stopPoint2.neozn))
    {
        subQueue.push_back(zvukNaZnameni);
    }

    pridejDoFrontyVyhlas(subQueue);

    return 1;
}

bool VoiceAnnouncer::announceThisStop(StopPoint thisStop)
{
    qDebug() <<  Q_FUNC_INFO;

    qDebug()<<"zvuk gong adresa "<<zvukGong;

    QVector<QUrl> subQueue;

    subQueue.push_back(zvukGong);
    subQueue.push_back(getFilePathFromStopIds(thisStop.idOis,thisStop.idCis));
    subQueue.append(stopAttributesToFileQurlList(thisStop));

    pridejDoFrontyVyhlas(subQueue);

    return 1;
}


bool VoiceAnnouncer::announceNextStop(StopPoint nextStop)
{
    qDebug() <<  Q_FUNC_INFO;

    qDebug()<<"zvuk gong adresa "<<zvukGong;

    QVector<QUrl> subQueue;

    //kratkaFronta.push_back(zvukGong);
     subQueue.push_back(zvukGongPristi);
    subQueue.push_back(zvukPristiZastavka);
     subQueue.push_back(getFilePathFromStopIds(nextStop.idOis,nextStop.idCis));

    if(nextStop.onRequest&&(!nextStop.neozn))
    {
        subQueue.push_back(zvukNaZnameni);
    }

    pridejDoFrontyVyhlas(subQueue);

    return 1;
}

bool VoiceAnnouncer::composeFirstStopDeparture(StopPoint stopPoint2)
{
    qDebug() <<  Q_FUNC_INFO;

    qDebug()<<"zvuk gong adresa "<<zvukGong;

    QVector<QUrl> subQueue;

    subQueue.push_back(zvukPristiZastavka);
    subQueue.push_back(getFilePathFromStopIds(stopPoint2.idOis,stopPoint2.idCis));

    if(stopPoint2.onRequest&&(!stopPoint2.neozn))
    {
        subQueue.push_back(zvukNaZnameni);
    }

    pridejDoFrontyVyhlas(subQueue);

    return 1;
}

QVector<QUrl> VoiceAnnouncer::stopAttributesToFileQurlList(StopPoint stopPoint)
{
    QVector<QUrl> urlList;
    if(stopPoint.onRequest&&(!stopPoint.neozn))
    {
        urlList.push_back(zvukNaZnameni);
    }

    if(stopPoint.transferMetroA)
    {
        urlList.push_back(zvukPrestupNaMetro );

        if(stopPoint.transferMetroB)
        {
            urlList.push_back(zvukMAaB);
        }
        else if(stopPoint.transferMetroC)
        {
            urlList.push_back(zvukMAaC);
        }
        else if(stopPoint.transferMetroD)
        {
            urlList.push_back(zvukMAaD);
        }
        else
        {
            urlList.push_back(zvukMA);
        }
    }
    else if(stopPoint.transferMetroB)
    {
        urlList.push_back(zvukPrestupNaMetro );

        if(stopPoint.transferMetroC)
        {
            urlList.push_back(zvukMBaC);
        }
        else if(stopPoint.transferMetroD)
        {
            urlList.push_back(zvukMBaD);
        }
        else
        {
            urlList.push_back(zvukMB);
        }
    }
    else if(stopPoint.transferMetroC)
    {
        urlList.push_back(zvukPrestupNaMetro );
        if(stopPoint.transferMetroD)
        {
            urlList.push_back(zvukMCaD);
        }
        else
        {
            urlList.push_back(zvukMC);
        }
    }
    else if(stopPoint.transferMetroD)
    {
        urlList.push_back(zvukPrestupNaMetro );
        urlList.push_back(zvukMD);
    }


    if(stopPoint.transferTrain)
    {
        urlList.push_back(zvukPrestupNaLinkyS );
    }
    if(stopPoint.transferFerry)
    {
        urlList.push_back(zvukPrestupNaPrivoz );
    }

    if(stopPoint.transferAirplane)
    {
        urlList.push_back(zvukPrestupNaLetiste );
    }




    return urlList;

}





void VoiceAnnouncer::composeFareZoneChange()
{
    qDebug() <<  Q_FUNC_INFO;
    QVector<QUrl> subQueue;
    subQueue.push_back(zvukProsimPozor);
    subQueue.push_back(zvukZmenaPasma);

    pridejDoFrontyVyhlas(subQueue);



}


bool VoiceAnnouncer::composeSpecialAnnouncement(AdditionalAnnoucement additionalAnnouncement)
{
    qDebug() <<  Q_FUNC_INFO <<" segmentu:"<<QString::number(additionalAnnouncement.mp3.count());
    QVector<QUrl> qurlList;


    foreach(QString segment, additionalAnnouncement.mp3)
    {
        QUrl qurl= najdiCestuSpecial(segment);
        if(!qurl.isEmpty())
        {
            qurlList.push_back(qurl);
        }
    }

    if(qurlList.isEmpty())
    {
        qDebug()<<"file list is empty";
        return 0;
    }
    pridejDoFrontyVyhlas(qurlList);
    return 1;

}


bool VoiceAnnouncer::composeLastStopAnnouncement(StopPoint vstup)
{
    qDebug() <<  Q_FUNC_INFO;

    QVector<QUrl> subQueue;

    subQueue.push_back(zvukGong);
    subQueue.push_back(getFilePathFromStopIds(vstup.idOis, vstup.idCis));
    subQueue.append(stopAttributesToFileQurlList(vstup));
    subQueue.push_back(zvukKonecna);
    subQueue.push_back(zvukProsimeVystupte);

    pridejDoFrontyVyhlas(subQueue);
    // prehrajCelySeznamUrl(zasobnikAdres);


    return 1;
}



void VoiceAnnouncer::setPath(QString vstup)
{
    qDebug() <<  Q_FUNC_INFO;
    announcmentSoundFolderPath=vstup;
    aktualizujCestyZvuku(announcmentSoundFolderPath);
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
    zvukPrestupNaLetiste=QUrl::fromLocalFile(cestaVnitrni+"/special/H628.mp3");
    zvukMA=QUrl::fromLocalFile(cestaVnitrni+"/special/H104.mp3");
    zvukMB=QUrl::fromLocalFile(cestaVnitrni+"/special/H105.mp3");
    zvukMC=QUrl::fromLocalFile(cestaVnitrni+"/special/H106.mp3");
    zvukMD=QUrl::fromLocalFile(cestaVnitrni+"/special/H010.mp3"); //MP3 zatím neexistuje!


    zvukMAaB=QUrl::fromLocalFile(cestaVnitrni+"/special/H107.mp3");
    zvukMAaC=QUrl::fromLocalFile(cestaVnitrni+"/special/H108.mp3");
    zvukMAaD=QUrl::fromLocalFile(cestaVnitrni+"/special/H011.mp3");
    zvukMBaC=QUrl::fromLocalFile(cestaVnitrni+"/special/H109.mp3");
    zvukMBaD=QUrl::fromLocalFile(cestaVnitrni+"/special/H012.mp3");
    zvukMCaD=QUrl::fromLocalFile(cestaVnitrni+"/special/H013.mp3");


    //H178 prosím pozor
    //H170 změna tarifního pásma
    //H143 nástup postiženého
    // 144 linka
    //145 směr



}


void VoiceAnnouncer::setApplicationDirectory(QString umisteni)
{
    qDebug() <<  Q_FUNC_INFO;
    applicationDirectory=umisteni;
    announcmentSoundFolderPath=applicationDirectory+"/hlaseni";
    aktualizujCestyZvuku(announcmentSoundFolderPath);
}




