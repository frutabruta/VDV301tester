#ifndef IPISTELEGRAMCOMPOSE_H
#define IPISTELEGRAMCOMPOSE_H

#include "../VDV301DataStructures/stoppoint.h"
#include <QObject>
class IpisTelegramCompose
{
public:
    IpisTelegramCompose();
    QString slozBUSEjednoradekAA(QString DestinationName, QString LineName);
    QString slozeniTextuFront(QString address, QString LineName, QString DestinationName);
    QString slozeniTextuRear(QString address, QString LineName);
    QString slozeniTextuSideAA(QString address, QString LineName, QString DestinationName);
    QString slozeniTextuInnerL(QString LineName);
    QString slozeniTextuInnerZA(QString DestinationName);
    QString slozeniTextuInnerZN(QVector<StopPoint> nacestne);
    QString slozeniTextuInnerV(QString StopName);
    QString slozeniTextuJKZr1(QString address, QVector<StopPoint> nacestne, QString LineName);
    QString slozeniTextuJKZr2(QString address, QString DestinationName, QString LineName);
    QString slozeniTextuSideAA2(QString address, QVector<StopPoint> nacestne);
    QString nahradZobacek(QString vstup);
    QString slozeniTextuSideZNold(QVector<StopPoint> nacestne);
private:
    QString slozeniTextuSideAAold(QVector<StopPoint> nacestne, QString LineName, QString DestinationName);
};

#endif // IPISTELEGRAMCOMPOSE_H
