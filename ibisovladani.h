#ifndef IBISOVLADANI_H
#define IBISOVLADANI_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <VDV301struktury/zastavka.h>
#include <VDV301struktury/zastavkacil.h>



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
    QVector<Zastavka> vytvorNacestne(QVector<ZastavkaCil> vstup, int index);

    int odesliInnerKomplet(QVector<ZastavkaCil> zastavky, int index);
    int odesliFrontKomplet(QVector<ZastavkaCil> zastavky, int index);
    int odesliSideKomplet(QVector<ZastavkaCil> zastavky, int index);
    QString nahradZobacek(QString vstup);
    QString slozeniTextuSideZN(QVector<Zastavka> nacestne);
    int odesliJKZKomplet(QVector<ZastavkaCil> zastavky, int index);


    //QString odeslikompletBUSEjednoradekAA(QVector<SeznamZastavek> nacestne, QString DestinationName, QString LineName);
    //QString odeslikompletBUSEjednoradekAA(QVector<SeznamZastavek> zastavky, int index);
    int odeslikompletBUSEjednoradekAA(QVector<ZastavkaCil> zastavky, int index);
    int odesliRearKomplet(QVector<ZastavkaCil> zastavky, int index);
private:
    QString nahradDiakritiku(QString vstup);
    QString slozBUSEjednoradekAA(QString DestinationName, QString LineName);
    QString slozeniTextuSideAA(QVector<Zastavka> nacestne, QString LineName, QString DestinationName);
    QString slozeniTextuFront(QString LineName, QString DestinationName);
    QString slozeniTextuInnerZA(QString DestinationName);
    QString slozeniTextuInnerZN(QVector<Zastavka> nacestne);
    QString slozeniTextuInnerV(QString StopName);
    QString slozeniTextuInnerL(QString LineName);
    QString slozeniTextuJKZr1(QVector<Zastavka> nacestne, QString LineName);
    QString slozeniTextuJKZr2(QString DestinationName, QString LineName);
    QString slozeniTextuRear(QString LineName);
    QString currentPortName="";
};

#endif // IBISOVLADANI_H
