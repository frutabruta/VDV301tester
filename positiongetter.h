#ifndef POSITIONGETTER_H
#define POSITIONGETTER_H

#include <QObject>
#include <QLocationPermission>
#include <QCoreApplication>
#include <QGeoPositionInfoSource>
#include <QNmeaPositionInfoSource>
#include <QPointF>
#include <QSerialPort>

enum class PositionSourceType
    {
        Default,
        NmeaSerial
    };

class PositionGetter : public QObject
{
    Q_OBJECT
public:
    PositionGetter();

    QGeoPositionInfoSource *m_source = nullptr;
    QSerialPort m_serialPort;

    void setupPositioning();

    void startDefaultSource();

    void slotPortChanged(const QString &portName);
    void setSource(const QString &sourceId);
public slots:

private slots:
    void slotPositionUpdated(const QGeoPositionInfo &info);
    void slotErrorOccurred(QGeoPositionInfoSource::Error error);

signals:
    void signalStringData(QString message);
    void signalStringError(QString message);
    void signalPositionUpdate(QPointF coordinates);
};

#endif // POSITIONGETTER_H
