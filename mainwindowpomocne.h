#ifndef MAINWINDOWPOMOCNE_H
#define MAINWINDOWPOMOCNE_H

#include <QMainWindow>
#include <QObject>
#include "subscriber.h"

class MainWindowPomocne: public QObject
{
    Q_OBJECT
public:
    MainWindowPomocne();
   // void vypisSubscribery2_2CZ(QVector<Subscriber> adresy);
};

#endif // MAINWINDOWPOMOCNE_H