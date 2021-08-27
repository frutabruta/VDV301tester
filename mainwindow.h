#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "VDV301struktury/cestaudaje.h"



#include "xmlmpvparser.h"
#include "xmlropidparser.h"
#include "ibisovladani.h"
#include "hlasic.h"

#include "sqlpraceropid.h"
#include <QNetworkAccessManager>
#include <QMainWindow>
#define MAX_ZAST 100
#include "VDV301struktury/zastavka.h"
#include "VDV301struktury/linka.h"
#include "VDV301struktury/cestaudaje.h"
#include <QVector>
#include <QListWidget>

#include <QtSerialPort/QSerialPort>


#include "VDV301publisher/httpsluzba.h"
#include "VDV301publisher/customerinformationservice.h"
#include "VDV301publisher/ticketvalidationservice.h"
#include "VDV301struktury/zastavkacil.h"


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
    QVector<ZastavkaCil>  globalniSeznamZastavek ;
    //int vytvor();
    //CestaUdaje stavSystemu2;
    CestaUdaje stavSystemu;
    //SQLprace mojesql;
    SqlPraceRopid mojesql;
    int cisloPortu=12;


    XmlMpvParser mpvParser;
    void xmlHromadnyUpdate();

    XmlRopidParser xmlRopidParser;
    IbisOvladani ibisOvladani;
    Hlasic hlasic;
    QVector <Linka> seznamLinek;
    QVector <Spoj> seznamSpoju;
    bool platnostSpoje=1;
    int VDV301verze=0;

    HttpSluzba deviceManagementService1_0;
    CustomerInformationService customerInformationService1_0;
    CustomerInformationService customerInformationService2_2CZ1_0;
    TicketValidationService ticketValidationService2_3CZ1_0;

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
    //void PostDoDispleje(QUrl adresaDispleje, QString dataDoPostu);
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
    void startDatabaze();
    void inicializacePoli();
    void vypisSubscribery(QVector<Subscriber> adresy);

    void vypisSubscribery2(QVector<Subscriber> adresy);
private slots:
    //void novySubsriber(QUrl adresaSubscribera);

    void on_tlacitkoAddsubscriber_clicked();
    void on_tlacitkoRemoveSubscriber_clicked();
    void on_tlacitkoHlaseniSlozka_clicked();
    void on_tlacitkoAddsubscriber_2_clicked();
    void on_tlacitkoRemoveSubscriber_2_clicked();
    void vypisDiagnostika(QString vstup);
};

#endif // MAINWINDOW_H
