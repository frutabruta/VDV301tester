#ifndef POLOZKATESTU_H
#define POLOZKATESTU_H

#include <QObject>

class PolozkaTestu
{
public:
    PolozkaTestu();
    QString nazev="";
    QString prubeh="";
    QString vysledek="";


    void stavOk();
    void stavChyba(QString textChyby);
};

#endif // POLOZKATESTU_H
