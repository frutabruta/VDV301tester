#ifndef SQLROPIDXMLQUERIES_H
#define SQLROPIDXMLQUERIES_H

#include <QMainWindow>

#include <QWidget>

#include "VDV301publisher/VDV301DataStructures/line.h"
#include "VDV301publisher/VDV301DataStructures/trip.h"
#include "VDV301publisher/VDV301DataStructures/farezone.h"
#include "VDV301publisher/VDV301DataStructures/vehiclerun.h"

#include "MapaVykresleni/mapabod.h"

#include "XmlRopidImportStream/sqlitebase.h"


class SqlRopidXmlQueries: public  SqLiteBase
{
    Q_OBJECT
public:
    
    SqlRopidXmlQueries();

    QSqlQueryModel *getLineListModel(QString kj);
    QSqlQueryModel *getRootLineListModel(QString kj);
    QSqlQueryModel *getVehicleRunListModel(Line line, QString kj);
    QSqlQueryModel *getTripListFromVehicleRunModel(VehicleRun &vehicleRun, QString kj);
    QSqlQueryModel *getLineStopListModel(Line line, QString kj);

    //SQL queries
    int getDatasetValidity(QDate &dateFrom, QDate &dateTo, QString &ver);
    int getTripSfromC(Trip &trip, QString kj); //unused
    int getTripListFromVehicleRun(VehicleRun &vehicleRun, QString kj);
    QVector<MapaBod> getTrajectoryFromTripS(int tripS, QString kj);
    int getVehicleRunFromTripLC(Trip trip, int &rootLine, int &vehicleRun, int &tripIndex, QString kj); //unused
    int getVehicleRunStops(QVector<Trip> &tripList, int tripIndex, QString kj);

    //auxiliary functions    
    QString createValidyMaskFromDate(QDate workingDate, QDate validityStart, QDate validityEnd);
    QString fareZoneToString(QVector<FareZone> fareZoneList, QString delimiter);
    
    
    bool getPolygonFromStopPoint(StopPoint &stopPoint, QString kj, bool out);
    Trip getTripDescriptionFromId(int tripId, QString kj);
    int getVehicleRunFromTripS(Trip trip, int &rootLine, int &vehicleRun, int &tripIndex, QString kj);
    QString getTrajectoryType();

private:
    QVector<QString> getNotesFromTripS(int tripS, int xorder);
    QVector<StopNote> getNotesFromTripSNew(int tripS, int xorder);

    QString createGetTripQueryBase();

    static double absoluteValue(double input);
    QVector<FareZone> createInterRegionFareZones(QVector<QString> tp, QVector<QString> pz, QVector<QString> pc, QString cids, QString tl);
    QVector<FareZone> fareZoneListStringToVector(QString inputText, QString system, QString tl);

    QSqlQueryModel *queryModelWrapper(const QString &queryString, const QVariantMap &bindings);
};

#endif // SQLROPIDXMLQUERIES_H
