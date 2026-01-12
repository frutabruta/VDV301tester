#include "avl.h"

Q_LOGGING_CATEGORY(avlLog, "Avl")

Avl::Avl(int port): avlWebsocketSender(QUrl("ws://127.0.0.1:"+QString::number(port)),this)
{

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

void Avl::dumpValues()
{
    qInfo()<<"turnus: "<<mTurnus;
    qInfo()<<"line: "<<mLine;
    qInfo()<<"evc:" <<mEvc;
    qInfo()<<"lat: "<<mLat;
    qInfo()<<"lng: "<<mLng;
    qInfo()<<"akt: "<<mAkt;
    qInfo()<<"takt: "<<mTakt;
    qInfo()<<"konc: "<<mKonc;
    qInfo()<<"tjr: "<<mTjr;
    qInfo()<<"tm: "<<mTm;
    qInfo()<<"events: "<<mEvents;
}

void Avl::triggerUpdate(QString event)
{
    mEvents=event;

    avlWebsocketSender.setData(generateJsonMessage());
    dumpValues();
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


