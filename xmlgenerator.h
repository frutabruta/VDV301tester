#ifndef XMLGENERATOR_H
#define XMLGENERATOR_H

#include <QMainWindow>
#include <QObject>
#include "VDV301struktury/seznamzastavek.h"
#include <QCoreApplication>
#include <QDomDocument>
#include "VDV301struktury/cestaudaje.h"

class xmlGenerator : public QMainWindow
{
    Q_OBJECT
    QDomElement StopSequence1_0(QDomDocument xmlko, QVector<SeznamZastavek> docasnySeznamZastavek, QString language, int currentStopIndex, QDomDocument Connections, CestaUdaje stav);
    QDomElement ViaPoint1_0(QDomDocument xmlko, SeznamZastavek nacestnaZastavka, QString language);
    QDomElement TimeStampTag1_0(QDomDocument xmlko);
    QDomElement additionalTextMessage1_0(QString obsahZpravy);
    QDomElement AllData_empty_1_0();
public:
    explicit xmlGenerator(QWidget *parent = nullptr);

    QString devStatus();
    QString createTimestamp();
    QString AllData2_2CZ1_0(int poradi, QVector<SeznamZastavek> docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections);
    QString CurrentDisplayContent1_0(int poradi, QVector<SeznamZastavek> docasnySeznamZastavek, CestaUdaje stav);
    QDomElement DisplayContent1_0(QString tagName, QDomDocument xmlko, QVector<SeznamZastavek> docasnySeznamZastavek, QString lineNumber, QString lineName, QString language, QString destinationRef, QString destinationName, CestaUdaje stav);
    QVector<Pasmo> pasmoStringDoVectoru(QString vstup, QString system);
    QDomElement internationalTextType(QString name, QString value, QString language);
    QDomElement fareZone1_0(QString shortName, QString longName, QString type, QString language);
    QDomElement stopPoint1_0(QVector<SeznamZastavek> docasnySeznamZastavek, int indexZpracZastavky, QDomDocument Connections, QString language, int currentStopIndex, CestaUdaje stav);
    QDomElement ref(QString name, QString value);
    QDomElement fareZone2_2CZ1_0(QString shortName, QString longName, QString type, QString language);
    QDomElement StopSequence2_2CZ1_0(QDomDocument xmlko, QVector<SeznamZastavek> docasnySeznamZastavek, QString language, int currentStopIndex, QDomDocument Connections);
    QDomElement stopPoint2_2CZ1_0(QVector<SeznamZastavek> docasnySeznamZastavek, int indexZpracZastavky, QDomDocument Connections, QString language, int currentStopIndex);
    QDomElement ViaPoint2_2CZ1_0(QDomDocument xmlko, SeznamZastavek nacestnaZastavka, QString language);
    QVector<QDomElement> FareZoneInformationStructure2_2CZ1_0(QVector<Pasmo> seznamPasem, QString language);
    QVector<QDomElement> FareZoneInformationStructure1_0(QVector<Pasmo> seznamPasem, QString language);
    QDomElement xxxProperty2_2CZ1_0(QString nazev, bool vysledek, QString hodnota);
    QDomElement DisplayContent2_2CZ1_0(QString tagName, QVector<SeznamZastavek> docasnySeznamZastavek, QString language, int iteracniIndex, int currentStopIndex);
    QString AllData1_0(QVector<SeznamZastavek> docasnySeznamZastavek, int docasLinka, QString doorState, QString locationState, QDomDocument Connections, CestaUdaje stav);
signals:

public slots:
};

#endif // XMLGENERATOR_H
