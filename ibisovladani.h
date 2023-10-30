#ifndef IBISOVLADANI_H
#define IBISOVLADANI_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <VDV301DataStructures/stoppoint.h>
#include <VDV301DataStructures/stoppointdestination.h>


#include <QDebug>
#include <QCoreApplication>




class IbisOvladani: public QObject
{
    Q_OBJECT
public:
    IbisOvladani();
    void smazPanely();
    QString dopocetKontrolnihoZnaku(QString puvodniPrikaz);
  //  int sendToPortOld(QString vstup);

    QString globalniSeriovyPort="COM9";


    int odesliInnerKomplet(QVector<StopPointDestination> zastavky, int index);
    int odesliFrontKomplet(QVector<StopPointDestination> zastavky, int index);
    int odesliSideKomplet(QVector<StopPointDestination> zastavky, int index);
    int odesliJKZKomplet(QVector<StopPointDestination> zastavky, int index);
    int odeslikompletBUSEjednoradekAA(QVector<StopPointDestination> zastavky, int index);
    int odesliRearKomplet(QVector<StopPointDestination> zastavky, int index);


    //nove


    void sendToPortNew(QString obsah);
    void vypisStringPoBytech(QString vstup);
private slots:
    void slotBytesWritten();

private:
    QString nahradDiakritiku(QString vstup);
    QString nahradZobacek(QString vstup);
    QString slozBUSEjednoradekAA(QString DestinationName, QString LineName);
    QString slozeniTextuSideAA(QVector<StopPoint> nacestne, QString LineName, QString DestinationName);
    QString slozeniTextuSideZN(QVector<StopPoint> nacestne);
    QString slozeniTextuFront(QString LineName, QString DestinationName);
    QString slozeniTextuInnerZA(QString DestinationName);
    QString slozeniTextuInnerZN(QVector<StopPoint> nacestne);
    QString slozeniTextuInnerV(QString StopName);
    QString slozeniTextuInnerL(QString LineName);
    QString slozeniTextuJKZr1(QVector<StopPoint> nacestne, QString LineName);
    QString slozeniTextuJKZr2(QString DestinationName, QString LineName);
    QString slozeniTextuRear(QString LineName);
    QVector<StopPoint> vytvorNacestne(QVector<StopPointDestination> vstup, int index);

    QString currentPortName="";
    //instance knihoven


    /*          nove               */
    QSerialPort serial;

    bool odesilaniBezi=false;
    int m_waitTimeout = 0;
    //int adresniBit=1;
    QVector<QString> zasobnikZprav;

    void odesliAdresu(QSerialPort &port, QString adresa);
//    void odesliZbytek(QSerialPort &port, QString zbytek);
    void startPortu(QSerialPort &port);
signals:
    //new
    void timeout(const QString &s);
};

#endif // IBISOVLADANI_H
