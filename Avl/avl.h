#ifndef AVL_H
#define AVL_H

#include "avlwebsocketsender.h"

#include <QLoggingCategory>
#include <QDomDocument>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>
#include <QStringLiteral>
#include <QTimer>
#include <QPointF>

class Avl: public QObject
{
    Q_OBJECT
public:
    Avl(int port);

    AvlWebsocketSender avlWebsocketSender;

    QString turnus() const;
    void setTurnus(const QString &newTurnus);

    void setTurnus(int rootLine, int order);

    int line() const;
    void setLine(int newLine);

    int evc() const;
    void setEvc(int newEvc);

    void setCoordinates(float newLat, float newLng);
    QString akt() const;
    void setAkt(const QString &newAkt);

    QString takt() const;
    void setTakt(const QString &newTakt);

    QString konc() const;
    void setKonc(const QString &newKonc);

    QString tjr() const;
    void setTjr(const QString &newTjr);

    QString tm() const;
    void setTm(const QString &newTm);

    QString events() const;
    void setEvents(const QString &newEvents);

    QString generateJsonMessage();
    void dumpValues();
    void triggerUpdate(QString event);

    QTimer timerSendMessage;
    QString qTimeToMpvDatetime(QTime input);
    void timerStart();
    void timerStop();
public slots:
    void slotUpdatePosition(QPointF input);
private slots:
    void slotTimerTimout();
private:
    QString mTurnus="";
    int mLine=0;
    int mEvc=0;
    float mLat=0.0;
    float mLng=0.0;
    QString mAkt="";
    QString mTakt="";
    QString mKonc="";
    QString mTjr="";
    QString mTm="";
    QString mEvents="";


    int mTimerInterval=5000;


    int mPkt=333;

};

#endif // AVL_H
