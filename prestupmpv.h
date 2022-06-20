#ifndef PRESTUPMPV_H
#define PRESTUPMPV_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include "VDV301struktury/prestup.h"
#include <QDateTime>


class PrestupMPV
{
public:
    PrestupMPV();

    void setLin(int pLin);
    QString stan="";
    QString lin="";
    QString alias="";
    int spoj=0;
    QString smer="";

    QDateTime odj;
    QDateTime odjReal;


    int zpoz=0;
    bool np=false;
    bool nad=false;
    QString t="";
    int dd=0;
    int smer_c=0;
    bool sled=false;
    static void ddDoVehicleMode(int dd, QString &mainMode, QString &subMode, Linka &linka);
    Prestup toPrestup();
    static QDateTime posunTimeStampZpozdeni(QDateTime vstupniTimestamp, int zpozdeni);
    static   bool srovnejPrestupy(const PrestupMPV &d1, const PrestupMPV &d2);
    QString vypisPrestup();
    static  QVector<PrestupMPV> seradPrestupyExpectedDeparture(QVector<PrestupMPV> vstup);
    static QDateTime qStringDoQDateTime(QString vstup);
    static QString qDateTimeToString(QDateTime vstup);
private:

};

#endif // PRESTUPMPV_H
