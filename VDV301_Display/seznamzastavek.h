#ifndef SEZNAMZASTAVEK_H
#define SEZNAMZASTAVEK_H

#include "struktury/pasmo.h"
#include <QMainWindow>
#include <QObject>


class SeznamZastavek
{
public:
    int StopIndex=0;
    int cisloCis=0;
    QString ids="";
    QString StopName="";
    QString LineName="";
    QString LineNumber="";
    QString DestinationName="";
    int DestinationCis=0;
    QString DepartureTime="";
    QString NameFront="";
    QString NameSide="";
    QString NameLcd="";
    QString NameRear="";
    QString NameInner="";
    bool prestupVlak=0;
    bool prestupMetroA=0;
    bool prestupMetroB=0;
    bool prestupMetroC=0;
    bool prestupMetroD=0;
    bool prestupLetadlo=0;
    bool prestupPrivoz=0;
    bool naZnameni=0;


    int cisloOis=0;
    int nacestna=0;
    SeznamZastavek();
    QVector<Pasmo> seznamPasem;

};


#endif // SEZNAMZASTAVEK_H
