#include "voiceannouncer.h"
#include <QBuffer>

Q_LOGGING_CATEGORY(VoiceAnnouncerLog, "VoiceAnnouncer");


VoiceAnnouncer::VoiceAnnouncer()
{
    this->updateSoundFilesPaths(announcmentSoundFolderPath);
}


QUrl VoiceAnnouncer::getFilePathFromStopIds(int kodCis)
{
    qCDebug(VoiceAnnouncerLog) <<  Q_FUNC_INFO;
    QString folder=announcmentSoundFolderPath+"/zastavky/";
    QString testCis="";

    testCis+=folder;
    testCis+=QString::number(kodCis);
    testCis+=".mp3";

    if(fileExists(testCis))
    {
        qCDebug(VoiceAnnouncerLog)<<"files exists, CIS code: "<<QString::number(kodCis);
        return QUrl::fromLocalFile(testCis);
    }
    else
    {
        qCDebug(VoiceAnnouncerLog)<<"file doesnt exist: CIS "<<kodCis;
    }
    return QUrl();
}


QUrl VoiceAnnouncer::getFilePathNumber(QString fileName)
{
    qCDebug(VoiceAnnouncerLog) <<  Q_FUNC_INFO;
    QString directory=announcmentSoundFolderPath+"/cisla/";
    QString filePath="";

    filePath+=directory;
    filePath+=fileName;
    filePath+=".mp3";

    if(fileExists(filePath))
    {
        qCDebug(VoiceAnnouncerLog)<<"file special exists: "<<fileName;
        return QUrl::fromLocalFile(filePath);
    }

    return QUrl();
}

QUrl VoiceAnnouncer::getFilePathSpecial(QString fileName)
{
    qCDebug(VoiceAnnouncerLog) <<  Q_FUNC_INFO;
    QString directory=announcmentSoundFolderPath+"/special/";
    QString filePath="";

    filePath+=directory;
    filePath+=fileName;

    if(fileExists(filePath))
    {
        qCDebug(VoiceAnnouncerLog)<<"file special exists: "<<fileName;
        return QUrl::fromLocalFile(filePath);
    }

    return QUrl();
}


bool VoiceAnnouncer::announceBlindPersonBoarding()
{
    qCDebug(VoiceAnnouncerLog) <<  Q_FUNC_INFO;
    QVector<QUrl> subQueue;
    subQueue.push_back(zvukNastupNeboVystupNevidomeho);
    pridejDoFrontyVyhlas(subQueue);
    return 1;
}

bool VoiceAnnouncer::announceLineAndDestination(StopPointDestination thisStop)
{
    qCDebug(VoiceAnnouncerLog) <<  Q_FUNC_INFO;

    QVector<QUrl> subQueue;
    subQueue.push_back(zvukLinka);

    if(thisStop.line.lineName.isEmpty())
    {
       subQueue.append(lineNameCreate(thisStop.line.lineName));
    }
    else
    {
        subQueue.append(lineNameCreate(QString::number(thisStop.line.c)));
    }


    subQueue.push_back(zvukSmer);
    subQueue.push_back(getFilePathFromStopIds(thisStop.destination.idCis));
    //subQueue.append(stopAttributesToFileQurlList(thisStop));

    pridejDoFrontyVyhlas(subQueue);

    return 1;
}


bool VoiceAnnouncer::announceThisAndNextStop(StopPoint stopPoint1, StopPoint stopPoint2)
{
    qCDebug(VoiceAnnouncerLog) <<  Q_FUNC_INFO;
    qCDebug(VoiceAnnouncerLog)<<"zvuk gong adresa "<<zvukGong;

    QVector<QUrl> subQueue;

    subQueue.push_back(zvukGong);
    subQueue.push_back(getFilePathFromStopIds(stopPoint1.idCis));
    subQueue.append(stopAttributesToFileQurlList(stopPoint1));
    subQueue.push_back(zvukPristiZastavka);
    subQueue.push_back(getFilePathFromStopIds(stopPoint2.idCis));

    if(stopPoint2.onRequest&&(!stopPoint2.neozn))
    {
        subQueue.push_back(zvukNaZnameni);
    }

    pridejDoFrontyVyhlas(subQueue);

    return 1;
}

bool VoiceAnnouncer::announceThisStop(StopPoint thisStop)
{
    qCDebug(VoiceAnnouncerLog) <<  Q_FUNC_INFO;
    qCDebug(VoiceAnnouncerLog)<<"zvuk gong adresa "<<zvukGong;

    QVector<QUrl> subQueue;

    subQueue.push_back(zvukGong);
    subQueue.push_back(getFilePathFromStopIds(thisStop.idCis));
    subQueue.append(stopAttributesToFileQurlList(thisStop));

    pridejDoFrontyVyhlas(subQueue);

    return 1;
}



bool VoiceAnnouncer::announceNextStop(StopPoint nextStop)
{
    qCDebug(VoiceAnnouncerLog) <<  Q_FUNC_INFO;

    qCDebug(VoiceAnnouncerLog)<<"zvuk gong adresa "<<zvukGong;

    QVector<QUrl> subQueue;

    //kratkaFronta.push_back(zvukGong);
    subQueue.push_back(zvukGongPristi);
    subQueue.push_back(zvukPristiZastavka);
    subQueue.push_back(getFilePathFromStopIds(nextStop.idCis));

    if(nextStop.onRequest&&(!nextStop.neozn))
    {
        subQueue.push_back(zvukNaZnameni);
    }

    pridejDoFrontyVyhlas(subQueue);

    return 1;
}

