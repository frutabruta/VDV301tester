#include "cestaudaje.h"
#include<iostream>
#include <QDebug>
using namespace std;
CestaUdaje::CestaUdaje(QWidget *parent) : QMainWindow(parent)
{
    /*
doorState="AllDoorsClosed";
locationState="AtStop";
VehicleStopRequested=false;
cislo=0;
pocetZastavek=0;
aktlinka=0;
aktspoj=0;
*/
    vymaz();
qInfo() << "inicializace CestaUdaje";
}


int CestaUdaje::vymaz()
{
    doorState="AllDoorsClosed";
    locationState="AtStop";
    VehicleStopRequested=false;
    cislo=0;
    pocetZastavek=0;
    aktlinka=0;
    aktspoj=0;
    qInfo() << "vymaz CestaUdaje";
   return 1;
}
