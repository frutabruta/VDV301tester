#ifndef IBISSENDER_H
#define IBISSENDER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <VDV301DataStructures/stoppoint.h>
#include <VDV301DataStructures/stoppointdestination.h>


#include <QDebug>
#include <QCoreApplication>


class IbisSender: public QObject
{
    Q_OBJECT
public:
    IbisSender();
    ~IbisSender();


   // void smazPanely();
    QString sendTelegram(QString puvodniPrikaz);
  //  int sendToPortOld(QString vstup);

    //nove


    void sendToPortNew(QString obsah);
    void vypisStringPoBytech(QString vstup);
    void portStop(QSerialPort &port);

    QString serialPortName() const;
    void setSerialPortName(const QString &newSerialPortName);

    void start();
    void stop();
    char checkSumCreate(QString puvodniPrikaz);
private slots:
    void slotBytesWritten();

private:
    //QString nahradDiakritiku(QString vstup);



    QString mSerialPortName="COM5";
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

#endif // IBISSENDER_H
