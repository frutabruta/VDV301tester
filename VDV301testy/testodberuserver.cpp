#include "testodberuserver.h"

TestOdberuServer::TestOdberuServer()
{
    inicializujPolozky();

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
    pridejPolozkuTestu("StartSluzby","","");
    pridejPolozkuTestu("Prihlaseni k odberu","","");
    pridejPolozkuTestu("Prihlaseni po odebrani","","");
    pridejPolozkuTestu("Prijem dat","","");
    pridejPolozkuTestu("Response","","");
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

void TestOdberuServer::aktualizaceSubscriberu(QVector<Subscriber> seznamSubscriberuInt)
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
            this->seznamPolozek[indexTestu].vysledek=vysledekFail;
        }
        else
        {
            this->seznamPolozek[indexTestu].prubeh=seznamSubscriberuInt.first().adresa.toString()+" "+seznamSubscriberuInt.first().struktura;
            this->seznamPolozek[indexTestu].vysledek=vysledekOK;
            qDebug()<<"seznamPolozek[indexTestu].vysledek="<<seznamPolozek[indexTestu].vysledek;
        }
        indexTestu++;
        emit vymazSeznamOdberatelu();
        //emit update(seznamPolozek);
        break;

    case 1:
        if (seznamSubscriberuInt.isEmpty())
        {
            this->seznamPolozek[indexTestu].vysledek=vysledekFail;
        }
        else
        {
            this->seznamPolozek[indexTestu].prubeh=seznamSubscriberuInt.first().adresa.toString()+" "+seznamSubscriberuInt.first().struktura;
            this->seznamPolozek[indexTestu].vysledek=vysledekOK;
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


int TestOdberuServer::prubehTestu()
{
    qDebug()<<"TestOdberuServer::prubehTestu()";
    emit nastartujSluzbu(true);
    return 0;
}
