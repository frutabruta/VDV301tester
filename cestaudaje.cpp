#include "cestaudaje.h"
#include<iostream>
#include <QDebug>
using namespace std;
CestaUdaje::CestaUdaje(QWidget *parent) : QMainWindow(parent)
{
qDebug()<<"CestaUdaje::CestaUdaje";
    vymaz();

}


int CestaUdaje::vymaz()
{
    qDebug()<<"CestaUdaje::vymaz()";
    doorState="AllDoorsClosed";
    locationState="AtStop";
    VehicleStopRequested=false;
    cislo=0;
    pocetZastavek=0;
    aktlinka=0;
    aktspoj=0;
   return 1;
}
