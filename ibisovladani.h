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
    QString slozeniTextuSideZN(QVector<SeznamZastavek> nacestne);
    int odesliJKZKomplet(QVector<SeznamZastavek> zastavky, int index);

    QString slozBUSEjednoradekAA(QVector<SeznamZastavek> nacestne, QString DestinationName, QString LineName);
    //QString odeslikompletBUSEjednoradekAA(QVector<SeznamZastavek> nacestne, QString DestinationName, QString LineName);
    //QString odeslikompletBUSEjednoradekAA(QVector<SeznamZastavek> zastavky, int index);
    int odeslikompletBUSEjednoradekAA(QVector<SeznamZastavek> zastavky, int index);
    int odesliRearKomplet(QVector<SeznamZastavek> zastavky, int index);
private:
    QString nahradDiakritiku(QString vstup);
    QString slozeniTextuSideAA(QVector<SeznamZastavek> nacestne, QString LineName, QString DestinationName);
    QString slozeniTextuFront(QString LineName, QString DestinationName);
    QString slozeniTextuInnerZA(QString DestinationName);
    QString slozeniTextuInnerZN(QVector<SeznamZastavek> nacestne);
    QString slozeniTextuInnerV(QString StopName);
    QString slozeniTextuInnerL(QString LineName);
    QString slozeniTextuJKZr1(QVector<SeznamZastavek> nacestne, QString LineName);
    QString slozeniTextuJKZr2(QString DestinationName, QString LineName);
    QString slozeniTextuRear(QString LineName);
};

#endif // IBISOVLADANI_H
