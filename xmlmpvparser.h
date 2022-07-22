#ifndef XMLMPVPARSER_H
#define XMLMPVPARSER_H
#include <QMainWindow>
#include <QObject>
#include <QtXml>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "prestupmpv.h"
#include "VDV301struktury/linka.h"

class XmlMpvParser: public QObject
{
    Q_OBJECT
public:
    XmlMpvParser();
    //konstanty
    bool filtrovatPrestupy=true;

    QDomDocument vstupniDomDokument;
    QByteArray stazenaData="";
    QByteArray vystupData="";
    void naplnVstupDokument(QByteArray vstup);
    QDomDocument connections1_0( QVector<PrestupMPV> lokPrestupy);
    //QDomDocument prestupyXmlDokumentVystup1_0;
   // QDomDocument prestupyXmlDokumentVystup2_2CZ1_0;
    QVector<PrestupMPV> parsujDomDokument();
    //QByteArray vlozitDoXml="";
    QVector<PrestupMPV> seznamPrestupu;
    void stahniMpvXml(int cisloCis, QString Ids);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    ~XmlMpvParser();

    QDomDocument connections2_2CZ1_0(QVector<PrestupMPV> lokPrestupy);
    QVector<PrestupMPV> vyfiltrujPrestupy(QVector<PrestupMPV> vstupniPrestupy, Linka linka);
    bool jePrestupNaSeznamu(PrestupMPV prestup, QVector<PrestupMPV> seznamPrestupu);
private slots:
    QByteArray requestReceived(QNetworkReply *replyoo);
signals:
    void stazeniHotovo ();
};

#endif // XMLMPVPARSER_H
