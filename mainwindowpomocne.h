#ifndef MAINWINDOWPOMOCNE_H
#define MAINWINDOWPOMOCNE_H

#include <QMainWindow>
#include <QObject>
#include "VDV301publisher/subscriber.h"
#include <QTableWidget>
#include "VDV301struktury/specialnihlaseni.h"


class MainWindowPomocne: public QObject
{
    Q_OBJECT
public:
    MainWindowPomocne();
    // void vypisSubscribery2_2CZ(QVector<Subscriber> adresy);
    static int jeVRozsahu(int index, int pocetHodnot, QString funkce);
    static void naplnTabulkuHlaseni(QTableWidget *vstup, QVector<SpecialniHlaseni> seznamHlaseni);

};

#endif // MAINWINDOWPOMOCNE_H
