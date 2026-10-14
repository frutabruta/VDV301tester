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

class GolemioInfotext
{


public:
    enum DisplayType
    {
        DisplayTypeInline,
        DisplayTypeGeneral,
        DisplayTypeGeneralAlternate
    };

    DisplayType display_type=DisplayTypeGeneral;
    QString text="";
    QString text_en="";
    QVector<QString> related_stops;
    QDateTime valid_from;
    QDateTime valid_to;

    static QString displayTypeToQString(GolemioInfotext::DisplayType input);
    static GolemioInfotext::DisplayType displayTypeFromQString(QString input);

};



class Golemio: public QObject
{
    Q_OBJECT
public:
    //konstruktor a destruktor
    Golemio(QByteArray klic);
    ~Golemio();


    QByteArray stazenaData="";

    QVector<ConnectionGolemio> seznamPrestupuGolemio;
    QVector<GolemioInfotext> golemioInfotextList;


    void naplnVstupDokument(QByteArray vstup);
;
    void stahniMpvXml(int cisloCis, QString Ids);
    QVector<ConnectionMPV> vyfiltrujPrestupy(QVector<ConnectionMPV> vstupniPrestupy, Line linka); //unused
    bool jePrestupNaSeznamu(ConnectionMPV prestup, QVector<ConnectionMPV> seznamPrestupu);

    QVector<ConnectionGolemio> parseDomDocumentDepartures();
    QVector<GolemioInfotext> parseDomDocumentInfotexts();


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
