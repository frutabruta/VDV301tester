#ifndef BLABLA_H
#define BLABLA_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class CestaUdaje
{

public:
    explicit CestaUdaje(QWidget *parent = nullptr);
    QString doorState="AllDoorsClosed";
    QString locationState="AtStop";  
    bool VehicleStopRequested=false;
    bool prestupy=false;
    int indexAktZastavky;
    int pocetZastavek;
    int aktlinka;
    int aktspoj;
    int cisloVozu;
    int otevreneDvere;
    int vystupniStrana;
    int vymaz();
signals:

public slots:
};

#endif // BLABLA_H
