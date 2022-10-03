#include "ibisovladani.h"

IbisOvladani::IbisOvladani()
{
    connect(&serial, &QSerialPort::bytesWritten ,this,&IbisOvladani::slotBytesWritten );
    startPortu(serial);
}



QString IbisOvladani::nahradDiakritiku(QString vstup)
{
    qDebug() << Q_FUNC_INFO;
    if (vstup.isEmpty())
    {
        return vstup;
    }
    //BUSE kodovani
    /*
    vstup.replace("á","<0E><20>");
    vstup.replace("Á","<0E><0F>");
    vstup.replace("č","<0E><07>");
    vstup.replace("Č","<0E><00>");
    vstup.replace("ď","<0E><03>");
    vstup.replace("Ď","<0E><05>");
    vstup.replace("é","<0E><02>");
    vstup.replace("É","<0E><10>");
    vstup.replace("ě","<0E><08>");
    vstup.replace("Ě","<0E><09>");
    vstup.replace("í","<0E><21>");
    vstup.replace("Í","<0E><0B>");
    vstup.replace("ň","<0E><24>");
    vstup.replace("Ň","<0E><25>");
    vstup.replace("ó","<0E><22>");
    vstup.replace("Ó","<0E><15>");
    vstup.replace("ř","<0E><29>");
    vstup.replace("Ř","<0E><1E>");
    vstup.replace("š","<0E><28>");
    vstup.replace("Š","<0E><1B>");
    vstup.replace("ť","<0E><1F>");
    vstup.replace("Ť","<0E><06>");
    vstup.replace("ú","<0E><23>");
    vstup.replace("Ú","<0E><17>");
    vstup.replace("ů","<0E><16>");
    vstup.replace("Ů","<0E><26>");
    vstup.replace("ý","<0E><18>");
    vstup.replace("Ý","<0E><1D>");
    vstup.replace("ž","<0E><11>");
    vstup.replace("Ž","<0E><12>");*/

    //IPIS kodovani
    vstup.replace("á","<0E><41>"); //chybička zobrazuje D
    vstup.replace("Á","<0E><61>");
    vstup.replace("č","<0E><43>");
    vstup.replace("Č","<0E><63>");
    vstup.replace("ď","<0E><44>");
    vstup.replace("Ď","<0E><64>");
    vstup.replace("é","<0E><57>");
    vstup.replace("É","<0E><77>");
    vstup.replace("ě","<0E><45>");
    vstup.replace("Ě","<0E><65>");
    vstup.replace("í","<0E><49>");
    vstup.replace("Í","<0E><69>");
    vstup.replace("ň","<0E><4E>");
    vstup.replace("Ň","<0E><6E>");
    vstup.replace("ó","<0E><4F>");
    vstup.replace("Ó","<0E><6F>");
    vstup.replace("ř","<0E><52>");
    vstup.replace("Ř","<0E><72>");
    vstup.replace("š","<0E><53>");
    vstup.replace("Š","<0E><73>");
    vstup.replace("ť","<0E><54>");
    vstup.replace("Ť","<0E><74>");
    vstup.replace("ú","<0E><55>");
    vstup.replace("Ú","<0E><75>");
    vstup.replace("ů","<0E><4A>");
    vstup.replace("Ů","<0E><6A>");
    vstup.replace("ý","<0E><59>");
    vstup.replace("Ý","<0E><79>");
    vstup.replace("ž","<0E><5A>");
    vstup.replace("Ž","<0E><7A>");




    return vstup;
}


QString IbisOvladani::dopocetKontrolnihoZnaku(QString puvodniPrikaz)
{

    qDebug() << Q_FUNC_INFO;
    puvodniPrikaz=nahradDiakritiku(puvodniPrikaz);
    qDebug()<<puvodniPrikaz;

    QString prikaz = "";
    QString output="";
    char zacatecniByte=0x7F;
    char ridiciZnak=0;
    char jeZnak=5;

    char hexridiciznak[2];

    prikaz=puvodniPrikaz+'\r';

    for (int k=0; k<prikaz.length(); k++)
    {
        if (prikaz[k]=='<')
        {
            jeZnak=0;
        }
        if (prikaz[k]=='>')
        {
            jeZnak=4;
        }
        switch (jeZnak)
        {
        case 0:
            jeZnak++;
            break;

        case 1:
            hexridiciznak[0]=prikaz[k].toLatin1() ;
            jeZnak++;
            break;

        case 2:
            hexridiciznak[1]=prikaz[k].toLatin1();
            jeZnak++;
            break;

        case 3:
            jeZnak++;
            break;
        case 4:
            ridiciZnak=int(strtol(hexridiciznak,NULL,16));
            zacatecniByte=zacatecniByte^ridiciZnak;
            output+=ridiciZnak;
            hexridiciznak[0]=0;
            hexridiciznak[1]=0;
            jeZnak++;
            break;
        case 5:
            zacatecniByte=zacatecniByte^prikaz[k].toLatin1();
            output+=prikaz[k];
            break;
        }

    }

    output+=zacatecniByte;
    qDebug()<<"kontrolni soucet je "<<zacatecniByte;
    sendToPortNew(output);
    //sendToPortOld(output);

    return output;

}


