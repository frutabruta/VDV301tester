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
    QTimer *timer = new QTimer(this);

    int indexTestu=0;

    void pridejPolozkuTestu(QString jmeno, QString prubeh, QString vysledek);
    QVector<PolozkaTestu> seznamPolozek;
    void start();
    void stop();
    void vymazStavy(QVector<PolozkaTestu> &seznamPolozek2);
public slots:
    void slotCasovacVyprsel();
signals:
    void update(QVector<PolozkaTestu> &seznamPolozek);


};

#endif // VDV301TESTY_H
