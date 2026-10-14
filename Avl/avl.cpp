#include "avl.h"

Q_LOGGING_CATEGORY(avlLog, "Avl")

Avl::Avl(int port): avlWebsocketSender(QUrl("ws://127.0.0.1:"+QString::number(port)),this)
{
    timerSendMessage.setInterval(mTimerInterval);

    connect(&timerSendMessage,&QTimer::timeout,this,&Avl::slotTimerTimout);
}

void Avl::dumpValues()
{
    qCDebug(avlLog)<<"turnus: "<<mTurnus;
    qCDebug(avlLog)<<"line: "<<mLine;
    qCDebug(avlLog)<<"evc:" <<mEvc;
    qCDebug(avlLog)<<"lat: "<<mLat;
    qCDebug(avlLog)<<"lng: "<<mLng;
    qCDebug(avlLog)<<"akt: "<<mAkt;
    qCDebug(avlLog)<<"takt: "<<mTakt;
    qCDebug(avlLog)<<"konc: "<<mKonc;
    qCDebug(avlLog)<<"tjr: "<<mTjr;
    qCDebug(avlLog)<<"tm: "<<mTm;
    qCDebug(avlLog)<<"events: "<<mEvents;
}

QString Avl::generateJsonMessage()
{
    qCDebug(avlLog)<<Q_FUNC_INFO;

    QJsonObject gnssData;
    gnssData["turnus"] = mTurnus;
    gnssData["line"] = mLine;
    gnssData["evc"] = mEvc;
    gnssData["np"] = "ano";
    gnssData["lat"] = mLat;
    gnssData["lng"] = mLng;
    gnssData["akt"] = mAkt;
    gnssData["takt"] = mTakt;
    gnssData["konc"] = mKonc;
    gnssData["tjr"] = mTjr;
    gnssData["pkt"] = mPkt;
    gnssData["tm"] = mTm;
    gnssData["events"] = mEvents;


    QJsonDocument doc(gnssData);
    QString jsonString = doc.toJson(QJsonDocument::Compact);

    qCDebug(avlLog).noquote()<<jsonString;
    return jsonString;
}

void Avl::slotUpdatePosition(QPointF input)
{
    qCDebug(avlLog)<<Q_FUNC_INFO;
    mLat=input.y();
    mLng=input.x();
    qCDebug(avlLog).noquote()<<input;
}

QString Avl::turnus() const
{
    return mTurnus;
}

void Avl::setTurnus(const QString &newTurnus)
{

    mTurnus = newTurnus;
}

void Avl::setTurnus(int rootLine, int order)
{

    mTurnus = QString::number(rootLine)+"/"+QString::number(order);
}



void Avl::triggerUpdate(QString event)
{
    mEvents=event;
    mTm=qTimeToMpvDatetime(QTime::currentTime());

    avlWebsocketSender.setData(generateJsonMessage());
    dumpValues();
}




int Avl::line() const
{
    return mLine;
}

void Avl::setLine(int newLine)
{
    mLine = newLine;
}

int Avl::evc() const
{
    return mEvc;
}

void Avl::setEvc(int newEvc)
{
    mEvc = newEvc;
}

void Avl::setCoordinates(float newLat, float newLng)
{
    mLat=newLat;
    mLng=newLng;
}

QString Avl::akt() const
{
    return mAkt;
}

void Avl::setAkt(const QString &newAkt)
{
    mAkt = newAkt;
}

QString Avl::takt() const
{
    return mTakt;
}

void Avl::setTakt(const QString &newTakt)
{
    mTakt = newTakt;
}

QString Avl::konc() const
{
    return mKonc;
}

void Avl::setKonc(const QString &newKonc)
{
    mKonc = newKonc;
}

QString Avl::tjr() const
{
    return mTjr;
}

void Avl::setTjr(const QString &newTjr)
{
    mTjr = newTjr;
}

QString Avl::tm() const
{
    return mTm;
}

void Avl::setTm(const QString &newTm)
{
    mTm = newTm;
}

QString Avl::events() const
{
    return mEvents;
}

void Avl::setEvents(const QString &newEvents)
{
    mEvents = newEvents;
}

void Avl::timerStart()
{
    qCDebug(avlLog)<<Q_FUNC_INFO;
    timerSendMessage.setInterval(mTimerInterval);
    timerSendMessage.start();
}


void Avl::timerStop()
{
    timerSendMessage.stop();
}

QString Avl::qTimeToMpvDatetime(QTime input)
{
    QDateTime output;
    output=QDateTime::currentDateTime();
    output.setTime(input);
    return output.toUTC().toString("yyyy-MM-ddThh:mm:ss");
}

void Avl::slotTimerTimout()
{
    triggerUpdate("O");;
}


