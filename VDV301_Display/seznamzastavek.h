#ifndef SEZNAMZASTAVEK_H
#define SEZNAMZASTAVEK_H

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
    QString DestinationName="";
    QString DepartureTime="";
    SeznamZastavek();

};


#endif // SEZNAMZASTAVEK_H
