#include "ipispid.h"

IpisPid::IpisPid() {}


QVector<StopPoint> IpisPid::vytvorNacestne(QVector<StopPointDestination> vstup, int index)
{
    qDebug() << Q_FUNC_INFO;
    QVector <StopPoint> vystup;
    vystup.clear();
    if (index>vstup.count())
    {
        index=vstup.count();
    }


    for (int i = index;i< vstup.count() ; i++)
    {
        qDebug()<<vstup[i].stopPoint.NameInner<<" "<<vstup[i].stopPoint.isViapoint;
        if(vstup[i].stopPoint.isViapoint)
        {
            qDebug()<<"nacestna "<<vstup[i].stopPoint.NameInner;
            vystup.push_back(vstup[i].stopPoint);
        }
    }


    return vystup;

}


void IpisPid::smazPanely ()
{
    qDebug() << Q_FUNC_INFO;
    QString prikaz="";
    prikaz="zA ";
    sendIpisTelegram(prikaz);

    prikaz="zN ";
    sendIpisTelegram(prikaz);

    prikaz="zI2 ";
    sendIpisTelegram(prikaz);

    prikaz="l000";
    sendIpisTelegram(prikaz);
}


int IpisPid::odesliFrontKomplet(QVector<StopPointDestination>zastavky,int index)
{
    qDebug() << Q_FUNC_INFO;
    QString LineName=zastavky[index].line.lineName;
    QString DestinationName= zastavky[index].destination.NameFront;
    // zastavky.last().NameFront;
    sendIpisTelegram(ipisTelegramCompose.slozeniTextuFront(LineName,DestinationName));
    return 1;
}




int IpisPid::odesliRearKomplet(QVector<StopPointDestination>zastavky,int index)
{
    qDebug() << Q_FUNC_INFO;
    QString LineName=zastavky[index].line.lineName;
    //QString DestinationName= zastavky.last().NameFront;
    QString DestinationName= zastavky.at(index).destination.NameFront;
    sendIpisTelegram(ipisTelegramCompose.slozeniTextuRear(LineName));
    return 1;
}




int IpisPid::odesliSideKomplet(QVector <StopPointDestination> zastavky,int index)
{
    qDebug() << Q_FUNC_INFO;
    QString LineName=zastavky[index].line.lineName;
    //QString DestinationName=zastavky.last().NameSide;
    QString DestinationName=zastavky.at(index).destination.NameSide;
    this->sendIpisTelegram(ipisTelegramCompose.slozeniTextuSideAA(vytvorNacestne(zastavky,index),LineName,DestinationName));
    this->sendIpisTelegram("xxxkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk");
    this->sendIpisTelegram(ipisTelegramCompose.slozeniTextuSideZN(vytvorNacestne(zastavky,index)));

    return 1;
}


int IpisPid::odesliInnerKomplet(QVector <StopPointDestination> zastavky,int index)
{
    qDebug() << Q_FUNC_INFO;
    QString LineName=zastavky[index].line.lineName;
    QString DestinationName=zastavky[zastavky.count()-1].destination.NameInner;
    this->sendIpisTelegram(ipisTelegramCompose.slozeniTextuInnerL(LineName));
    this->sendIpisTelegram(ipisTelegramCompose.slozeniTextuInnerV(zastavky[index].stopPoint.NameInner));
    this->sendIpisTelegram(ipisTelegramCompose.slozeniTextuInnerZA(DestinationName));
    //   this->dopocetKontrolnihoZnaku(slozeniTextuInnerZN(vytvorNacestne(zastavky,index)));
    return 1;
}



int IpisPid::odesliJKZKomplet(QVector <StopPointDestination> zastavky,int index)
{
    qDebug() << Q_FUNC_INFO;
    QString LineName=zastavky[index].line.lineName;
    QString DestinationName=zastavky[zastavky.count()-1].destination.NameInner;

    this->sendIpisTelegram(ipisTelegramCompose.slozeniTextuJKZr1(vytvorNacestne( zastavky,index),LineName));
    this->sendIpisTelegram(ipisTelegramCompose.slozeniTextuJKZr2(DestinationName,LineName));
    this->sendIpisTelegram("l"+LineName);
    /*
    this->dopocetCelni(slozeniTextuInnerL(LineName));
    this->dopocetCelni(slozeniTextuInnerV(zastavky[index].NameInner));
    this->dopocetCelni(slozeniTextuInnerZA(DestinationName));
    this->dopocetCelni(slozeniTextuInnerZN(vytvorNacestne(zastavky,index)));
    */
    return 1;
}


int IpisPid::odeslikompletBUSEjednoradekAA(QVector<StopPointDestination> zastavky,int index)
{
    qDebug() << Q_FUNC_INFO;
    QString LineName=zastavky[index].line.lineName;
    //QString DestinationName=zastavky[zastavky.count()-1].NameInner;
    QString DestinationName=zastavky[zastavky.count()-1].destination.NameInner;
    this->sendTelegram(nahradDiakritikuKamenicky(ipisTelegramCompose.slozBUSEjednoradekAA(DestinationName,LineName)));
    return 1;
}
