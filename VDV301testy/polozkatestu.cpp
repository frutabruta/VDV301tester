#include "polozkatestu.h"

PolozkaTestu::PolozkaTestu()
{

}


void PolozkaTestu::stavOk()
{
    vysledek="OK";
}
void PolozkaTestu::stavChyba(QString textChyby)
{
    vysledek=textChyby;
}
