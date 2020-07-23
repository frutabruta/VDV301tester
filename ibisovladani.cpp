#include "ibisovladani.h"
#include <QDebug>
#include <QMainWindow>
#include <QCoreApplication>
#include "VDV301_Display/seznamzastavek.h"

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


QVector<SeznamZastavek> IbisOvladani::vytvorNacestne(QVector<SeznamZastavek> vstup, int index)
{
    QVector <SeznamZastavek> vystup;
    vystup.clear();
    if (index>vstup.count())
    {
        index=vstup.count();
    }


    for (int i = index;i< vstup.count() ; i++)
    {
        if(vstup[i].nacestna==1)
        {
         vystup.push_back(vstup[i]);
        }
    }


    return vystup;

}

QString IbisOvladani::slozeniTextuFront(QString LineName,QString DestinationName)
{
    QString vystup="";
    vystup+="aA1 ";
    vystup+="<1B><5A><1B>p<2D><0C>";
    vystup+=LineName;
    vystup+="<1B>c<1B><55><1B>l<2E>";
    vystup+=DestinationName;
    //vystup+="";
    return vystup;
}
int IbisOvladani::odesliFrontKomplet(QVector<SeznamZastavek>zastavky,int index)
{
    QString LineName=zastavky[index].LineName;
    QString DestinationName=zastavky.last().NameLcd;
    dopocetCelni(slozeniTextuFront(LineName,DestinationName));
    return 1;
}


QString IbisOvladani::slozeniTextuSide(QVector<SeznamZastavek> nacestne,QString LineName,QString DestinationName)
{
    QString vystup="";
    vystup+="aA2 ";
    vystup+="<1B><5A><1B>p<2D><0C>";
    vystup+=LineName;
    vystup+="<1B>c<1B><53><1B>l<2E>"; //y0
    vystup+=DestinationName;
    for (int i =0;i<nacestne.count();i++)
    {
        vystup+="<1B><F0>"; //y10
        vystup+=nacestne[i].NameSide;
        vystup+="<0A>";
    }

    return vystup;
}

int IbisOvladani::odesliSideKomplet(QVector <SeznamZastavek> zastavky,int index)
{

    QString LineName=zastavky[index].LineName;
    QString DestinationName=zastavky.last().NameLcd;
    this->dopocetCelni(slozeniTextuSide(vytvorNacestne(zastavky,index),LineName,DestinationName));

    return 1;
}


int IbisOvladani::odesliInnerKomplet(QVector <SeznamZastavek> zastavky,int index)
{
    QString LineName=zastavky[index].LineName;
    QString DestinationName=zastavky.last().NameLcd;
    this->dopocetCelni( slozeniTextuInnerL(LineName));
    this->dopocetCelni(slozeniTextuInnerV(zastavky[index].NameLcd));
    this->dopocetCelni(slozeniTextuInnerZA(DestinationName));
    this->dopocetCelni(slozeniTextuInnerZN(vytvorNacestne(zastavky,index)));
    return 1;
}

QString IbisOvladani::slozeniTextuInnerL(QString LineName)
{
    QString vystup="";
    vystup+="l";
    vystup+=LineName;
    return vystup;
}
QString IbisOvladani::slozeniTextuInnerZA(QString DestinationName)
{
    QString vystup="";
    vystup+="zA ";
    vystup+=DestinationName;
    return vystup;
}
QString IbisOvladani::slozeniTextuInnerZN(QVector<SeznamZastavek> nacestne)
{
    QString vystup="zN ";
    for (int i=0;i<nacestne.count();i++)
    {
        vystup+=nacestne[i].NameLcd;
        vystup+="-";
    }

    return vystup;
}
QString IbisOvladani::slozeniTextuInnerV(QString StopName)
{
    QString vystup="";
    vystup+="v ";
    vystup+=StopName;
    return vystup;
}