void IbisOvladani::smazPanely ()
{
    qDebug() << Q_FUNC_INFO;
    QString prikaz="";
    prikaz="zA ";
    dopocetKontrolnihoZnaku(prikaz);

    prikaz="zN ";
    dopocetKontrolnihoZnaku(prikaz);

    prikaz="zI2 ";
    dopocetKontrolnihoZnaku(prikaz);

    prikaz="l000";
    dopocetKontrolnihoZnaku(prikaz);
}
/*
int IbisOvladani::sendToPortOld(QString vstup)
{
    qDebug() << Q_FUNC_INFO;
    bool currentPortNameChanged = false;
    QString portName=globalniSeriovyPort;
    // QString currentPortName=globalniSeriovyPort;
    if (currentPortName != portName) {
        currentPortName = portName;
        currentPortNameChanged = true;
        qDebug()<<"jmeno portu se zmenilo na "<<currentPortName;
    }

    int waitTimeout=1000;
    int currentWaitTimeout = waitTimeout;
    QString request=vstup;
    QString currentRequest = request;
    QSerialPort serial;

    if (currentPortName.isEmpty()) {
        qDebug()<<"No port name specified";
        return 0;
    }
    int quit=0;
    while (!quit) {
        if (currentPortNameChanged)
        {
            serial.close();
            serial.setPortName(currentPortName);
            if(serial.open(QIODevice::ReadWrite))
            {
                qDebug()<<"port "<<currentPortName<<" je otevren";
            }

            serial.setBaudRate(1200);
            serial.setDataBits(QSerialPort::Data7);
            serial.setParity(QSerialPort::EvenParity);
            serial.setStopBits(QSerialPort::TwoStop);
            serial.setFlowControl(QSerialPort::NoFlowControl);


        }
        //! [7] //! [8]
        // write request
        QByteArray requestData = currentRequest.toLocal8Bit();
        if(!serial.isOpen())
        {
            qDebug()<<"seriovy port NENI otevreny";

            return 0;

        }
        else
        {
            qDebug()<<"seriovy port JE otevreny";
            serial.write(requestData);
            if (serial.waitForBytesWritten(waitTimeout))
            {

            }
            else
            {
            }
        }


        quit=1;
    }
    qDebug()<<"konec odesliDoPortu";
    return 1;
}
*/


QVector<Zastavka> IbisOvladani::vytvorNacestne(QVector<ZastavkaCil> vstup, int index)
{
    qDebug() << Q_FUNC_INFO;
    QVector <Zastavka> vystup;
    vystup.clear();
    if (index>vstup.count())
    {
        index=vstup.count();
    }


    for (int i = index;i< vstup.count() ; i++)
    {
        qDebug()<<vstup[i].zastavka.NameInner<<" "<<vstup[i].zastavka.nacestna;
        if(vstup[i].zastavka.nacestna==1)
        {
            qDebug()<<"nacestna "<<vstup[i].zastavka.NameInner;
            vystup.push_back(vstup[i].zastavka);
        }
    }


    return vystup;

}

QString IbisOvladani::slozeniTextuFront(QString LineName,QString DestinationName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="";
    // funkcni vystup+="aA1 <1B>b<1B>l<12><0A><1B><22><1B>l<12><1B>p<2D><1B><58>";
    vystup+="aA1 <1B>b<1B>p<2C><1B><58><1B><22>"; //ME kopie
    //vystup+="aA1 <1B>b<1B>l<12><1B><22><1B><1B>p<2D><1B><58>";
    vystup+=LineName;
    //vystup+="<0C><1B>c<1B><55><1B>l<2E>";
    // funkcni vystup+="<0A><1B><21><1B>c<1B>l<2F><1B><55>";
    vystup+="<0C><1B>c<1B>l<2F><1B><55><1B><21>"; //ME kopie
    vystup+=nahradZobacek( DestinationName);
    vystup+="<0C><1B>c";
    return vystup;
}
int IbisOvladani::odesliFrontKomplet(QVector<ZastavkaCil>zastavky,int index)
{
    qDebug() << Q_FUNC_INFO;
    QString LineName=zastavky[index].linka.LineName;
    QString DestinationName= zastavky[index].cil.NameFront;
    // zastavky.last().NameFront;
    dopocetKontrolnihoZnaku(slozeniTextuFront(LineName,DestinationName));
    return 1;
}


