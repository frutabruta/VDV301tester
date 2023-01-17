#ifndef GOLEMIO_H
#define GOLEMIO_H
//#include <QMainWindow>
#include <QObject>
#include <QtXml>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
//#include <QCoreApplication>

#include "VDV301struktury/prestupmpv.h"
#include "VDV301struktury/prestupmpv.h"
#include "VDV301struktury/linka.h"

#include "VDV301struktury/prestupgolemio.h"

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
    QVector<PrestupGolemio> seznamPrestupuGolemio;



    void naplnVstupDokument(QByteArray vstup);
;
    void stahniMpvXml(int cisloCis, QString Ids);
    QVector<PrestupMPV> vyfiltrujPrestupy(QVector<PrestupMPV> vstupniPrestupy, Linka linka);
    bool jePrestupNaSeznamu(PrestupMPV prestup, QVector<PrestupMPV> seznamPrestupu);

    QVector<PrestupGolemio> parsujDomDokument();
private:
    //instance
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    //promenne
    QByteArray mKlic="";
    QJsonDocument mVstupniJson;

private slots:
    QByteArray requestReceived(QNetworkReply *replyoo);
signals:
    void stazeniHotovo ();
};

#endif // GOLEMIO_H
