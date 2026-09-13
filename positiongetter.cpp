#include "positiongetter.h"

PositionGetter::PositionGetter()
{
    emit signalStringError("Available position sources:"+ QGeoPositionInfoSource::availableSources().join(" "));


    QLocationPermission perm;
    perm.setAccuracy(QLocationPermission::Precise);
    perm.setAvailability(QLocationPermission::WhenInUse);

    switch (qApp->checkPermission(perm)) {
    case Qt::PermissionStatus::Granted:
        setupPositioning();
        break;
    case Qt::PermissionStatus::Undetermined:
        qApp->requestPermission(perm, this, [this](const QPermission &p) {
            if (p.status() == Qt::PermissionStatus::Granted)
                setupPositioning();
            else
                qDebug()<<"Status: location permission denied";
        });
        break;
    case Qt::PermissionStatus::Denied:
        qDebug()<<"Status: location permission denied by OS/policy";
        break;
    }

}


void PositionGetter::setupPositioning()
{
    emit signalStringError("Available position sources:"+ QGeoPositionInfoSource::availableSources().join(" "));


    m_source = QGeoPositionInfoSource::createDefaultSource(this);

    if (!m_source) {
        emit signalStringError("Status: no default position source (winrt plugin likely didn't load with MinGW — check Device Manager for a GPS/NMEA COM port instead)");
        return;
    }

    emit signalStringError(QString("Status: using \"%1\" source").arg(m_source->sourceName()));

    connect(m_source, &QGeoPositionInfoSource::positionUpdated,
            this, &PositionGetter::slotPositionUpdated);
    connect(m_source, &QGeoPositionInfoSource::errorOccurred,
            this, &PositionGetter::slotErrorOccurred);

    m_source->setUpdateInterval(1000);
    m_source->startUpdates();
}


void PositionGetter::slotErrorOccurred(QGeoPositionInfoSource::Error error)
{
    emit signalStringError(QString("Status: positioning error (%1)").arg(int(error)));

}




void PositionGetter::slotPositionUpdated(const QGeoPositionInfo &info)
{
    const QGeoCoordinate c = info.coordinate();
    emit signalStringData(QString("Lat/Lon: %1, %2  \n(updated %3) \n source %4").arg(
                              QString::number(c.latitude()),
                              QString::number(c.longitude()),
                              info.timestamp().toLocalTime().toString(Qt::ISODate),
                              m_source->sourceName()));

    emit signalPositionUpdate(QPointF(c.longitude(),c.latitude()));

}

void PositionGetter::setSource(const QString &sourceId)
{
    if (m_source)
    {
        m_source->stopUpdates();
        delete m_source;
        m_source = nullptr;
    }

    /*
    if (m_serialPort)
    {
        m_serialPort->close();
        delete m_serialPort;
        m_serialPort = nullptr;
    } */

    if (sourceId == "__DEFAULT__")
    {
        m_source = QGeoPositionInfoSource::createDefaultSource(this);

        if (!m_source)
        {
            emit signalStringError("No default source available");
            return;
        }
    }
    else
    {
        //m_serialPort = new QSerialPort(this);

        /*
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

        */




        m_serialPort.setPortName(sourceId);
        m_serialPort.setBaudRate(QSerialPort::Baud9600);

        if(!m_serialPort.isOpen())
        {
            if (!m_serialPort.open(QIODevice::ReadOnly))
            {
                emit signalStringError(
                    QString("Cannot open %1").arg(sourceId));
                return;
            }
        }
        else
        {
            emit signalStringError(
                QString("Port already opened %1").arg(sourceId));
        }



        QNmeaPositionInfoSource *nmeaSource =  new QNmeaPositionInfoSource(QNmeaPositionInfoSource::RealTimeMode, this);

        nmeaSource->setDevice(&m_serialPort);
        nmeaSource->setObjectName("serial");

        m_source = nmeaSource;
    }

    connect(m_source,&QGeoPositionInfoSource::positionUpdated,this,&PositionGetter::slotPositionUpdated);
    connect(m_source,&QGeoPositionInfoSource::errorOccurred,this,&PositionGetter::slotErrorOccurred);

    m_source->startUpdates();
}