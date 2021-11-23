#include "vdv301testy.h"
#include <QDebug>
Vdv301testy::Vdv301testy()
{
  //  connect(timer, &QTimer::timeout, this, &Vdv301testy::slotCasovacVyprsel);

   // inicializujPolozky();

}

/*
void Vdv301testy::start()
{
    qDebug()<<"Vdv301testy::start";
    testBezi=true;
    indexTestu=0;
    inicializujPolozky();
    //vymazStavy(seznamPolozek);
    emit update(seznamPolozek);
    prubehTestu();


}

void Vdv301testy::inicializujPolozky()
{
    seznamPolozek.clear();
    pridejPolozkuTestu("zacatek","probiha","");
    pridejPolozkuTestu("stred","","");
    pridejPolozkuTestu("stred2","","");
    pridejPolozkuTestu("konec","","");
}


void Vdv301testy::prubehTestu()
{
    qDebug()<<"Vdv301testy::prubehTestu()";
timer->start(4000);
}
void Vdv301testy::stop()
{
    qDebug()<<"Vdv301testy::stop";
    timer->stop();
    testBezi=false;
}
*/
void Vdv301testy::pridejPolozkuTestu(QString jmeno, QString prubeh, QString vysledek)
{
    qDebug()<<"Vdv301testy::pridejPolozkuTestu";
    PolozkaTestu novaPolozka;
    novaPolozka.nazev=jmeno;
    novaPolozka.prubeh=prubeh;
    novaPolozka.vysledek=vysledek;
    seznamPolozek.append(novaPolozka);

}
/*
void Vdv301testy::slotCasovacVyprsel()
{
    qDebug()<<"Vdv301testy::slotCasovacVyprsel";
    if(indexTestu<seznamPolozek.length())
    {
        seznamPolozek[indexTestu].vysledek="OK";
        indexTestu++;
    }
    else
    {
        timer->stop();
    }



    emit update(seznamPolozek);
}
*/
void Vdv301testy::vymazStavy(QVector<PolozkaTestu> &seznamPolozek2)
{
    qDebug()<<"Vdv301testy::vymazStavy";
    for(int i=0;i<seznamPolozek2.length();i++)
    {
        seznamPolozek2[i].prubeh="";
        seznamPolozek2[i].vysledek="";
        qDebug()<<"iteruju";
    }
}

void Vdv301testy::emitujUpdate()
{
    qDebug()<<"Vdv301testy::emitujUpdate";
    emit update(seznamPolozek);
}
