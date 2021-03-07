#ifndef XMLMPVPARSER_H
#define XMLMPVPARSER_H
#include <QMainWindow>
#include <QObject>
#include <QtXml>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "prestupmpv.h"

class XmlMpvParser: public QObject
{
    Q_OBJECT
public:
    XmlMpvParser();
    QDomDocument vstupniDomDokument;
    QByteArray stazenaData="";
    QByteArray vystupData="";
    void naplnVstupDokument(QByteArray vstup);
    QDomDocument VytvorVystupniDokument(int max, QDomDocument xmlko);
    QDomDocument prestupyXmlDokumentVystup;
    int parsujDomDokument();
    //QByteArray vlozitDoXml="";
    prestupMPV mujPrestup[40];
    void StahniMpvXml(int cisloCis, QString Ids);
    ~XmlMpvParser();
private slots:
    QByteArray requestReceived(QNetworkReply *replyoo);
signals:
    void stazeniHotovo ();
};

#endif // XMLMPVPARSER_H
