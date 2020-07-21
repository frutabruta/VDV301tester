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
    void dopocetCelni(QString puvodniPrikaz);
    void nastavPort(QString nazev);
    int inicializujSeriovyPort(QString port);
    int zapisDoSeriovehoPortu(QString obsah, QString port);
    QString globalniSeriovyPort="ttyUSB0";
    QString nahradDiakritiku(QString vstup);
private:
    QSerialPort serial;
};

#endif // IBISOVLADANI_H