bool VoiceAnnouncer::composeFirstStopDeparture(StopPoint stopPoint2)
{
    qCDebug(VoiceAnnouncerLog) <<  Q_FUNC_INFO;
    qCDebug(VoiceAnnouncerLog)<<"zvuk gong adresa "<<zvukGong;

    QVector<QUrl> subQueue;

    subQueue.push_back(zvukPristiZastavka);
    subQueue.push_back(getFilePathFromStopIds(stopPoint2.idCis));

    if(stopPoint2.onRequest&&(!stopPoint2.neozn))
    {
        subQueue.push_back(zvukNaZnameni);
    }

    pridejDoFrontyVyhlas(subQueue);

    return 1;
}

// mockup for now
QVector<QUrl> VoiceAnnouncer::lineNameCreate(QString lineName)
{
    qCDebug(VoiceAnnouncerLog) << Q_FUNC_INFO << " input: "<<lineName;
    QVector<QUrl> urlList;

    int lineNameNumber=lineName.toInt();

    if(lineNameNumber>0)
    {
        urlList.push_back(getFilePathNumber("C100"));
    }
    else
    {
        qCDebug(VoiceAnnouncerLog) << "not a number";
    }

    return urlList;
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
    qCDebug(VoiceAnnouncerLog) <<  Q_FUNC_INFO;
    QVector<QUrl> subQueue;
    subQueue.push_back(zvukProsimPozor);
    subQueue.push_back(zvukZmenaPasma);

    pridejDoFrontyVyhlas(subQueue);
}


bool VoiceAnnouncer::composeSpecialAnnouncement(AdditionalAnnoucement additionalAnnouncement)
{
    qCDebug(VoiceAnnouncerLog) <<  Q_FUNC_INFO <<" segmentu:"<<QString::number(additionalAnnouncement.mp3.count());
    QVector<QUrl> qurlList;


    foreach(QString segment, additionalAnnouncement.mp3)
    {
        QUrl qurl= getFilePathSpecial(segment);
        if(!qurl.isEmpty())
        {
            qurlList.push_back(qurl);
        }
    }

    if(qurlList.isEmpty())
    {
        qCDebug(VoiceAnnouncerLog)<<"file list is empty";
        return 0;
    }
    pridejDoFrontyVyhlas(qurlList);
    return 1;

}


bool VoiceAnnouncer::composeLastStopAnnouncement(StopPoint vstup)
{
    qCDebug(VoiceAnnouncerLog) <<  Q_FUNC_INFO;

    QVector<QUrl> subQueue;

    subQueue.push_back(zvukGong);
    subQueue.push_back(getFilePathFromStopIds( vstup.idCis));
    subQueue.append(stopAttributesToFileQurlList(vstup));
    subQueue.push_back(zvukKonecna);
    subQueue.push_back(zvukProsimeVystupte);

    pridejDoFrontyVyhlas(subQueue);
    // prehrajCelySeznamUrl(zasobnikAdres);


    return 1;
}



void VoiceAnnouncer::setPath(QString vstup)
{
    qCDebug(VoiceAnnouncerLog) <<  Q_FUNC_INFO;
    announcmentSoundFolderPath=vstup;
    updateSoundFilesPaths(announcmentSoundFolderPath);
}
void VoiceAnnouncer::updateSoundFilesPaths(QString cestaVnitrni)
{
    qCDebug(VoiceAnnouncerLog) <<  Q_FUNC_INFO;
    zvukPristiZastavka=QUrl::fromLocalFile(cestaVnitrni+"/special/H001.mp3");
    zvukGong=QUrl::fromLocalFile(cestaVnitrni+"/special/H000.mp3");
    zvukGongPristi=QUrl::fromLocalFile(cestaVnitrni+"/special/H242.mp3");
    zvukKonecna=QUrl::fromLocalFile(cestaVnitrni+"/special/H113.mp3");
    zvukProsimeVystupte=QUrl::fromLocalFile(cestaVnitrni+"/special/H114.mp3");
    zvukZmenaPasma=QUrl::fromLocalFile(cestaVnitrni+"/special/H170.mp3");
    zvukProsimPozor=QUrl::fromLocalFile(cestaVnitrni+"/special/H178.mp3");
    zvukNastupNeboVystupNevidomeho= QUrl::fromLocalFile(cestaVnitrni+"/special/H142.mp3");
    zvukLinka=QUrl::fromLocalFile(cestaVnitrni+"/special/H144.mp3");
    zvukSmer=QUrl::fromLocalFile(cestaVnitrni+"/special/H145.mp3");

    zvukNaZnameni=QUrl::fromLocalFile(cestaVnitrni+"/special/H002.mp3");
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

 
 
    //H143 nástup postiženého
  
}


void VoiceAnnouncer::setApplicationDirectory(QString umisteni)
{
    qCDebug(VoiceAnnouncerLog) <<  Q_FUNC_INFO;
    applicationDirectory=umisteni;
    announcmentSoundFolderPath=applicationDirectory+"/hlaseni";
    updateSoundFilesPaths(announcmentSoundFolderPath);
}




