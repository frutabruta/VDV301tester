#include "polozkatestu.h"

PolozkaTestu::PolozkaTestu()
{

}


void PolozkaTestu::vysledekOk()
{
    vysledek="OK";
}

void PolozkaTestu::vysledekChyba()
{
    vysledek="chyba";
}

void PolozkaTestu::vysledekChyba(QString textChyby)
{
    vysledek=textChyby;
}

void PolozkaTestu::prubehBezi()
{
    prubeh="test běží";
}

void PolozkaTestu::prubehHotovo()
{
    prubeh="hotovo";
}

void PolozkaTestu::prubehPrerusen()
{
    prubeh="test přerušen";
}

void PolozkaTestu::prubehTimeout()
{
    prubeh="timeout";
}
