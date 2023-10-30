#ifndef XMLMPVPARSER_H
#define XMLMPVPARSER_H
//#include <QMainWindow>
#include <QObject>
#include <QtXml>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
//#include <QCoreApplication>


#include "VDV301DataStructures/connectionmpv.h"
#include "VDV301DataStructures/line.h"

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
    QVector<ConnectionMPV> seznamPrestupu;


    void naplnVstupDokument(QByteArray vstup);
    QVector<ConnectionMPV> parsujDomDokument();
    void stahniMpvXml(int cisloCis, QString Ids);
    QVector<ConnectionMPV> vyfiltrujPrestupy(QVector<ConnectionMPV> vstupniPrestupy, Line linka);
    bool jePrestupNaSeznamu(ConnectionMPV prestup, QVector<ConnectionMPV> seznamPrestupu);

private slots:
    QByteArray requestReceived(QNetworkReply *replyoo);
signals:
    void stazeniHotovo ();
};

#endif // XMLMPVPARSER_H
