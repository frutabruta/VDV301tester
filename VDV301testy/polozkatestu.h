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
    int timeout=-1;

    void prubehBezi();
    void prubehHotovo();

    void vysledekOk();
    void vysledekChyba();
    void vysledekChyba(QString textChyby);
    void prubehPrerusen();
    void prubehTimeout();
};

#endif // POLOZKATESTU_H
