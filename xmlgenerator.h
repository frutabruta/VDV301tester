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
    QDomElement StopSequence1_0(QDomDocument xmlko, QVector<SeznamZastavek> docasnySeznamZastavek, QString language, int currentStopIndex, QDomDocument Connections);
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
    QVector<Pasmo> pasmoStringDoVectoru(QString vstup, QString system);
    QDomElement internationalTextType(QString name, QString value, QString language);
    QDomElement fareZone1_0(QString shortName, QString longName, QString type, QString language);
    QDomElement stopPoint1_0(QVector<SeznamZastavek> docasnySeznamZastavek, int indexZpracZastavky, QDomDocument Connections, QString language, int currentStopIndex);
    QDomElement ref(QString name, QString value);
    QDomElement fareZone2_2CZ1_0(QString shortName, QString longName, QString type, QString language);
    QDomElement StopSequence2_2CZ1_0(QDomDocument xmlko, QVector<SeznamZastavek> docasnySeznamZastavek, QString language, int currentStopIndex, QDomDocument Connections);
    QDomElement stopPoint2_2CZ1_0(QVector<SeznamZastavek> docasnySeznamZastavek, int indexZpracZastavky, QDomDocument Connections, QString language, int currentStopIndex);
    QDomElement DisplayContent2_2CZ1_0(QString tagName, QDomDocument xmlko, QVector<SeznamZastavek> docasnySeznamZastavek, QString lineNumber, QString lineName, QString language, QString destinationRef, QString destinationName, int currentStopIndex);
    QDomElement ViaPoint2_2CZ1_0(QDomDocument xmlko, SeznamZastavek nacestnaZastavka, QString language);
    QVector<QDomElement> FareZoneInformationStructure2_2CZ1_0(QVector<Pasmo> seznamPasem, QString language);
    QVector<QDomElement> FareZoneInformationStructure1_0(QVector<Pasmo> seznamPasem, QString language);
    QDomElement stopProperty2_2CZ1_0(bool vysledek, QString hodnota);
signals:

public slots:
};

#endif // XMLGENERATOR_H
