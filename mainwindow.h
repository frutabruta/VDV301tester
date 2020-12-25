#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "cestaudaje.h"
#include "sqlprace.h"
#include "httpserver/myhttpserver.h"
#include "xmlgenerator.h"
#include "xmlmpvparser.h"
#include "xmlropidparser.h"
#include "ibisovladani.h"
#include "hlasic.h"

#include "sqlpraceropid.h"
#include <QNetworkAccessManager>
#include <QMainWindow>
#define MAX_ZAST 100
#include "VDV301_Display/seznamzastavek.h"
#include "VDV301_Display/linka.h"
#include <QVector>
#include <QListWidget>

#include <QtSerialPort/QSerialPort>

#include "qtzeroconf/qzeroconf.h"
#include "httpsluzba.h"



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

    xmlGenerator TestXmlGenerator;
    XmlMpvParser mpvParser;
    void xmlHromadnyUpdate();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    void OdeslatDataDoDispleju(QDomDocument prestupyDomDocument, int verzeVDV301);

    void ObnoveniServeru(QByteArray dataDoServeru);
    XmlRopidParser xmlRopidParser;
    IbisOvladani ibisOvladani;
    Hlasic hlasic;
    QVector <Linka> seznamLinek;
    QVector <Spoj> seznamSpoju;
    bool platnostSpoje=1;
    int VDV301verze=0;

    HttpSluzba DeviceManagementService;
    HttpSluzba CustomerInformationService;

    QVector<QUrl> seznamSubscriberu;






    //bonjour
    QZeroConf zeroConf;
    QZeroConf zeroConf2;

//void StahniMpvXml(int cisloCis, QString Ids);
    //QByteArray requestReceived(QNetworkReply *replyoo);
    int priPrijezdu();
    int priOdjezdu();
    void NaplnVyberLinky(QVector<Linka> docasnySeznamLinek);
    void NaplnVyberSpoje(QVector<Spoj> docasnySeznamSpoju);

private slots:
  // QByteArray requestReceived(QNetworkReply *replyoo);
    int on_prikaztlacitko_clicked();
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



    void on_tlacitkoNastaveni_clicked();

    void on_tlacitkoSQL_clicked();

    void on_tlacitkoTruncate_clicked();

    void on_tlacitkoOdesliPrikaz_clicked();

    void on_tlacitkoNastavPort_clicked();

    void on_tlacitkoIBIS_clicked();

    void on_listSpoje_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_listLinek_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_tlacitkoZpetVydej_clicked();

    void on_tlacitkoLinkospoj_clicked();

    void on_tlacitkoSmazOkno_clicked();

    void on_tlacitkoManual_clicked();

    void on_tlacitkoOdesliXml_clicked();

private:
    Ui::MainWindow *ui;
    //void replyFinished(QNetworkReply *);
    void AktualizaceDispleje();
    void bonjourStartKomplet();

    void bonjourStartPublish2(QString nazevSluzby, QString typSluzby, int port, QZeroConf &instanceZeroConf);
    void startDatabaze();
    void inicializacePoli();
    void vypisSubscribery(QVector<QUrl> adresy);

private slots:
    void novySubsriber(QUrl adresaSubscribera);

};

#endif // MAINWINDOW_H
