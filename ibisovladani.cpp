#include "ibisovladani.h"
#include <QDebug>
#include <QMainWindow>
#include <QCoreApplication>

IbisOvladani::IbisOvladani()
{

}




int IbisOvladani::kontrolniZnak(QString)
{
    int kontrolniZnak=0;

    return kontrolniZnak;
}






/*


IBISSW::IBISSW()
{
    swSer.begin(1200, SWSERIAL_7O2,11,12,false);
    //swSer.begin(1200, SERIAL_7E2);
    pinMode(12,OUTPUT);
    //swSer.flush();
    //swSer.enableTx(true);
}

*/



void IbisOvladani::dopocetCelni (QString puvodniPrikaz)
{
    qDebug()<<"IbisOvladani::dopocetCelni";
    inicializujSeriovyPort(globalniSeriovyPort);
    QString prikaz = "";
    QString output="";
    char zacatecniByte=0x7F;
    QString ridiciZnak ="";
    char jeZnak=5;

    char hexridiciznak[3];
    //char hex1=0;
    //char hex2=0;

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
            hexridiciznak[0]=prikaz[k].toLatin1();
            jeZnak++;
            break;

        case 2:
            hexridiciznak[1]=prikaz[k].toLatin1();
            jeZnak++;
            //zacatecniByte=zacatecniByte^atoi(hexridiciznak);
            break;

        case 3:
            hexridiciznak[2]=prikaz[k].toLatin1();
            jeZnak++;
            break;
        case 4:
            zacatecniByte=zacatecniByte^int(strtol(hexridiciznak,NULL,16));
           // zacatecniByte=zacatecniByte^int(strtol(hexridiciznak,0,16) );
            output+=hexridiciznak;

                      //  char(strtol(hexridiciznak,NULL,16)));

            qDebug()<<int(strtol(hexridiciznak,NULL,16));

            hexridiciznak[0]=0;
            hexridiciznak[1]=0;
            hexridiciznak[2]=0;
            jeZnak++;
            break;
        case 5:
            zacatecniByte=zacatecniByte^prikaz[k].toLatin1();
            output+=prikaz[k];
            qDebug()<<QString::number(prikaz[k].toLatin1(),16);
            //swSer.print(prikaz[k]);

            break;
        }

    }
    //swSer.print(zacatecniByte);

    qDebug()<<QString::number(zacatecniByte,16);
    output+=zacatecniByte;
    serial.write(output.toLatin1());
    qDebug()<<output;

    serial.close();
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

void IbisOvladani::nastavPort(QString nazev)
{

}




int IbisOvladani::inicializujSeriovyPort(QString port)
{
    qDebug()<<"IbisOvladani::inicializujSeriovyPort";
    //serial.close();
    serial.setPortName(port);
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(QSerialPort::Baud1200);
    serial.setDataBits(QSerialPort::Data7);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    qDebug()<<"konecInicializace";
    return 1;

}


int IbisOvladani::zapisDoSeriovehoPortu(QString obsah, QString port)
{


    if (serial.isOpen() && serial.isWritable())
    {
        qDebug() << "Serial is open";
        qDebug()<< obsah;

        QByteArray output;
        QByteArray input;


        output = obsah.toLatin1();
        //output="50 0 0";

        serial.write(output);
        serial.write("\n");
        serial.waitForBytesWritten();

        return 1;


    }
    else
    {
        qDebug() << "Nepovedlo se otevrit seriovy port";

    }
    return 0;
}
