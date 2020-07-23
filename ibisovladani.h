#ifndef IBISOVLADANI_H
#define IBISOVLADANI_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <VDV301_Display/seznamzastavek.h>



class IbisOvladani
{
public:
    IbisOvladani();
    void smazPanely();
    QString dopocetCelni(QString puvodniPrikaz);
    int odesliDoPortu(QString vstup);
    int inicializujSeriovyPort(QString port);
    int zapisDoSeriovehoPortu(QString obsah, QString port);
    QString globalniSeriovyPort="ttyUSB0";
    // QSerialPort serial;
    QVector<SeznamZastavek> vytvorNacestne(QVector<SeznamZastavek> vstup,int index);

    int odesliInnerKomplet(QVector<SeznamZastavek> zastavky, int index);
    int odesliFrontKomplet(QVector<SeznamZastavek> zastavky, int index);
    int odesliSideKomplet(QVector<SeznamZastavek> zastavky, int index);
    QString nahradZobacek(QString vstup);
private:
    QString nahradDiakritiku(QString vstup);
    QString slozeniTextuSide(QVector<SeznamZastavek> nacestne, QString LineName, QString DestinationName);
    QString slozeniTextuFront(QString LineName, QString DestinationName);
    QString slozeniTextuInnerZA(QString DestinationName);
    QString slozeniTextuInnerZN(QVector<SeznamZastavek> nacestne);
    QString slozeniTextuInnerV(QString StopName);
    QString slozeniTextuInnerL(QString LineName);

};

#endif // IBISOVLADANI_H
