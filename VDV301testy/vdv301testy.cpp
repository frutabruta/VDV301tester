#include "vdv301testy.h"
#include <QDebug>
Vdv301testy::Vdv301testy()
{
    timerTimeoutFaze->setSingleShot(true);
  //  connect(timer, &QTimer::timeout, this, &Vdv301testy::slotCasovacVyprsel);

   // inicializujPolozky();
     connect(timerTimeoutFaze, &QTimer::timeout, this, &Vdv301testy::slotTimeoutFazeVyprsel);
}


void Vdv301testy::pridejPolozkuTestu(QString jmeno, QString prubeh, QString vysledek,int timeout)
{
    qDebug()<<"Vdv301testy::pridejPolozkuTestu";
    PolozkaTestu novaPolozka;
    novaPolozka.nazev=jmeno;
    novaPolozka.prubeh=prubeh;
    novaPolozka.vysledek=vysledek;
    novaPolozka.timeout=timeout;
    seznamPolozek.append(novaPolozka);

}

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

/*
void Vdv301testy::polozkaBezi(int index, QVector<PolozkaTestu> &seznamPolozek)
{
    qDebug()<<"Vdv301testy::polozkaBezi";
    if (index<seznamPolozek.size()&&(index>=0))
    {
        seznamPolozek[index].prubeh="test bezi";
    }
}

void Vdv301testy::polozkaHotovo(int index, QVector<PolozkaTestu> &seznamPolozek)
{
    qDebug()<<"Vdv301testy::polozkaHotovo";
    if (index<seznamPolozek.size()&&(index>=0))
    {
        seznamPolozek[index].prubeh="hotovo";
    }
}*/




void Vdv301testy::start()
{
qDebug()<<"Vdv301testy::start()";
}

void Vdv301testy::stop()
{
    qDebug()<<"Vdv301testy::stop";
    timerTimeoutFaze->stop();
    testBezi=false;
    seznamPolozek[indexFaze].prubehPrerusen();
    emit update(seznamPolozek);
}

void Vdv301testy::slotTimeoutFazeVyprsel()
{
    qDebug()<<"TestOdberuServer::timeoutFazeVyprsel()"<<" nastaven na"<<timerTimeoutFaze->interval();
    seznamPolozek[indexFaze].prubehTimeout();
    seznamPolozek[indexFaze].vysledekChyba();
    emit update(seznamPolozek);

    this->stop();
}
