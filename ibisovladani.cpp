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


void IbisOvladani::dopocetCelni (QString puvodniPrikaz)
{
    inicializujSeriovyPort(globalniSeriovyPort);
    if (serial.isOpen() && serial.isWritable())
    {
        qDebug() << "Serial is open";
        //  qDebug()<< obsah;

        //    QByteArray output;
        //      QByteArray input;


        //        output = obsah.toLatin1();
        //output="50 0 0";

        // serial.write(output);
        //serial.write("\n");
        // serial.waitForBytesWritten();

        //   return 1;


    }
    else
    {
        qDebug() << "Nepovedlo se otevrit seriovy port";

    }
    qDebug()<<"IbisOvladani::dopocetCelni";
    qDebug()<<puvodniPrikaz;

    QString prikaz = "";
    QString output="";
    char zacatecniByte=0x7F;
    //QString ridiciZnak ="";
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
            //zacatecniByte=zacatecniByte^atoi(hexridiciznak);
            break;

        case 3:
            //hexridiciznak[2]=prikaz[k].toLatin1();
            jeZnak++;
            break;
        case 4:
            ridiciZnak=int(strtol(hexridiciznak,NULL,16));
            zacatecniByte=zacatecniByte^ridiciZnak;

            // zacatecniByte=zacatecniByte^int(strtol(hexridiciznak,0,16) );
            output+=ridiciZnak;

            //  char(strtol(hexridiciznak,NULL,16)));

            //qDebug()<<int(strtol(hexridiciznak,NULL,16));

            hexridiciznak[0]=0;
            hexridiciznak[1]=0;
            //hexridiciznak[2]=0;
            jeZnak++;
            break;
        case 5:
            zacatecniByte=zacatecniByte^prikaz[k].toLatin1();
            output+=prikaz[k];
            //qDebug()<<QString::number(prikaz[k].toLatin1(),16);
            //swSer.print(prikaz[k]);

            break;
        }

    }
    //swSer.print(zacatecniByte);

    // qDebug()<<QString::number(zacatecniByte,16);
    output+=zacatecniByte;
    serial.write(output.toLatin1());
    qDebug()<<serial.error();
    serial.waitForBytesWritten();
    qDebug()<<output;
    qDebug()<<"hexdump";
    for (int i=0;i<output.length();i++)
    {
        qDebug()<<QString::number(output[i].toLatin1(),16)<<" "<<output[i];

    }
    qDebug()<<output.toLatin1();
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
    serial.close();
    serial.setPortName(port);

    serial.setBaudRate(QSerialPort::Baud1200 );
    serial.setDataBits(QSerialPort::Data7);
    serial.setParity(QSerialPort::EvenParity);
    serial.setStopBits(QSerialPort::TwoStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.open(QIODevice::ReadWrite);

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
