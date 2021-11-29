#ifndef VDV301TESTY_H
#define VDV301TESTY_H

#include <QObject>
#include <QTimer>

#include "polozkatestu.h"

class Vdv301testy : public QObject
{
    Q_OBJECT
public:
    Vdv301testy();

    int indexFaze=0;
    bool testBezi=false;
    QVector<PolozkaTestu> seznamPolozek;


    void pridejPolozkuTestu(QString jmeno, QString prubeh, QString vysledek, int timeout);
    void vymazStavy(QVector<PolozkaTestu> &seznamPolozek2);
    void emitujUpdate();


    QTimer *timerTimeoutFaze = new QTimer(this);



    //bez slova virtual se spouští start z dceřiné třídy
    //jenTest
    virtual void start();

    void stop();
public slots:
   // void slotCasovacVyprsel();

    void slotTimeoutFazeVyprsel();
signals:
    void update(QVector<PolozkaTestu> &seznamPolozek);
    void testDokoncen(bool vysledek);


};

#endif // VDV301TESTY_H
