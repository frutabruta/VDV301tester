#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "cestaudaje.h"
#include "sqlprace.h"
#include "httpserver/myhttpserver.h"
#include "xmlgenerator.h"
#include "xmlmpvparser.h"
#include "xmlropidparser.h"
#include "ibisovladani.h"

#include "sqlpraceropid.h"
#include <QNetworkAccessManager>
#include <QMainWindow>
#define MAX_ZAST 100
#include "VDV301_Display/seznamzastavek.h"
#include <QVector>
#include <QtSerialPort/QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //SeznamZastavek* globalniSeznamZastavek = new SeznamZastavek[MAX_ZAST]; //new SeznamZastavek[MAX_ZAST];
    QVector<SeznamZastavek>  globalniSeznamZastavek ;
    //int vytvor();
    CestaUdaje novatrida;
    //SQLprace mojesql;
    SqlPraceRopid mojesql;

    int cisloPortu=12;
    myHTTPserver HHserver;
    xmlGenerator TestXmlGenerator;
    XmlMpvParser mpvParser;
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    void OdeslatDataDoDispleju(QDomDocument prestupyDomDocument);    
    void xmlHromadnyUpdate();    
    void ObnoveniServeru(QByteArray dataDoServeru);
    XmlRopidParser xmlRopidParser;
    IbisOvladani ibisOvladani;

//void StahniMpvXml(int cisloCis, QString Ids);
    //QByteArray requestReceived(QNetworkReply *replyoo);
private slots:
  // QByteArray requestReceived(QNetworkReply *replyoo);
    void on_prikaztlacitko_clicked();
    void on_sipkaNahoru_clicked();
    void on_sipkaDolu_clicked();
    void on_ubratTlacitko_clicked();
    void on_pripojeniTlacitko_clicked();
    void on_pridatTlacitko_clicked();
    void on_quitTlacitko_clicked();
    void on_tlacitkoNavic_clicked();
    void on_prijezd_clicked();
    void on_BeforeStop_clicked();
    void on_AtStop_2_clicked();
    void on_AfterStop_clicked();
    void on_BetweenStop_clicked();
    void PostDoDispleje(QUrl adresaDispleje, QByteArray dataDoPostu);
    void MpvNetReady();
    void on_prestupyCheckbox_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    //void on_pushButton_clicked();

    void on_tlacitkoNactiXMLropid_clicked();

    void on_tlacitkoZpet_clicked();

    void on_tlacitkoNastaveni_clicked();

    void on_tlacitkoSQL_clicked();

    void on_tlacitkoTruncate_clicked();

    void on_tlacitkoOdesliPrikaz_clicked();

    void on_tlacitkoNastavPort_clicked();

private:
    Ui::MainWindow *ui;
    //void replyFinished(QNetworkReply *);
    void AktualizaceDispleje();
};

#endif // MAINWINDOW_H
