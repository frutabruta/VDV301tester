#include "testdemo.h"
#include "vdv301testy.h"
#include <QDebug>

TestDemo::TestDemo()
{
    connect(timer, &QTimer::timeout, this, &TestDemo::slotCasovacVyprsel);

    inicializujPolozky();

}


void TestDemo::start()
{
    qDebug()<<"Vdv301testy::start";
    testBezi=true;
    indexTestu=0;
    inicializujPolozky();
    //vymazStavy(seznamPolozek);
    emit update(seznamPolozek);
    prubehTestu();


}

void TestDemo::stop()
{
    qDebug()<<"Vdv301testy::stop";
    timer->stop();
    testBezi=false;
}


void TestDemo::inicializujPolozky()
{
    seznamPolozek.clear();
    pridejPolozkuTestu("zacatek","probiha","");
    pridejPolozkuTestu("stred","","");
    pridejPolozkuTestu("stred2","","");
    pridejPolozkuTestu("konec","","");
}


void TestDemo::prubehTestu()
{
    qDebug()<<"Vdv301testy::prubehTestu()";
timer->start(4000);
}




void TestDemo::slotCasovacVyprsel()
{
    qDebug()<<"Vdv301testy::slotCasovacVyprsel";
    if(indexTestu<seznamPolozek.length())
    {
        seznamPolozek[indexTestu].vysledek=vysledekOK;
        indexTestu++;
    }
    else
    {
        timer->stop();
    }



    emit update(seznamPolozek);
}


