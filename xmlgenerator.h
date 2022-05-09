#ifndef XMLGENERATOR_H
#define XMLGENERATOR_H

#include <QMainWindow>
#include <QObject>
#include "VDV301struktury/zastavka.h"
#include "VDV301struktury/zastavkacil.h"
#include <QCoreApplication>
#include <QDomDocument>
#include "VDV301struktury/cestaudaje.h"
//#include "VDV301struktury/trip.h"
#include "prestupmpv.h"

class xmlGenerator : public QMainWindow
{
    Q_OBJECT

public:
    explicit xmlGenerator(QWidget *parent = nullptr);

    QString devStatus();
    QString createTimestamp();
    static QVector<Pasmo> pasmoStringDoVectoru(QString vstup, QString system, QString tl);

    QDomElement internationalTextType(QString name, QString value, QString language);
    QDomElement ref(QString name, QString value);
    QDomElement xxxProperty2_2CZ1_0(QString nazev, bool vysledek, QString hodnota);

    //struktury
    QString AllData1_0(QVector<ZastavkaCil> docasnySeznamZastavek, QString doorState, QString locationState, QVector<prestupMPV> prestupy, CestaUdaje stav);
    QString AllData_empty_1_0();

    QString AllData2_2CZ1_0(QVector<Spoj> seznamSpoju, QVector<prestupMPV> prestupy, CestaUdaje stav);
    QString AllDataEmpty2_2CZ1_0();

    QString CurrentDisplayContent1_0(int poradi, QVector<ZastavkaCil> docasnySeznamZastavek, CestaUdaje stav);

    QDomElement TripInformation2_2CZ1_0(QVector<Spoj> docasnySeznamTripu, QVector<prestupMPV> prestupy, CestaUdaje stav, int indexSpoje, bool navazny);

    QString TicketValidationService_GetVehicleDataResponse2_2CZ1_0(CestaUdaje stav);
    QString TicketValidationService_GetRazziaResponse2_2CZ1_0(CestaUdaje stav);
    QString TicketValidationService_GetCurrentTariffStopResponse2_2CZ1_0(int poradi, QVector<ZastavkaCil> docasnySeznamZastavek, QString doorState, QString locationState, QVector<prestupMPV> prestupy);

    //operace s pasmy
    QDomElement fareZone1_0(QString shortName);
    QDomElement fareZone2_2CZ1_0(QString shortName, QString longName, QString type, QString language);
    QVector<QDomElement> FareZoneInformationStructure2_2CZ1_0(QVector<Pasmo> seznamPasem, QString language);
    QVector<QDomElement> FareZoneInformationStructure1_0(QVector<Pasmo> seznamPasem);
    QDomElement FareZoneChange2_2CZ1_0(QVector<Pasmo> seznamPasemZ, QVector<Pasmo> seznamPasemNa, QString language);
   // QVector<Pasmo> vratPidPasma(QVector<Pasmo> vstup,QString hledanePasmo);
    //bool podminkaHlasitZmenuPasma(QVector<Pasmo> seznamPasem1, QVector<Pasmo> seznamPasem2);

    QDomElement stopPoint1_0(QVector<ZastavkaCil> docasnySeznamZastavek, int indexZpracZastavky, QVector<prestupMPV> seznamPrestupu, QString language, int currentStopIndex, CestaUdaje stav);
    QDomElement stopPoint2_2CZ1_0(QVector<ZastavkaCil> docasnySeznamZastavek, int indexZpracZastavky, QVector<prestupMPV> seznamPrestupu, QString language, int currentStopIndex);

    QDomElement StopSequence2_2CZ1_0(QDomDocument xmlko, QVector<ZastavkaCil> docasnySeznamZastavek, QString language, int currentStopIndex, QVector<prestupMPV> seznamPrestupu);
    QDomElement ViaPoint2_2CZ1_0(QDomDocument xmlko, Zastavka nacestnaZastavka, QString language);

    QDomElement DisplayContent1_0(QString tagName, QDomDocument xmlko, QVector<ZastavkaCil> docasnySeznamZastavek, QString language, CestaUdaje stav);
    QDomElement DisplayContent2_2CZ1_0(QString tagName, QVector<ZastavkaCil> docasnySeznamZastavek, QString language, int iteracniIndex, int currentStopIndex);

    QDomElement RouteDeviation(QDomDocument xmlko, QString obsah);
    QDomElement DoorOpenState(QDomDocument xmlko, QString obsah);
    QDomElement VehicleMode(QDomDocument xmlko, QString mode, QString subMode);

    QDomDocument connections1_0(QVector<prestupMPV>  lokPrestupy);
    QDomDocument connections2_2CZ1_0(QVector<prestupMPV> seznamPrestupu);

private:
    QDomElement StopSequence1_0(QDomDocument xmlko, QVector<ZastavkaCil> docasnySeznamZastavek, QString language, int currentStopIndex, QVector<prestupMPV> prestupy, CestaUdaje stav);
    QDomElement ViaPoint1_0(QDomDocument xmlko, Zastavka nacestnaZastavka, QString language);
    QDomElement TimeStampTag1_0(QDomDocument xmlko);
    QDomElement additionalTextMessage1_0(QString obsahZpravy);
    QDomElement rawInsert(QString vstup);
    QDomElement additionalTextMessage2_2CZ1_0(QString obsahZpravy);
    QString defaultniJazyk1_0="de";
    QString defaultniJazyk2_2CZ1_0="cz";
signals:

public slots:
};

#endif // XMLGENERATOR_H
