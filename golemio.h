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

class Golemio: public QObject
{
    Q_OBJECT
public:
    Golemio(QByteArray klic);
    ~Golemio();
     QByteArray mKlic="";
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //konstanty
    QDomDocument vstupniDomDokument;
    QJsonDocument vstupniJson;
    QByteArray stazenaData="";
    QByteArray vystupData="";
    QVector<PrestupMPV> seznamPrestupu;
    int tabulka[15];


    void naplnVstupDokument(QByteArray vstup);
    QVector<PrestupMPV> parsujDomDokument();
    void stahniMpvXml(int cisloCis, QString Ids);
    QVector<PrestupMPV> vyfiltrujPrestupy(QVector<PrestupMPV> vstupniPrestupy, Linka linka);
    bool jePrestupNaSeznamu(PrestupMPV prestup, QVector<PrestupMPV> seznamPrestupu);

private slots:
    QByteArray requestReceived(QNetworkReply *replyoo);
signals:
    void stazeniHotovo ();
};

#endif // GOLEMIO_H
