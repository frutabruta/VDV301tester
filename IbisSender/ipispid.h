#ifndef IPISPID_H
#define IPISPID_H

#include "ipissender.h"
#include "ipistelegramcompose.h"

#include "VDV301publisher/VDV301DataStructures/stoppointdestination.h"

class IpisPid : public IpisSender
{
public:
    IpisPid();

    int odesliInnerKomplet(QVector<StopPointDestination> zastavky, int index); //unused
    int odesliFrontKomplet(QString address, QVector<StopPointDestination> zastavky, int index);
    int odesliSideKomplet(QString address, QVector<StopPointDestination> zastavky, int index);
    int odesliJKZKomplet(QString address, QVector<StopPointDestination> zastavky, int index);
    int odeslikompletBUSEjednoradekAA(QVector<StopPointDestination> zastavky, int index);
    int odesliRearKomplet(QString address, QVector<StopPointDestination> zastavky, int index);

    IpisTelegramCompose ipisTelegramCompose;
    QVector<StopPoint> vytvorNacestne(QVector<StopPointDestination> vstup, int index);
    void smazPanely(); //unused
};

#endif // IPISPID_H
