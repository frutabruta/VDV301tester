#include "ibisovladani.h"
#include <QDebug>
#include <QMainWindow>
#include <QCoreApplication>
#include "VDV301struktury/zastavka.h"

IbisOvladani::IbisOvladani()
{

}









QString IbisOvladani::nahradDiakritiku(QString vstup)
{
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


QString IbisOvladani::dopocetCelni (QString puvodniPrikaz)
{
    puvodniPrikaz=nahradDiakritiku(puvodniPrikaz);
    qDebug()<<"IbisOvladani::dopocetCelni";
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
    odesliDoPortu(output);

    return output;

}


void IbisOvladani::smazPanely ()
{
    qDebug()<<"IbisOvladani::smazPanely";
    QString prikaz="";
    prikaz="zA ";
    dopocetCelni(prikaz);

    prikaz="zN ";
    dopocetCelni(prikaz);

    prikaz="zI2 ";
    dopocetCelni(prikaz);

    prikaz="l000";
    dopocetCelni(prikaz);
}

int IbisOvladani::odesliDoPortu(QString vstup)
{
    qDebug()<<"IbisOvladani::odesliDoPortu";
    bool currentPortNameChanged = false;
    QString portName="ttyUSB0";
    QString currentPortName;
    if (currentPortName != portName) {
        currentPortName = portName;
        currentPortNameChanged = true;
    }

    int waitTimeout=1000;
    int currentWaitTimeout = waitTimeout;
    QString request=vstup;
    QString currentRequest = request;
    QSerialPort serial;

    if (currentPortName.isEmpty()) {
        //emit error(tr("No port name specified"));
        return 0;
    }
    int quit=0;
    while (!quit) {
        //![6] //! [7]
        if (currentPortNameChanged) {
            serial.close();
            serial.setPortName(currentPortName);
            serial.open(QIODevice::ReadWrite);

            serial.setBaudRate(1200);
            serial.setDataBits(QSerialPort::Data7);
            serial.setParity(QSerialPort::EvenParity);
            serial.setStopBits(QSerialPort::TwoStop);
            serial.setFlowControl(QSerialPort::NoFlowControl);


        }
        //! [7] //! [8]
        // write request
        QByteArray requestData = currentRequest.toLocal8Bit();
        serial.write(requestData);
        if (serial.waitForBytesWritten(waitTimeout)) {
            //! [8] //! [10]
            // read response
            if (serial.waitForReadyRead(currentWaitTimeout)) {
                QByteArray responseData = serial.readAll();
                while (serial.waitForReadyRead(10))
                    responseData += serial.readAll();

                QString response(responseData);
                //! [12]
                //emit this->response(response);
                //! [10] //! [11] //! [12]
            } else {
                //emit timeout(tr("Wait read response timeout %1")    .arg(QTime::currentTime().toString()));
            }
            //! [9] //! [11]
        } else {
            // emit timeout(tr("Wait write request timeout %1")                        .arg(QTime::currentTime().toString()));
        }
        if (currentPortName != portName) {
            currentPortName = portName;
            currentPortNameChanged = true;
        } else {
            currentPortNameChanged = false;
        }
        currentWaitTimeout = waitTimeout;
        currentRequest = request;
        quit=1;
    }
    return 1;
}


QVector<Zastavka> IbisOvladani::vytvorNacestne(QVector<ZastavkaCil> vstup, int index)
{
    qDebug()<<"IbisOvladani::vytvorNacestne";
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
    qDebug()<<"IbisOvladani::slozeniTextuFront";
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
    qDebug()<<"IbisOvladani::odesliFrontKomplet";
    QString LineName=zastavky[index].linka.LineName;
    QString DestinationName= zastavky[index].cil.NameFront;
       // zastavky.last().NameFront;
    dopocetCelni(slozeniTextuFront(LineName,DestinationName));
    return 1;
}


QString IbisOvladani::slozeniTextuRear(QString LineName)
{
    qDebug()<<"IbisOvladani::slozeniTextuRear";
    QString vystup="";
    // funkcni vystup+="aA1 <1B>b<1B>l<12><0A><1B><22><1B>l<12><1B>p<2D><1B><58>";
    vystup+="aA4 <1B>b<1B><58><1B><22>"; //ME kopie
    //vystup+="aA1 <1B>b<1B>l<12><1B><22><1B><1B>p<2D><1B><58>";
    vystup+=LineName;

    return vystup;
}

int IbisOvladani::odesliRearKomplet(QVector<ZastavkaCil>zastavky,int index)
{
    qDebug()<<"IbisOvladani::odesliRearKomplet";
    QString LineName=zastavky[index].linka.LineName;
    //QString DestinationName= zastavky.last().NameFront;
    QString DestinationName= zastavky.at(index).cil.NameFront;
    dopocetCelni(slozeniTextuRear(LineName));
    return 1;
}


QString IbisOvladani::slozeniTextuSideAA(QVector<Zastavka> nacestne,QString LineName,QString DestinationName)
{
    qDebug()<<"IbisOvladani::slozeniTextuSide";
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
    qDebug()<<"IbisOvladani::slozeniTextuSide";
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
    qDebug()<<"IbisOvladani::odesliSideKomplet";
    QString LineName=zastavky[index].linka.LineName;
    //QString DestinationName=zastavky.last().NameSide;
    QString DestinationName=zastavky.at(index).cil.NameSide;
    this->dopocetCelni(slozeniTextuSideAA(vytvorNacestne(zastavky,index),LineName,DestinationName));
    this->dopocetCelni(slozeniTextuSideZN(vytvorNacestne(zastavky,index)));

    return 1;
}


int IbisOvladani::odesliInnerKomplet(QVector <ZastavkaCil> zastavky,int index)
{
    qDebug()<<"IbisOvladani::odesliInnerKomplet";
    QString LineName=zastavky[index].linka.LineName;
    QString DestinationName=zastavky[zastavky.count()-1].cil.NameInner;
    this->dopocetCelni(slozeniTextuInnerL(LineName));
    this->dopocetCelni(slozeniTextuInnerV(zastavky[index].zastavka.NameInner));
    this->dopocetCelni(slozeniTextuInnerZA(DestinationName));
    this->dopocetCelni(slozeniTextuInnerZN(vytvorNacestne(zastavky,index)));
    return 1;
}

QString IbisOvladani::slozeniTextuInnerL(QString LineName)
{
    qDebug()<<"IbisOvladani::slozeniTextuInnerL";
    QString vystup="";
    vystup+="l";
    vystup+=LineName;
    return vystup;
}

QString IbisOvladani::slozeniTextuInnerZA(QString DestinationName)
{
    qDebug()<<"IbisOvladani::slozeniTextuInnerZA";
    QString vystup="";
    vystup+="zA ";
    vystup+=DestinationName;
    return vystup;
}
QString IbisOvladani::slozeniTextuInnerZN(QVector<Zastavka> nacestne)
{
    qDebug()<<"IbisOvladani::slozeniTextuInnerZN";
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
    qDebug()<<"IbisOvladani::slozeniTextuInnerV";
    QString vystup="";
    vystup+="v ";
    vystup+=StopName;
    return vystup;
}


QString IbisOvladani::slozeniTextuJKZr1(QVector<Zastavka> nacestne,QString LineName)
{
    qDebug()<<"IbisOvladani::slozeniTextuJKZr1";
    QString vystup="aA<3B>3";
    //vystup+="<1B>p<26><1B><53><1B><22>"; BUSE?
    vystup+="<1B>t<11>";
   // vystup+=LineName;
   // vystup+="<0C><1B>l<29><1B>p<0E><17><1B>z<10><1B>t<11><1B><53><1B><22>"; BUSE?
    //vystup+="<0C><1B>l<29><1B>p<0E><17><1B>z<10><1B>t<11><1B><53><1B><22>";
    vystup+="přes zastávky/via: ";
    int i=0;
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
    qDebug()<<"IbisOvladani::slozeniTextuJKZr2";
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
    qDebug()<<"IbisOvladani::odesliInnerKomplet";
    QString LineName=zastavky[index].linka.LineName;
    QString DestinationName=zastavky[zastavky.count()-1].cil.NameInner;

    this->dopocetCelni(slozeniTextuJKZr1(vytvorNacestne( zastavky,index),LineName));
    this->dopocetCelni(slozeniTextuJKZr2(DestinationName,LineName));
    this->dopocetCelni("l"+LineName);
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
    QString vystup="aA<3B>2 <3E>";
    //vystup+="<0C><1B>l<29><1B>p<0E><17><1B>z<10><1B>t<11><1B><53><1B><22>";
    vystup+=this->nahradZobacek( DestinationName);
    return vystup;
}

int IbisOvladani::odeslikompletBUSEjednoradekAA(QVector<ZastavkaCil> zastavky,int index)
{
    QString LineName=zastavky[index].linka.LineName;
    //QString DestinationName=zastavky[zastavky.count()-1].NameInner;
    QString DestinationName=zastavky[zastavky.count()-1].cil.NameInner;
    this->dopocetCelni(nahradDiakritiku(this->slozBUSEjednoradekAA(DestinationName,LineName)));
    return 1;
}
