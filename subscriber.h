#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QObject>
#include <QUrl>

class Subscriber
{
public:
    explicit Subscriber();
    QUrl adresa=QUrl("127.0.0.1");
    QString struktura="";



    Subscriber(QUrl adresa2, QString struktura2);
    Subscriber(QUrl adresaBezPortu, QString struktura3, int port3);
signals:

};



#endif // SUBSCRIBER_H
