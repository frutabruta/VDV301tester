#include "ipistelegramcompose.h"

IpisTelegramCompose::IpisTelegramCompose() {}


QString IpisTelegramCompose::nahradZobacek(QString vstup)
{
    vstup.replace("<","?");
    //vstup.replace("<","<3C>");
    vstup.replace(">","<3E>");
    vstup.replace("?","<3C>");

    return vstup;
}

QString IpisTelegramCompose::slozBUSEjednoradekAA(QString DestinationName,QString LineName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="aA<3B>2 <3E>";
    //vystup+="<0C><1B>l<29><1B>p<0E><17><1B>z<10><1B>t<11><1B><53><1B><22>";
    vystup+=this->nahradZobacek( DestinationName);
    return vystup;
}


QString IpisTelegramCompose::slozeniTextuFront(QString address, QString LineName,QString DestinationName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="";
    // funkcni vystup+="aA1 <1B>b<1B>l<12><0A><1B><22><1B>l<12><1B>p<2D><1B><58>";
    vystup+="aA";
    vystup+=address;
    vystup+=" <1B>b<1B>p<2C><1B><58><1B><22>"; //ME kopie
    //vystup+="aA1 <1B>b<1B>l<12><1B><22><1B><1B>p<2D><1B><58>";
    vystup+=LineName;
    //vystup+="<0C><1B>c<1B><55><1B>l<2E>";
    // funkcni vystup+="<0A><1B><21><1B>c<1B>l<2F><1B><55>";
    vystup+="<0C><1B>c<1B>l<2F><1B><55><1B><21>"; //ME kopie
    vystup+=nahradZobacek( DestinationName);
    vystup+="<0C><1B>c";
    return vystup;
}

QString IpisTelegramCompose::slozeniTextuRear(QString address, QString LineName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="";
    // funkcni vystup+="aA1 <1B>b<1B>l<12><0A><1B><22><1B>l<12><1B>p<2D><1B><58>";
    vystup+="aA";
    vystup+=address;
    vystup+=" <1B>b<1B><58><1B><22>"; //ME kopie
    //vystup+="aA1 <1B>b<1B>l<12><1B><22><1B><1B>p<2D><1B><58>";
    vystup+=LineName;

    return vystup;
}




QString IpisTelegramCompose::slozeniTextuSideAA(QString address, QString LineName,QString DestinationName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="";
    vystup+="aA";
    vystup+=address;
    vystup+=" <1B>b<1B>p+<1B>X<1B><22>"; //ME kopie
    vystup+=LineName;
    vystup+="<0C><1B>c<1B>d<1A><1B>l<2E><1B><52><1B><21>"; //y0
    vystup+=nahradZobacek( DestinationName);
    vystup+="<0C><1B>c";
    return vystup;
}




QString IpisTelegramCompose::slozeniTextuInnerL(QString LineName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="";
    vystup+="l";
    vystup+=LineName;
    return vystup;
}

QString IpisTelegramCompose::slozeniTextuInnerZA(QString DestinationName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="";
    vystup+="zA ";
    vystup+=DestinationName;
    return vystup;
}
QString IpisTelegramCompose::slozeniTextuInnerZN(QVector<StopPoint> nacestne)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="zN ";
    for (int i=0;i<nacestne.count();i++)
    {
        vystup+=nacestne[i].NameInner;
        vystup+="-";
        if (i>3) return vystup;
    }

    return vystup;
}



QString IpisTelegramCompose::slozeniTextuInnerV(QString StopName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="";
    vystup+="v ";
    vystup+=StopName;
    return vystup;
}


QString IpisTelegramCompose::slozeniTextuJKZr1(QString address,QVector<StopPoint> nacestne,QString LineName)
{
    qDebug() << Q_FUNC_INFO;
     //default address 0x3B, <3B>

    QString vystup="aA"+address+"3";
    //vystup+="<1B>p<26><1B><53><1B><22>"; BUSE?
    vystup+="<1B>t<11>";
    // vystup+=LineName;
    // vystup+="<0C><1B>l<29><1B>p<0E><17><1B>z<10><1B>t<11><1B><53><1B><22>"; BUSE?
    //vystup+="<0C><1B>l<29><1B>p<0E><17><1B>z<10><1B>t<11><1B><53><1B><22>";
    vystup+="přes zastávky/via: ";
    int i=0;
    if(nacestne.isEmpty())
    {
        vystup+="<0B>";
        return vystup;
    }
    for (i=0;i<(nacestne.count()-1);i++)
    {
        vystup+= nahradZobacek( nacestne[i].NameInner);

        vystup+=" - ";
        if (i>6)
        {
            vystup+= nahradZobacek( nacestne[i+1].NameInner);
            vystup+="<0B>";
            return vystup;
        }
    }
    vystup+= nahradZobacek( nacestne[i].NameInner);

    vystup+="<0B>";

    return vystup;
}

QString IpisTelegramCompose::slozeniTextuJKZr2(QString address, QString DestinationName,QString LineName)
{
    //default address 0x3B, <3B>
    qDebug() << Q_FUNC_INFO;
    QString vystup="aA"+address+"2";
    //vystup+="<1B>p<26><1B><53><1B><22>"; BUSE?
    //vystup+="<1B>t<11>";
    // vystup+=LineName;
    // vystup+="<0C><1B>l<29><1B>p<0E><17><1B>z<10><1B>t<11><1B><53><1B><22>"; BUSE?
    //vystup+="<0C><1B>l<29><1B>p<0E><17><1B>z<10><1B>t<11><1B><53><1B><22>";
    vystup+=nahradZobacek(DestinationName);



    return vystup;
}

QString IpisTelegramCompose::slozeniTextuSideAA2(QString address,QVector<StopPoint> nacestne)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="";
    vystup+="aA";
    vystup+=address;

    vystup+=" <1B>b<1B>h<18><1B>l<2E><0A><1B>z<20>"; //ME kopie
    // vystup+="<1A><1B>l<2F><1B><51><1B><21>"; //ME kopie
    vystup+="<0A><1B>z<20><1B>Q<1B>!Přes zastávky:";
    for (int i =0;i<nacestne.count();i++)
    {
        vystup+="<0A><1B>z<20><1B>Q<1B>!";
        vystup+=nahradZobacek(nacestne[i].NameSide);
    }
    vystup+="<0A><1B>z<20><1B>Q<1B>!";
    vystup+="<0B>";

    return vystup;
}

QString IpisTelegramCompose::slozeniTextuSideAAold(QVector<StopPoint> nacestne,QString LineName,QString DestinationName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="";
    vystup+="aA2 ";
    vystup+="<1B>p<2C><1B><58><1B><22>"; //ME kopie
    vystup+=LineName;
    vystup+="<0C><1B>c<1B>l<2F><1B><51><1B><21>"; //y0
    vystup+=nahradZobacek( DestinationName);
    vystup+="<0C><1B>c";
    for (int i =0;i<nacestne.count();i++)
    {
        vystup+="<1B><3A>"; //y10
        vystup+=nacestne[i].NameSide;

    }
    vystup+="<0B>";


    return vystup;
}
QString IpisTelegramCompose::slozeniTextuSideZNold(QVector<StopPoint> nacestne)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="";
    vystup+="zN ";
    vystup+="<1B>z<1A><1B>l<2F><1B><51><1B><21>"; //ME kopie

    for (int i =0;i<nacestne.count();i++)
    {
        vystup+="<0A>";
        vystup+=nahradZobacek(nacestne[i].NameSide);


    }
    vystup+="<0B>";

    return vystup;
}

