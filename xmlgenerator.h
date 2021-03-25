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
    QDomElement StopSequence1_0(QDomDocument xmlko, QVector<SeznamZastavek> docasnySeznamZastavek, QString language, QString lineNumber, QString lineName, QString destinationName, int currentStopIndex, QDomDocument Connections);
    QDomElement ViaPoint1_0(QDomDocument xmlko, SeznamZastavek nacestnaZastavka, QString language);
    QDomElement TimeStampTag1_0(QDomDocument xmlko);
public:
    explicit xmlGenerator(QWidget *parent = nullptr);

    QString devStatus();
    QString createTimestamp();
    QString AllData1_0(int poradi, QVector<SeznamZastavek> docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections);
    QString AllData2_2CZ1_0(int poradi, QVector<SeznamZastavek> docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections);
    QString CurrentDisplayContent1_0(int poradi, QVector<SeznamZastavek> docasnySeznamZastavek, int docasLinka);
    QDomElement DisplayContent1_0(QString tagName, QDomDocument xmlko, QVector<SeznamZastavek> docasnySeznamZastavek, QString lineNumber, QString lineName, QString language, QString destinationRef, QString destinationName, int currentStopIndex);
signals:

public slots:
};

#endif // XMLGENERATOR_H
