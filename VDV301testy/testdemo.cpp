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
    qDebug()<<"TestDemo::start";
    testBezi=true;
    indexTestu=0;
    inicializujPolozky();
    //vymazStavy(seznamPolozek);
    emit update(seznamPolozek);
    prubehTestu();


}

void TestDemo::stop()
{
    qDebug()<<"TestDemo::stop";
    timer->stop();
    testBezi=false;
    seznamPolozek[indexTestu].prubehPrerusen();
    emit update(seznamPolozek);
}


void TestDemo::inicializujPolozky()
{
    qDebug()<<"TestDemo::inicializujPolozky";
    seznamPolozek.clear();
    pridejPolozkuTestu("Fáze 1","","",-1);
    pridejPolozkuTestu("Fáze 2","","",-1);
    pridejPolozkuTestu("Fáze 3","","",-1);
    pridejPolozkuTestu("Fáze 4","","",-1);
}


void TestDemo::prubehTestu()
{
    qDebug()<<"TestDemo::prubehTestu";
    seznamPolozek[indexTestu].prubehBezi();
    emit update(seznamPolozek);
timer->start(4000);
}




void TestDemo::slotCasovacVyprsel()
{

    qDebug()<<"TestDemo::slotCasovacVyprsel";
    if(indexTestu<seznamPolozek.length())
    {
        seznamPolozek[indexTestu].vysledekOk();
        seznamPolozek[indexTestu].prubehHotovo();
        indexTestu++;
        qDebug()<<"A";
        if (indexTestu<seznamPolozek.length())
        {
            qDebug()<<"B";
            seznamPolozek[indexTestu].prubehBezi();
        }
        else
        {
            qDebug()<<"C";
            emit testDokoncen(true);
        }

    }
    else
    {
        qDebug()<<"D";
        timer->stop();
    }



    emit update(seznamPolozek);
}


