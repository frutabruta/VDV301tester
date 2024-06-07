#ifndef GOLEMIO_H
#define GOLEMIO_H
//#include <QMainWindow>
#include <QObject>
#include <QtXml>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
//#include <QCoreApplication>


#include <VDV301publisher/VDV301DataStructures/connectionmpv.h>
#include <VDV301publisher/VDV301DataStructures/line.h>

#include <VDV301publisher/VDV301DataStructures/connectiongolemio.h>

class Golemio: public QObject
{
    Q_OBJECT
public:
    //konstruktor a destruktor
    Golemio(QByteArray klic);
    ~Golemio();


    QByteArray stazenaData="";
  //  QByteArray vystupData="";
   // QVector<PrestupMPV> seznamPrestupuMpv;
    QVector<ConnectionGolemio> seznamPrestupuGolemio;



    void naplnVstupDokument(QByteArray vstup);
;
    void stahniMpvXml(int cisloCis, QString Ids);
    QVector<ConnectionMPV> vyfiltrujPrestupy(QVector<ConnectionMPV> vstupniPrestupy, Line linka);
    bool jePrestupNaSeznamu(ConnectionMPV prestup, QVector<ConnectionMPV> seznamPrestupu);

    QVector<ConnectionGolemio> parsujDomDokument();
    void setKlic(const QByteArray &newKlic);

    void setParametry(const QString &newParametry);

    void setAdresa(const QString &newAdresa);

private:
    //instance
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    //promenne
    QByteArray mKlic="";
    QString mAdresa="http://api.golemio.cz/v2/pid/departureboards/";
    QString mParametry="";
    QJsonDocument mVstupniJson;


private slots:
    QByteArray requestReceived(QNetworkReply *replyoo);
signals:
    void stazeniHotovo ();
};

#endif // GOLEMIO_H
