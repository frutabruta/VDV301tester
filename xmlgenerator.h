#ifndef XMLGENERATOR_H
#define XMLGENERATOR_H

#include <QMainWindow>
#include <QObject>
#include "VDV301_Display/seznamzastavek.h"
#include <QCoreApplication>
#include <QDomDocument>

class xmlGenerator : public QMainWindow
{
    Q_OBJECT
public:
    explicit xmlGenerator(QWidget *parent = nullptr);
    QByteArray AllData(int poradi, int pocetZastavek, SeznamZastavek *docasnySeznamZastavek , int docasLinka, QString doorState, QString locationState, QByteArray Connections);
    QByteArray devStatus();
    QByteArray createTimestamp();
    QByteArray AllData2(int poradi, int pocetZastavek, SeznamZastavek *docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections, bool poslatHlavicku);
signals:

public slots:
};

#endif // XMLGENERATOR_H
