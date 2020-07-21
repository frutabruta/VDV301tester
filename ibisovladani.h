#ifndef IBISOVLADANI_H
#define IBISOVLADANI_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSerialPort/QSerialPort>



class IbisOvladani
{
public:
    IbisOvladani();
    int kontrolniZnak(QString);
    void smazPanely();
    QString dopocetCelni(QString puvodniPrikaz);
    void odesliDoPortu(QString vstup);
    int inicializujSeriovyPort(QString port);
    int zapisDoSeriovehoPortu(QString obsah, QString port);
    QString globalniSeriovyPort="ttyUSB0";
    QString nahradDiakritiku(QString vstup);
   // QSerialPort serial;
private:

};

#endif // IBISOVLADANI_H
