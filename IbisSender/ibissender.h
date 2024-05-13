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
#include <QTimer>

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
    char checkSumCreate(QString puvodniPrikaz, QString &output);
    int delayBetweenMessagesMs() const;
    void setDelayBetweenMessagesMs(int newDelayBetweenMessagesMs);

private slots:
    void slotBytesWritten();

    void slotDelayBetweenMessagesTimeout();
private:
    //QString nahradDiakritiku(QString vstup);

    QTimer casovac;

    int mDelayBetweenMessagesMs=700;

    QString mSerialPortName="COM5";
    //instance knihoven


    /*          nove               */
    QSerialPort serial;

    bool odesilaniBezi=false;

    QVector<QString> zasobnikZprav;

    void writeStringToPort(QSerialPort &port, QString content);
    void startPortu(QSerialPort &port);
signals:
    //new
    void timeout(const QString &s);
};

#endif // IBISSENDER_H
