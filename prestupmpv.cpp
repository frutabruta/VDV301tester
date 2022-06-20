#include "prestupmpv.h"


PrestupMPV::PrestupMPV()
{

}

void PrestupMPV::setLin(int pLin)
{
    this->lin= pLin;
}


Prestup PrestupMPV::toPrestup()
{

    Prestup vystup;
    /*
    void setLin(int pLin);
    QString lin="";
    int spoj=0;
    QString odj="";
    int zpoz=0;
    bool np=false;
    bool nad=false;
    QString t="";
    int smer_c=0;
    bool sled=false;   */

/*
    QString connectionProperty="";
    QString connectionType="";
    QString destination="";
    Linka line;*/

    vystup.line.LineName=this->alias;
    vystup.destinationName=this->smer;
    vystup.platform=this->stan;
    vystup.expectedDepartureTime=PrestupMPV::qDateTimeToString( posunTimeStampZpozdeni(this->odj,  this->zpoz ));
    vystup.scheduledDepartureTime=PrestupMPV::qDateTimeToString( this->odj);
    ddDoVehicleMode(this->dd,vystup.mainMode,vystup.subMode,vystup.line);

    return vystup;

}


QDateTime PrestupMPV::posunTimeStampZpozdeni(QDateTime vstupniTimestamp, int zpozdeni)
{

    return vstupniTimestamp.addSecs(zpozdeni*60);

}

QDateTime  PrestupMPV::qStringDoQDateTime(QString vstup)
{
    return QDateTime::fromString(vstup,Qt::ISODate);
}

QString PrestupMPV::qDateTimeToString(QDateTime vstup)
{
     return vstup.toString(Qt::ISODate);
}






void PrestupMPV::ddDoVehicleMode(int dd, QString &mainMode, QString &subMode, Linka &linka)
{
    qDebug()<<"PrestupMPV::ddDoVehicleMode "<<dd;

    /*
    bool isDiversion=false;
    bool isNight=false;
    bool isReplacement=false;
*/




    switch(dd)
    {
    case 1: //Metro
        mainMode="MetroSubmode";
        subMode="metro";

        break;
    case 2: //Denní tramvaj
        mainMode="TramSubmode";
        subMode="localTram";

        break;

    case 3: //Denní městská autobusová linka
        mainMode="BusSubmode";
        subMode="localBus";

        break;
    case 4: //Denní příměstská nebo regionální linka
        mainMode="BusSubmode";
        subMode="regionalBus";

        break;
    case 5: //Noční městská autobusová linka
        mainMode="BusSubmode";
        subMode="localBus";
        linka.isNight=true;

        break;
    case 6: //Noční tramvaj
        mainMode="TramSubmode";
        subMode="localTram";
        linka.isNight=true;

        break;
    case 7: //Linka náhradní dopravy, městský autobus
        mainMode="BusSubmode";
        subMode="localBus";
        linka.isReplacement=true;

        break;

    case 8: //Lanovka
        mainMode="FunicularSubmode";
        subMode="funicular";

        break;
    case 9: //Školní linka
        mainMode="BusSubmode";
        subMode="schoolBus";
        linka.isSchool=true;

        break;

    case 10: //Invalidní
        mainMode="BusSubmode";
        subMode="specialNeedsBus";
        linka.isWheelchair=true;

        break;
    case 11: //Smluvni
        mainMode="BusSubmode";
        subMode="localBus";
        linka.isSpecial=true;
        qDebug()<<"linka je specialni";


        break;
    case 12: //Přívoz
        mainMode="WaterSubmode";
        subMode="localPassengerFerry";

        break;
    case 13: //Vlaky PID – linky S nebo R
        mainMode="RailSubmode";
        subMode="regionalRail";

        break;
    case 14: //Linka náhradní dopravy, NAD za vlak
        mainMode="BusSubmode";
        subMode="railReplacementBus";
        linka.isReplacement=true;

        break;
    case 15: //Linka náhradní dopravy, Tram
        mainMode="TramSubmode";
        subMode="localTram";
        linka.isReplacement=true;

        break;

    case 16: //Noční příměstská nebo regionální linka
        mainMode="BusSubmode";
        subMode="regionalBus";
        linka.isNight=true;

        break;

    case 17: //Linka mimo systém PID (3 znaky)
        mainMode="BusSubmode";
        subMode="undefined";

        break;
    case 18: //Denní trolejbusová linka
        mainMode="TrolleybusSubmode";
        subMode="localTrolleybus";

        break;

        /*
    case XX: //Lanovka do Bohnic
        mainMode="TelecabinSubmode";
        subMode="telecabin";

        break;
        */


    default:
        mainMode="BusSubmode";
        subMode="undefined";
        break;

    }
}




bool PrestupMPV::srovnejPrestupy(const PrestupMPV &d1, const PrestupMPV &d2)
{
  //  return d1.smer < d2.smer; // sort by namefile

    return d1.odjReal <d2.odjReal;

}

QString PrestupMPV::vypisPrestup()
{
    QString vystup;
    vystup=vystup+"prestup: "+this->alias+" "+this->smer+" "+this->odj.toString()+" "+QString::number(this->zpoz)+" "+this->stan;
    return vystup;
}


QVector<PrestupMPV> PrestupMPV::seradPrestupyExpectedDeparture(QVector<PrestupMPV> vstup)
{
    qDebug()<<"PrestupMPV::seradPrestupyExpectedDeparture";


    foreach(PrestupMPV aktPrestup,vstup)
    {
        qDebug()<<aktPrestup.vypisPrestup();
    }

    qDebug()<<"serazeno:";

   std::sort(vstup.begin(),vstup.end(),PrestupMPV::srovnejPrestupy );

   foreach(PrestupMPV aktPrestup,vstup)
   {
       qDebug()<<aktPrestup.vypisPrestup();
   }


   return vstup;
}










