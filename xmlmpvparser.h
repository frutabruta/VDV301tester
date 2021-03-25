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
    QDomDocument connections1_0( QVector<prestupMPV> lokPrestupy);
    QDomDocument prestupyXmlDokumentVystup1_0;
    QDomDocument prestupyXmlDokumentVystup2_2CZ1_0;
    QVector<prestupMPV> parsujDomDokument();
    //QByteArray vlozitDoXml="";
    QVector<prestupMPV> seznamPrestupu;
    void StahniMpvXml(int cisloCis, QString Ids);
    ~XmlMpvParser();

    QDomDocument connections2_2CZ1_0(QVector<prestupMPV> lokPrestupy);
private slots:
    QByteArray requestReceived(QNetworkReply *replyoo);
signals:
    void stazeniHotovo ();
};

#endif // XMLMPVPARSER_H
