#include "testodberuserver.h"

TestOdberuServer::TestOdberuServer()
{
    qDebug()<<"TestOdberuServer::TestOdberuServer";
    inicializujPolozky();
    connect(this,&TestOdberuServer::signalDalsiKrok,this,&TestOdberuServer::slotKrok);

}

void TestOdberuServer::start()
{
    qDebug()<<"TestOdberuServer::start";
    testBezi=true;
    indexFaze=0;
    inicializujPolozky();
    //vymazStavy(seznamPolozek);
    emit update(seznamPolozek);
    prubehTestu();
}


/*
void TestOdberuServer::stop()
{
    qDebug()<<"TestOdberuServer::stop";
    // timer->stop();
    testBezi=false;
}*/

void TestOdberuServer::inicializujPolozky()
{
    qDebug()<<"TestOdberuServer::inicializujPolozky";
    seznamPolozek.clear();
    pridejPolozkuTestu("První odběr po spuštění","","",200000);
    pridejPolozkuTestu("Přihlášení po restartu služby","","",30000);
    pridejPolozkuTestu("Odezva na odeslaná data","","",20000);
    pridejPolozkuTestu("Odběr znova po 120s bez dat","","",200000);
    pridejPolozkuTestu("Response","","",-1);
}





void TestOdberuServer::slotVysledekOdberu(bool vysledek,QString poznamka)
{/*
    this->seznamPolozek[indexTestu].prubeh="hotovo";
    if(vysledek)
    {
     this->seznamPolozek[indexTestu].vysledek=vysledekOK;
    }
    else
    {
        this->seznamPolozek[indexTestu].vysledek=vysledekOK;
    }

    indexTestu++;
    emit update(seznamPolozek);*/

}

void TestOdberuServer::slotAktualizaceSubscriberu(QVector<Subscriber> seznamSubscriberuInt)
{
    qDebug()<<"TestOdberuServer::slotAktualizaceSubscriberu";
    if (testBezi==false)
    {
        return;
    }


    switch(indexFaze)
    {
    case 0:
        qDebug()<<"case 1";
        if (seznamSubscriberuInt.isEmpty())
        {
            this->seznamPolozek[indexFaze].vysledekChyba("seznam subscriberu je prazdny");
        }
        else
        {
            this->seznamPolozek[indexFaze].prubeh=seznamSubscriberuInt.first().adresa.toString()+" "+seznamSubscriberuInt.first().struktura;
            this->seznamPolozek[indexFaze].vysledekOk();
            qDebug()<<"seznamPolozek[indexTestu].vysledek="<<seznamPolozek[indexFaze].vysledek;

        }
        indexFaze++;
        indexFaze++;
        emit signalDalsiKrok();
        //emit update(seznamPolozek);
        break;

    case 3:
        qDebug()<<"case 3";
        if (seznamSubscriberuInt.isEmpty())
        {
            this->seznamPolozek[indexFaze].vysledekChyba("seznam subscriberu je prazdny");
            this->stop();
        }
        else
        {
            this->seznamPolozek[indexFaze].prubeh=seznamSubscriberuInt.first().adresa.toString()+" "+seznamSubscriberuInt.first().struktura;
            this->seznamPolozek[indexFaze].vysledekOk();
            qDebug()<<"seznamPolozek[indexTestu].vysledek="<<seznamPolozek[indexFaze].vysledek;
        }
        indexFaze++;
        emit update(seznamPolozek);
        emit signalDalsiKrok();
        break;

    default:
        qDebug()<<"default case";
        return;

        break;


    }




}





int TestOdberuServer::prubehTestu()
{
    qDebug()<<"TestOdberuServer::prubehTestu";
    slotKrok();
    return 0;
}


void TestOdberuServer::slotKrok()
{
    qDebug()<<"TestOdberuServer::slotKrok";
    switch(indexFaze)
    {
    case 0:
        startFaze0();
        break;
    case 1:
        startFaze1();
        break;
    case 2:
        startFaze2();
        break;
    case 3:
        startFaze2();
        break;
    default:
        break;


    }
}

void TestOdberuServer::startFaze0()
{
    qDebug()<<"             TestOdberuServer::startFaze0";
    seznamPolozek[indexFaze].prubehBezi();

    emitujUpdate();
    emit signalNastartujSluzbu(true);

    timerTimeoutFaze->setInterval(seznamPolozek.first().timeout);
    timerTimeoutFaze->start();


}
void TestOdberuServer::startFaze1()
{
    qDebug()<<"              TestOdberuServer::startFaze1";
    seznamPolozek[indexFaze].prubehBezi();
    emitujUpdate();
    timerTimeoutFaze->setInterval(seznamPolozek.at(indexFaze).timeout);
    timerTimeoutFaze->start();
    emit signalVymazSeznamOdberatelu();
}
void TestOdberuServer::startFaze2()
{
    qDebug()<<"              TestOdberuServer::startFaze2";
    seznamPolozek[indexFaze].prubehBezi();
    emitujUpdate();
    timerTimeoutFaze->setInterval(seznamPolozek.at(indexFaze).timeout);
    timerTimeoutFaze->start();
    emit signalZastavCisTimer();
    emit signalOdesliDataDoPanelu();
}

void TestOdberuServer::startFaze3()
{
    qDebug()<<"              TestOdberuServer::startFaze3";
    seznamPolozek[indexFaze].prubehBezi();
    emitujUpdate();
    timerTimeoutFaze->setInterval(seznamPolozek.at(indexFaze).timeout);
    timerTimeoutFaze->start();
    emit signalZastavCisTimer();
    //emit signalOdesliDataDoPanelu();
}

void TestOdberuServer::slotVypisOdpovedServeru(QNetworkReply* odpoved)
{

    //zdroj https://stackoverflow.com/questions/46348245/send-post-request-with-qt-and-read-json-response
    qDebug()<<"slotVypisOdpovedServeru";

    if(indexFaze!=2)
    {
        return;
    }

    QByteArray buffer = odpoved->readAll();
    qDebug() << "buffer "<< buffer;
    qDebug()<<"chyba "<<odpoved->errorString();
    qDebug()<<"rawheaderlist "<<odpoved->rawHeaderList();

    QVariant statusCode = odpoved->attribute( QNetworkRequest::HttpStatusCodeAttribute ); //https://forum.qt.io/topic/8428/getting-the-http-standard-response-code-from-a-qnetworkreply/4

    qDebug()<<statusCode;


    if (statusCode.toInt()!=200)
    {
        qDebug()<<"HTTP odpoved neni spravna "<<statusCode.toInt();
        seznamPolozek[indexFaze].vysledekChyba(statusCode.toString());
        testBezi=false;
    }
    else
    {
        qDebug()<<"HTTP response je ok";
        seznamPolozek[indexFaze].vysledekOk();
    }
    seznamPolozek[indexFaze].prubehHotovo();
    indexFaze++;
    emitujUpdate();
    emit signalDalsiKrok();
    /*QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
    QJsonObject jsonReply = jsonDoc.object();

    QJsonObject response = jsonReply["response"].toObject();
    QJsonArray  data     = jsonReply["data"].toArray();
    qDebug() << data;*/
}
