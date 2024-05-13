#include "ibissender.h"

IbisSender::IbisSender()
{
    connect(&serial, &QSerialPort::bytesWritten ,this,&IbisSender::slotBytesWritten );
    casovac.setInterval(mDelayBetweenMessagesMs);
    casovac.setSingleShot(true);
    connect(&casovac,&QTimer::timeout, this, &IbisSender::slotDelayBetweenMessagesTimeout);
   // startPortu(serial);
}


IbisSender::~IbisSender()
{
    portStop(serial);
}


char IbisSender::checkSumCreate(QString puvodniPrikaz, QString &output)
{
    char zacatecniByte=0x7F;
    char ridiciZnak=0;
    char jeZnak=5;

    char hexridiciznak[2];

    QString prikaz=puvodniPrikaz+'\r';

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
    return zacatecniByte;
}



QString IbisSender::sendTelegram(QString puvodniPrikaz)
{

    qDebug() << Q_FUNC_INFO;
    //puvodniPrikaz=nahradDiakritiku(puvodniPrikaz);
    qDebug()<<puvodniPrikaz;

    QString prikaz =puvodniPrikaz;
    QString output="";


    char checkSum=checkSumCreate(prikaz,output);
    output+=checkSum;
    qDebug()<<"kontrolni soucet je "<<checkSum;
    qDebug()<<"output je:"<<output;
    sendToPortNew(output);
    //sendToPortOld(output);

    return output;

}







QString IbisSender::serialPortName() const
{
    return mSerialPortName;
}

void IbisSender::setSerialPortName(const QString &newSerialPortName)
{
    mSerialPortName = newSerialPortName;
}









/* ----------------  nove --------------------*/
void IbisSender::slotBytesWritten()
{
    qDebug() << Q_FUNC_INFO;
    casovac.start();
}


void IbisSender::writeStringToPort(QSerialPort &port,QString content)
{
    qDebug() << Q_FUNC_INFO <<" length:"<<content.length()<< " "<<content;
    const QByteArray contentByteArray = content.toLatin1();
    port.write(contentByteArray);

    /*
    if (port.waitForBytesWritten(m_waitTimeout))
    {


        // read response
        if (serial.waitForReadyRead(currentWaitTimeout))
        {
            QByteArray responseData = serial.readAll();
            while (serial.waitForReadyRead(10))
                responseData += serial.readAll();

            const QString response = QString::fromUtf8(responseData);


    }
    else
    {
        emit timeout(tr("Wait write request timeout %1")
                     .arg(QTime::currentTime().toString()));
    }
    */

}




//vstupni funkce
void IbisSender::sendToPortNew(QString obsah)
{
    qDebug() << Q_FUNC_INFO;
    
    QString currentPortName=mSerialPortName;


    qDebug()<<"port "<<currentPortName<< " obsah "<<obsah.length()<<" "<<obsah;

    //vypisStringPoBytech(obsah);

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


void IbisSender::slotDelayBetweenMessagesTimeout()
{
    qDebug() << Q_FUNC_INFO;

    qDebug()<<"byty jsou zapsany";
    if(!zasobnikZprav.isEmpty())
    {
        QString aktualniPolozka=zasobnikZprav.first();
        zasobnikZprav.removeFirst();

        writeStringToPort(serial,aktualniPolozka);
        qDebug()<<"v zasobniku zbylo "<<zasobnikZprav.count();
    }
    else
    {
        qDebug()<<"zasobnik je uz prazdny";
        odesilaniBezi=false;
    }
}

int IbisSender::delayBetweenMessagesMs() const
{
    return mDelayBetweenMessagesMs;
}

void IbisSender::setDelayBetweenMessagesMs(int newDelayBetweenMessagesMs)
{
    mDelayBetweenMessagesMs = newDelayBetweenMessagesMs;
    casovac.setInterval(mDelayBetweenMessagesMs);
}



void IbisSender::start()
{
    startPortu( serial );
}


void IbisSender::stop()
{
    portStop(   serial);
}

void IbisSender::startPortu(QSerialPort &port)
{

    qDebug() << Q_FUNC_INFO;
    port.setBaudRate(1200);
    port.setDataBits(QSerialPort::Data7);
    port.setParity(QSerialPort::EvenParity);
    port.setStopBits(QSerialPort::TwoStop);
    port.setFlowControl(QSerialPort::NoFlowControl);

    //serial.close();
    serial.setPortName(mSerialPortName);

    if (!serial.open(QIODevice::ReadWrite))
    {
        qDebug()<<(tr("Can't open %1, error code %2")
                   .arg(serial.portName()).arg(serial.error()));
        return;
    }
}


void IbisSender::portStop(QSerialPort &port)
{
   port.close();
    odesilaniBezi=false;
}

void IbisSender::vypisStringPoBytech(QString vstup)
{
    qDebug() << Q_FUNC_INFO;

    QByteArray poleCharu=vstup.toLatin1();
    for(int i=0;i<poleCharu.size();i++)
    {
        qDebug()<<"i="<<i<<" "<<QString::number(poleCharu[i],16);//<<QString::number(test[i],16);
    }
}
