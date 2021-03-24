#include "subscriber.h"

Subscriber::Subscriber()
{
this->adresa=QUrl("127.0.0.1:80");
this->struktura="";
}

Subscriber::Subscriber(QUrl adresa2,QString struktura2)
{
    this->adresa=adresa2;
    this->struktura=struktura2;
}


Subscriber::Subscriber(QUrl adresaBezPortu,QString struktura3, int port3)
{
    this->adresa=adresaBezPortu;
    this->struktura=struktura3;
}