QString IbisOvladani::slozeniTextuRear(QString LineName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="";
    // funkcni vystup+="aA1 <1B>b<1B>l<12><0A><1B><22><1B>l<12><1B>p<2D><1B><58>";
    vystup+="aA4 <1B>b<1B><58><1B><22>"; //ME kopie
    //vystup+="aA1 <1B>b<1B>l<12><1B><22><1B><1B>p<2D><1B><58>";
    vystup+=LineName;

    return vystup;
}

int IbisOvladani::odesliRearKomplet(QVector<ZastavkaCil>zastavky,int index)
{
    qDebug() << Q_FUNC_INFO;
    QString LineName=zastavky[index].linka.LineName;
    //QString DestinationName= zastavky.last().NameFront;
    QString DestinationName= zastavky.at(index).cil.NameFront;
    dopocetKontrolnihoZnaku(slozeniTextuRear(LineName));
    return 1;
}


QString IbisOvladani::slozeniTextuSideAA(QVector<Zastavka> nacestne,QString LineName,QString DestinationName)
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
QString IbisOvladani::slozeniTextuSideZN(QVector<Zastavka> nacestne)
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

int IbisOvladani::odesliSideKomplet(QVector <ZastavkaCil> zastavky,int index)
{
    qDebug() << Q_FUNC_INFO;
    QString LineName=zastavky[index].linka.LineName;
    //QString DestinationName=zastavky.last().NameSide;
    QString DestinationName=zastavky.at(index).cil.NameSide;
    this->dopocetKontrolnihoZnaku(slozeniTextuSideAA(vytvorNacestne(zastavky,index),LineName,DestinationName));
    this->dopocetKontrolnihoZnaku(slozeniTextuSideZN(vytvorNacestne(zastavky,index)));

    return 1;
}


int IbisOvladani::odesliInnerKomplet(QVector <ZastavkaCil> zastavky,int index)
{
    qDebug() << Q_FUNC_INFO;
    QString LineName=zastavky[index].linka.LineName;
    QString DestinationName=zastavky[zastavky.count()-1].cil.NameInner;
    this->dopocetKontrolnihoZnaku(slozeniTextuInnerL(LineName));
    this->dopocetKontrolnihoZnaku(slozeniTextuInnerV(zastavky[index].zastavka.NameInner));
    this->dopocetKontrolnihoZnaku(slozeniTextuInnerZA(DestinationName));
    this->dopocetKontrolnihoZnaku(slozeniTextuInnerZN(vytvorNacestne(zastavky,index)));
    return 1;
}

QString IbisOvladani::slozeniTextuInnerL(QString LineName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="";
    vystup+="l";
    vystup+=LineName;
    return vystup;
}

QString IbisOvladani::slozeniTextuInnerZA(QString DestinationName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="";
    vystup+="zA ";
    vystup+=DestinationName;
    return vystup;
}
QString IbisOvladani::slozeniTextuInnerZN(QVector<Zastavka> nacestne)
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



QString IbisOvladani::slozeniTextuInnerV(QString StopName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="";
    vystup+="v ";
    vystup+=StopName;
    return vystup;
}


