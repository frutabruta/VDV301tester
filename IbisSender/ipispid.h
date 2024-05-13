#ifndef IPISPID_H
#define IPISPID_H

#include "ipissender.h"
#include "ipistelegramcompose.h"
class IpisPid : public IpisSender
{
public:
    IpisPid();

    int odesliInnerKomplet(QVector<StopPointDestination> zastavky, int index);
    int odesliFrontKomplet(QString address, QVector<StopPointDestination> zastavky, int index);
    int odesliSideKomplet(QString address, QVector<StopPointDestination> zastavky, int index);
    int odesliJKZKomplet(QString address, QVector<StopPointDestination> zastavky, int index);
    int odeslikompletBUSEjednoradekAA(QVector<StopPointDestination> zastavky, int index);
    int odesliRearKomplet(QString address, QVector<StopPointDestination> zastavky, int index);

    IpisTelegramCompose ipisTelegramCompose;
    QVector<StopPoint> vytvorNacestne(QVector<StopPointDestination> vstup, int index);
    void smazPanely();
};

#endif // IPISPID_H
