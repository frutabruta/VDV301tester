#include "testodberuserver.h"

TestOdberuServer::TestOdberuServer()
{
    inicializujPolozky();
    connect(timerTimeoutFaze, &QTimer::timeout, this, &TestOdberuServer::slotTimeoutFazeVyprsel);

}

void TestOdberuServer::start()
{
    qDebug()<<"TestOdberuServer::start";
    testBezi=true;
    indexTestu=0;
    inicializujPolozky();
    //vymazStavy(seznamPolozek);
    emit update(seznamPolozek);
    prubehTestu();


}
void TestOdberuServer::stop()
{
    qDebug()<<"TestOdberuServer::stop";
    // timer->stop();
    testBezi=false;
}

void TestOdberuServer::inicializujPolozky()
{
    seznamPolozek.clear();
    pridejPolozkuTestu("První odběr po spuštění","","",5000);
    pridejPolozkuTestu("Přihlášení po restartu služby","","",30000);
    pridejPolozkuTestu("Odezva na odeslaná data","","",-1);
    pridejPolozkuTestu("Odběr znova po 120s bez dat","","",-1);
    pridejPolozkuTestu("Response","","",-1);
}









void TestOdberuServer::vysledekOdberu(bool vysledek,QString poznamka)
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
    if (testBezi==false)
    {
        return;
    }


    switch(indexTestu)
    {
    case 0:
        if (seznamSubscriberuInt.isEmpty())
        {
            this->seznamPolozek[indexTestu].vysledekChyba("seznam subscriberu je prazdny");
        }
        else
        {
            this->seznamPolozek[indexTestu].prubeh=seznamSubscriberuInt.first().adresa.toString()+" "+seznamSubscriberuInt.first().struktura;
            this->seznamPolozek[indexTestu].vysledekOk();
            qDebug()<<"seznamPolozek[indexTestu].vysledek="<<seznamPolozek[indexTestu].vysledek;

        }
        indexTestu++;
        timerTimeoutFaze->setInterval(seznamPolozek.at(indexTestu).timeout);
        emit vymazSeznamOdberatelu();
        //emit update(seznamPolozek);
        break;

    case 1:
        if (seznamSubscriberuInt.isEmpty())
        {
            this->seznamPolozek[indexTestu].vysledekChyba("seznam subscriberu je prazdny");
        }
        else
        {
            this->seznamPolozek[indexTestu].prubeh=seznamSubscriberuInt.first().adresa.toString()+" "+seznamSubscriberuInt.first().struktura;
            this->seznamPolozek[indexTestu].vysledekOk();
            qDebug()<<"seznamPolozek[indexTestu].vysledek="<<seznamPolozek[indexTestu].vysledek;
        }
        indexTestu++;
        emit update(seznamPolozek);
        break;

    default:
        return;

        break;


    }




}

void TestOdberuServer::slotTimeoutFazeVyprsel()
{
    qDebug()<<"TestOdberuServer::timeoutFazeVyprsel()";
    seznamPolozek[indexTestu].prubehTimeout();
    seznamPolozek[indexTestu].vysledekChyba();
    emit update(seznamPolozek);

    this->stop();
}

void TestOdberuServer::slotOdpovedNaData(QString status)
{

}

int TestOdberuServer::prubehTestu()
{
    qDebug()<<"TestOdberuServer::prubehTestu()";
    emit nastartujSluzbu(true);
    if (!seznamPolozek.isEmpty())
    {
    timerTimeoutFaze->setInterval(seznamPolozek.first().timeout);
    timerTimeoutFaze->start();
    }
    return 0;
}