QString IbisOvladani::slozeniTextuJKZr1(QVector<Zastavka> nacestne,QString LineName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="aA<3B>3";
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

QString IbisOvladani::slozeniTextuJKZr2(QString DestinationName,QString LineName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="aA<3B>2";
    //vystup+="<1B>p<26><1B><53><1B><22>"; BUSE?
    //vystup+="<1B>t<11>";
    // vystup+=LineName;
    // vystup+="<0C><1B>l<29><1B>p<0E><17><1B>z<10><1B>t<11><1B><53><1B><22>"; BUSE?
    //vystup+="<0C><1B>l<29><1B>p<0E><17><1B>z<10><1B>t<11><1B><53><1B><22>";
    vystup+=nahradZobacek(DestinationName);



    return vystup;
}


int IbisOvladani::odesliJKZKomplet(QVector <ZastavkaCil> zastavky,int index)
{
    qDebug() << Q_FUNC_INFO;
    QString LineName=zastavky[index].linka.LineName;
    QString DestinationName=zastavky[zastavky.count()-1].cil.NameInner;

    this->dopocetKontrolnihoZnaku(slozeniTextuJKZr1(vytvorNacestne( zastavky,index),LineName));
    this->dopocetKontrolnihoZnaku(slozeniTextuJKZr2(DestinationName,LineName));
    this->dopocetKontrolnihoZnaku("l"+LineName);
    /*
    this->dopocetCelni(slozeniTextuInnerL(LineName));
    this->dopocetCelni(slozeniTextuInnerV(zastavky[index].NameInner));
    this->dopocetCelni(slozeniTextuInnerZA(DestinationName));
    this->dopocetCelni(slozeniTextuInnerZN(vytvorNacestne(zastavky,index)));
    */
    return 1;
}


QString IbisOvladani::nahradZobacek(QString vstup)
{
    vstup.replace("<","?");
    //vstup.replace("<","<3C>");
    vstup.replace(">","<3E>");
    vstup.replace("?","<3C>");

    return vstup;
}

QString IbisOvladani::slozBUSEjednoradekAA(QString DestinationName,QString LineName)
{
    qDebug() << Q_FUNC_INFO;
    QString vystup="aA<3B>2 <3E>";
    //vystup+="<0C><1B>l<29><1B>p<0E><17><1B>z<10><1B>t<11><1B><53><1B><22>";
    vystup+=this->nahradZobacek( DestinationName);
    return vystup;
}

int IbisOvladani::odeslikompletBUSEjednoradekAA(QVector<ZastavkaCil> zastavky,int index)
{
    qDebug() << Q_FUNC_INFO;
    QString LineName=zastavky[index].linka.LineName;
    //QString DestinationName=zastavky[zastavky.count()-1].NameInner;
    QString DestinationName=zastavky[zastavky.count()-1].cil.NameInner;
    this->dopocetKontrolnihoZnaku(nahradDiakritiku(this->slozBUSEjednoradekAA(DestinationName,LineName)));
    return 1;
}


/* ----------------  nove --------------------*/
void IbisOvladani::slotBytesWritten()
{
    qDebug() << Q_FUNC_INFO;

    qDebug()<<"byty jsou zapsany";
    if(!zasobnikZprav.isEmpty())
    {
        QString aktualniPolozka=zasobnikZprav.first();
        zasobnikZprav.removeFirst();

        odesliAdresu(serial,aktualniPolozka);
        qDebug()<<"v zasobniku zbylo "<<zasobnikZprav.count();
    }
    else
    {
        qDebug()<<"zasobnik je uz prazdny";
        odesilaniBezi=false;
    }
}


void IbisOvladani::odesliAdresu(QSerialPort &port,QString adresa)
{
    qDebug() << Q_FUNC_INFO <<" "<<adresa;
    const QByteArray adresaByteArray = adresa.toLatin1();
    port.write(adresaByteArray);

    if (port.waitForBytesWritten(m_waitTimeout))
    {

        /*
        // read response
        if (serial.waitForReadyRead(currentWaitTimeout))
        {
            QByteArray responseData = serial.readAll();
            while (serial.waitForReadyRead(10))
                responseData += serial.readAll();

            const QString response = QString::fromUtf8(responseData);
*/

    }
    else
    {
        emit timeout(tr("Wait write request timeout %1")
                     .arg(QTime::currentTime().toString()));
    }
    adresa=1;

}




//vstupni funkce
void IbisOvladani::sendToPortNew(QString obsah)
{
    qDebug() << Q_FUNC_INFO;

    QString currentPortName=globalniSeriovyPort;


    qDebug()<<"obsah "<<obsah.length()<<" "<<obsah;

    vypisStringPoBytech(obsah);

    if (currentPortName.isEmpty()) {
        qDebug()<<"No port name specified";
        return;
    }




    zasobnikZprav.push_back(obsah);


    if(odesilaniBezi==false)
    {
        qDebug()<<"menim odesilani bezi na true";
        odesilaniBezi=true;
        slotBytesWritten();
    }
    else
    {
        qDebug()<<"odesilani uz bezelo";
    }



}


void IbisOvladani::startPortu(QSerialPort &port)
{

    qDebug() << Q_FUNC_INFO;
    port.setBaudRate(1200);
    port.setDataBits(QSerialPort::Data7);
    port.setParity(QSerialPort::EvenParity);
    port.setStopBits(QSerialPort::TwoStop);
    port.setFlowControl(QSerialPort::NoFlowControl);

    //serial.close();
    serial.setPortName(globalniSeriovyPort);

    if (!serial.open(QIODevice::ReadWrite))
    {
        qDebug()<<(tr("Can't open %1, error code %2")
                   .arg(serial.portName()).arg(serial.error()));
        return;
    }
}

void IbisOvladani::vypisStringPoBytech(QString vstup)
{
    qDebug() << Q_FUNC_INFO;

    QByteArray poleCharu=vstup.toLatin1();
    for(int i=0;i<poleCharu.size();i++)
    {
        qDebug()<<"i="<<i<<" "<<QString::number(poleCharu[i],16);//<<QString::number(test[i],16);
    }
}
