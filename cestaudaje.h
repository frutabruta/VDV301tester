#ifndef BLABLA_H
#define BLABLA_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class CestaUdaje : public QMainWindow
{
    Q_OBJECT
public:
    explicit CestaUdaje(QWidget *parent = nullptr);
    QString doorState="AllDoorsClosed";
    QString locationState="AtStop";  
    bool VehicleStopRequested=false;
    bool prestupy=false;
    int cislo;
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
