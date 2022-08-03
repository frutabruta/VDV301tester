#ifndef XMLMPVPARSER_H
#define XMLMPVPARSER_H
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

class XmlMpvParser: public QObject
{
    Q_OBJECT
public:
    XmlMpvParser();
    ~XmlMpvParser();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //konstanty
    QDomDocument vstupniDomDokument;
    QByteArray stazenaData="";
    QByteArray vystupData="";
    QVector<PrestupMPV> seznamPrestupu;


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

#endif // XMLMPVPARSER_H
