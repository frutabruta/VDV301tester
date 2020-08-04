#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cestaudaje.h"
#include "sqlprace.h"
#include "httpserver/myhttpserver.h"
#include "xmlgenerator.h"

#include <QNetworkReply>
#include "VDV301_Display/seznamzastavek.h"


//koment

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug()<<"MainWindow::MainWindow";
    ui->setupUi(this);
    ui->prepinadloStran->setCurrentIndex(0);
    ui->prepinadloStran->setWindowState(Qt::WindowFullScreen);
    //MainWindow::setWindowState(Qt::WindowFullScreen);
}
/*
int MainWindow::vytvor()
{
    qDebug()<<"MainWindow::vytvor";
    return 0;
}
*/

void MainWindow::xmlHromadnyUpdate()
{
    qDebug()<<"MainWindow::xmlHromadnyUpdate()";

    ui->locationStateIndicator->setText(novatrida.locationState);
    QDomDocument vstupniDomXml;
    if (novatrida.prestupy==true)
    {

        mpvParser.StahniMpvXml(globalniSeznamZastavek[novatrida.cislo].cisloCis,globalniSeznamZastavek[novatrida.cislo].ids);
        connect(&mpvParser,SIGNAL(stazeniHotovo()),this,SLOT(MpvNetReady()));
    }

    OdeslatDataDoDispleju(vstupniDomXml);

}

void MainWindow::OdeslatDataDoDispleju(QDomDocument prestupyDomDocument) //novy
{
    qDebug()<<"MainWindow::OdeslatDataDoDispleju";
    QByteArray zpracovanoMPV="";
    QByteArray vysledek2=TestXmlGenerator.AllData2( novatrida.cislo,novatrida.pocetZastavek,globalniSeznamZastavek, novatrida.aktlinka, novatrida.doorState, novatrida.locationState,prestupyDomDocument, false);
    ObnoveniServeru(vysledek2);
    QUrl seznamAdres[]={QUrl("http://192.168.12.128:60011"),QUrl("http://127.0.0.1:47475")};
    int pocetAdres=2;
    for(int i=0;i<pocetAdres;i++ )
    {
        PostDoDispleje(seznamAdres[i],vysledek2);
    }
    qDebug()<<"\n MainWindow::xmlUpdate";


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::MpvNetReady()
{
    qDebug()<<"MainWindow::MpvNetReady";
    mpvParser.naplnVstupDokument(mpvParser.stazenaData);
    mpvParser.prestupyXmlDokumentVystup=mpvParser.VytvorVystupniDokument(mpvParser.parsujDomDokument(),mpvParser.prestupyXmlDokumentVystup);
    OdeslatDataDoDispleju(mpvParser.prestupyXmlDokumentVystup);
}

void MainWindow::ObnoveniServeru(QByteArray dataDoServeru)
{
    qDebug()<<"MainWindow::ObnoveniServeru";
    QByteArray hlavicka="";
    QByteArray argumentXMLserveru = "";
    hlavicka+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    hlavicka+=("Content-Type: application/xml\r\n");
    hlavicka+=("Connection: close\r\n");
    hlavicka+=("Pragma: no-cache\r\n");
    hlavicka+=("\r\n");

    argumentXMLserveru.append(hlavicka);
    argumentXMLserveru.append(dataDoServeru);
    HHserver.zapisDoPromenne(argumentXMLserveru);
}
void MainWindow::PostDoDispleje(QUrl adresaDispleje, QByteArray dataDoPostu)
{
    qDebug()<<"MainWindow::PostDoDispleje";
    QByteArray postDataSize = QByteArray::number(dataDoPostu.size());
    QNetworkRequest pozadavekPOST(adresaDispleje);
    pozadavekPOST.setRawHeader("Connection", "Keep-Alive");
    pozadavekPOST.setRawHeader("Content-Length", postDataSize );
    pozadavekPOST.setRawHeader("Content-Type", "text/xml");
    // pozadavekPOST.setRawHeader("Expect", "100-continue");
    pozadavekPOST.setRawHeader("Accept-Encoding", "gzip, deflate");
    QNetworkAccessManager *manager2 = new QNetworkAccessManager();
    manager2->post(pozadavekPOST,dataDoPostu);
}




/*
void MainWindow::StahniMpvXml(int cisloCis, QString Ids)
{
    qDebug()<<"MainWindow::requestShowPage";
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(requestReceived(QNetworkReply*)));
    //manager->get(QNetworkRequest(QUrl("http://www.mpvnet.cz/PID/x/21619?pocet=15&pz=true&t=true")));
    QString adresa = "http://www.mpvnet.cz/"+Ids+"/x/"+QString::number(cisloCis)+"?pocet=15&pz=true&t=true";
    qDebug()<<adresa;
    //manager->get(QNetworkRequest(QUrl("http://www.mpvnet.cz/PID/x/51888?pocet=15&pz=true&t=true")));
    manager->get(QNetworkRequest(QUrl(adresa)));
}
*/

/*
QByteArray MainWindow::requestReceived(QNetworkReply* replyoo)
{
    qDebug()<<"MainWindow::requestReceived";
    QString replyText;
    QByteArray rawData = replyoo->readAll();
    QString textData(rawData);
    qDebug() << textData;
    mpvParser.stazenaData=rawData;
    return rawData;
}

*/
int MainWindow::on_prikaztlacitko_clicked()
{
    qDebug()<<"MainWindow::on_prikaztlacitko_clicked";
    novatrida.doorState="AllDoorsClosed";
    novatrida.aktlinka=ui->polelinky->text().toInt();
    novatrida.aktspoj=ui->polespoje->text().toInt();
    novatrida.cislo=1;
    //mojesql.zjistiPocet(novatrida.pocetZastavek,novatrida.cislo, novatrida.aktlinka,novatrida.aktspoj);
    QString textDoPole="";
    int vysledek=mojesql.StahniSeznam(novatrida.pocetZastavek, novatrida.aktlinka,novatrida.aktspoj,globalniSeznamZastavek);
    if (vysledek==0)
    {
        textDoPole="spoj neexistuje";
        ui->prikazovyvysledek->setText(textDoPole);
        return 0;

    }

    xmlHromadnyUpdate();

    qDebug()<<"\n on_prikaztlacitko_clicked \n";
    if(globalniSeznamZastavek.empty()==1)
    {
        qDebug()<<"seznam zastavek  je prazdny";

        return 0;
    }
    else
    {
        mojesql.TestDotaz(textDoPole,novatrida.cislo,novatrida.aktlinka,novatrida.aktspoj,globalniSeznamZastavek,novatrida.pocetZastavek);
        ui->prikazovyvysledek->setText(textDoPole);



    }
    return 1;
}

void MainWindow::on_sipkaNahoru_clicked()
{
    qDebug()<<"\n on_prikaztlacitko_clicked \n";
    if (novatrida.cislo<novatrida.pocetZastavek)
    {
        if(novatrida.locationState=="AtStop")
        {
            novatrida.locationState="AfterStop";
            novatrida.cislo++;
        }
        else
        {
            if(novatrida.locationState=="BeforeStop")
            {novatrida.locationState="AtStop";}

            if(novatrida.locationState=="BetweenStop")
            {novatrida.locationState="BeforeStop";}

            if(novatrida.locationState=="AfterStop")
            {novatrida.locationState="BetweenStop";}



        }
    }
    QString textDoPole="";
    mojesql.TestDotaz(textDoPole,novatrida.cislo,novatrida.aktlinka,novatrida.aktspoj,globalniSeznamZastavek,novatrida.pocetZastavek);
    ui->prikazovyvysledek->setText(textDoPole);
    novatrida.doorState="AllDoorsClosed";
    //novatrida.locationState="BetweenStop";
    ui->popisek->setText(QString::number(novatrida.cislo));
    int vysledek=mojesql.StahniSeznam(novatrida.pocetZastavek, novatrida.aktlinka,novatrida.aktspoj,globalniSeznamZastavek);
    //xmlUpdate(QUrl("http://192.168.1.128:60011"));
    if (vysledek==1)
    {
        xmlHromadnyUpdate();
    }


}

void MainWindow::on_sipkaDolu_clicked()
{
    qDebug()<<"\n on_sipkaDolu_clicked \n";
    if (novatrida.cislo>=1)
    {
        if (novatrida.cislo<novatrida.pocetZastavek)
        {
            if(novatrida.locationState=="AfterStop")
            {
                novatrida.locationState="AtStop";
                novatrida.cislo--;
            }
            else
            {
                if(novatrida.locationState=="BetweenStop")
                {novatrida.locationState="AfterStop";}

                if(novatrida.locationState=="BeforeStop")
                {novatrida.locationState="BetweenStop";}

                if(novatrida.locationState=="AtStop")
                {novatrida.locationState="BeforeStop";}
            }
            QString textDoPole="";
            mojesql.TestDotaz(textDoPole,novatrida.cislo,novatrida.aktlinka,novatrida.aktspoj,globalniSeznamZastavek,novatrida.pocetZastavek);
            ui->prikazovyvysledek->setText(textDoPole);
        }
        QString textDoPole="";
        mojesql.TestDotaz(textDoPole,novatrida.cislo,novatrida.aktlinka,novatrida.aktspoj,globalniSeznamZastavek,novatrida.pocetZastavek);
        ui->prikazovyvysledek->setText(textDoPole);
    }
    //novatrida.doorState="AllDoorsClosed";
    ui->popisek->setText(QString::number(novatrida.cislo));
    xmlHromadnyUpdate();
}


void MainWindow::on_pripojeniTlacitko_clicked()
{
    qDebug()<<"\n on_pripojeniTlacitko_clicked \n";
    mojesql.Pripoj(ui->lineEditSqlServer->text() );
    if (mojesql.vysledek==0)
    {
        ui->NazevVysledku->setText("nepovedlo se");
    }
    else
    {
        ui->NazevVysledku->setText("povedlo se");
    }
}

void MainWindow::AktualizaceDispleje()
{
    QString textDoPole="";
    mojesql.TestDotaz(textDoPole,novatrida.cislo,novatrida.aktlinka,novatrida.aktspoj,globalniSeznamZastavek,novatrida.pocetZastavek);
    ui->prikazovyvysledek->setText(textDoPole);


    /*
     ibisOvladani.dopocetCelni(ibisOvladani.nahradDiakritiku("l "+globalniSeznamZastavek[novatrida.cislo].LineName));
    ibisOvladani.dopocetCelni(ibisOvladani.nahradDiakritiku("v "+globalniSeznamZastavek[novatrida.cislo].NameLcd));
    ibisOvladani.dopocetCelni(ibisOvladani.nahradDiakritiku("zN "+globalniSeznamZastavek[novatrida.cislo+1].NameLcd+"-"+globalniSeznamZastavek[novatrida.cislo+2].NameLcd+"-"+globalniSeznamZastavek[novatrida.cislo+3].NameLcd));
    ibisOvladani.dopocetCelni(ibisOvladani.nahradDiakritiku("zI "+globalniSeznamZastavek[globalniSeznamZastavek.length()-1].NameLcd));
    ibisOvladani.dopocetCelni(ibisOvladani.nahradDiakritiku("aA1 <1B><56>"+globalniSeznamZastavek[novatrida.cislo].NameFront));
    ibisOvladani.dopocetCelni(ibisOvladani.nahradDiakritiku("aA1 <1B><56>"+globalniSeznamZastavek[novatrida.cislo].NameFront));
    */
}

void MainWindow::on_pridatTlacitko_clicked()
{
    qDebug()<<"\n on_pridatTlacitko_clicked \n";
    novatrida.cislo++;
    ui->popisek->setText(QString::number(novatrida.cislo));
    AktualizaceDispleje();
    xmlHromadnyUpdate();
}

void MainWindow::on_ubratTlacitko_clicked()
{
    qDebug()<<"\n on_ubratTlacitko_clicked \n";
    novatrida.cislo--;
    ui->popisek->setText(QString::number(novatrida.cislo));
    AktualizaceDispleje();
    xmlHromadnyUpdate();
}

void MainWindow::on_quitTlacitko_clicked()
{
    qDebug()<<"\n on_quitTlacitko_clicked \n";
    MainWindow::close();
}

void MainWindow::on_tlacitkoNavic_clicked()
{

    qDebug()<< "on_tlacitkoNavic_clicked";
    mojesql.StahniSeznam(novatrida.pocetZastavek, novatrida.aktlinka,novatrida.aktspoj,globalniSeznamZastavek);
    QByteArray vysledekMpvnetu = "<TBL cas=\"2019-08-08T13:22:47\" ver=\"1.0.7145.21217\" text=\"Ověřovací provoz. Bez záruky.\"><t id=\"62887\" stan=\"A,B,M1,M2\" zast=\"Národní třída\"><o stan=\"B\" lin=\"9\" alias=\"9\" spoj=\"46\" smer=\"Praha,Sídliště Řepy\" odj=\"2019-08-08T13:23:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"50697\"/><o stan=\"A\" lin=\"18\" alias=\"18\" spoj=\"95\" smer=\"Praha,Vozovna Pankrác\" odj=\"2019-08-08T13:23:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"59386\"/><o stan=\"B\" lin=\"18\" alias=\"18\" spoj=\"158\" smer=\"Praha,Nádraží Podbaba\" odj=\"2019-08-08T13:23:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"63414\"/><o stan=\"M2\" lin=\"B\" alias=\"B\" spoj=\"9\" smer=\"Praha,Černý Most\" odj=\"2019-08-08T13:23:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Metro\" dd=\"1\" smer_c=\"47090\"/><o stan=\"A\" lin=\"16\" alias=\"16\" spoj=\"83\" smer=\"Praha,Lehovec\" odj=\"2019-08-08T13:24:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27872\"/><o stan=\"A\" lin=\"23\" alias=\"23\" spoj=\"22\" smer=\"Praha,Zvonařka\" odj=\"2019-08-08T13:24:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"62902\"/><o stan=\"A\" lin=\"9\" alias=\"9\" spoj=\"139\" smer=\"Praha,Spojovací\" odj=\"2019-08-08T13:25:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27891\"/><o stan=\"B\" lin=\"10\" alias=\"10\" spoj=\"102\" smer=\"Praha,Sídliště Řepy\" odj=\"2019-08-08T13:25:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"50697\"/><o stan=\"B\" lin=\"22\" alias=\"22\" spoj=\"133\" smer=\"Praha,Vypich\" odj=\"2019-08-08T13:25:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"51451\"/><o stan=\"M1\" lin=\"B\" alias=\"B\" spoj=\"197\" smer=\"Praha,Zličín\" odj=\"2019-08-08T13:25:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Metro\" dd=\"1\" smer_c=\"28037\"/><o stan=\"A\" lin=\"22\" alias=\"22\" spoj=\"99\" smer=\"Praha,Nádraží Strašnice\" odj=\"2019-08-08T13:26:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"57696\"/><o stan=\"B\" lin=\"2\" alias=\"2\" spoj=\"35\" smer=\"Praha,Sídliště Petřiny\" odj=\"2019-08-08T13:27:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"63906\"/><o stan=\"M2\" lin=\"B\" alias=\"B\" spoj=\"79\" smer=\"Praha,Černý Most\" odj=\"2019-08-08T13:28:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Metro\" dd=\"1\" smer_c=\"47090\"/><o stan=\"B\" lin=\"9\" alias=\"9\" spoj=\"54\" smer=\"Praha,Sídliště Řepy\" odj=\"2019-08-08T13:29:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"50697\"/><o stan=\"A\" lin=\"10\" alias=\"10\" spoj=\"47\" smer=\"Praha,Sídliště Ďáblice\" odj=\"2019-08-08T13:29:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27916\"/></t></TBL>";
    mpvParser.naplnVstupDokument(vysledekMpvnetu);
    mpvParser.VytvorVystupniDokument(mpvParser.parsujDomDokument(),mpvParser.prestupyXmlDokumentVystup);


    MainWindow::setWindowState(Qt::WindowFullScreen);
}

void MainWindow::on_prijezd_clicked()
{

    qDebug()<<"\n on_prijezd_clicked \n";
    novatrida.doorState="DoorsOpen";
    novatrida.locationState="AtStop";
    xmlHromadnyUpdate();

}

/*
void MainWindow::replyFinished(QNetworkReply*)
{
}
*/

void MainWindow::on_BeforeStop_clicked()
{

    novatrida.locationState="BeforeStop";
    xmlHromadnyUpdate();
}

void MainWindow::on_AtStop_2_clicked()
{
 //   hlasic.gong();
    hlasic.vyhlasZastavku(globalniSeznamZastavek[novatrida.cislo].cisloOis,globalniSeznamZastavek[novatrida.cislo].cisloCis);
    novatrida.locationState="AtStop";
    xmlHromadnyUpdate();

}

void MainWindow::on_AfterStop_clicked()
{
    novatrida.locationState="AfterStop";
    xmlHromadnyUpdate();
}

void MainWindow::on_BetweenStop_clicked()
{
    novatrida.locationState="BetweenStop";
    xmlHromadnyUpdate();
}

void MainWindow::on_prestupyCheckbox_stateChanged(int arg1)
{

}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    novatrida.prestupy= ui->checkBox->checkState();
}



void MainWindow::on_tlacitkoNactiXMLropid_clicked()
{
    xmlRopidParser.otevriSoubor();
}

void MainWindow::on_tlacitkoZpet_clicked()
{
    ui->prepinadloStran->setCurrentIndex(0);
}

void MainWindow::on_tlacitkoNastaveni_clicked()
{
    ui->prepinadloStran->setCurrentIndex(1);
}

void MainWindow::on_tlacitkoSQL_clicked()
{
    xmlRopidParser.databazeStart(ui->lineEditSqlServer->text());
}

void MainWindow::on_tlacitkoTruncate_clicked()
{
    xmlRopidParser.truncateAll();
}

void MainWindow::on_tlacitkoOdesliPrikaz_clicked()
{
    // ibisOvladani.dopocetCelni("l006");
}

void MainWindow::on_tlacitkoNastavPort_clicked()
{



    ibisOvladani.globalniSeriovyPort=ui->lineEdit_jmenoPortu->text();
    ibisOvladani.dopocetCelni("l006");
    ibisOvladani.dopocetCelni("aA1 ahoj");
    ibisOvladani.dopocetCelni("v povel v\\");
    ibisOvladani.dopocetCelni("zA povel zA");
    ibisOvladani.dopocetCelni("zN povel zN");
    ibisOvladani.dopocetCelni("xC2");
}

void MainWindow::on_tlacitkoIBIS_clicked()
{
    ibisOvladani.dopocetCelni("xC2");
    ibisOvladani.odesliFrontKomplet(globalniSeznamZastavek,novatrida.cislo);
    ibisOvladani.odesliSideKomplet(globalniSeznamZastavek,novatrida.cislo);
    //ibisOvladani.odesliInnerKomplet(globalniSeznamZastavek,novatrida.cislo);
    ibisOvladani.odesliJKZKomplet(globalniSeznamZastavek,novatrida.cislo);
    ibisOvladani.odeslikompletBUSEjednoradekAA(globalniSeznamZastavek,novatrida.cislo);
    ibisOvladani.odesliRearKomplet(globalniSeznamZastavek,novatrida.cislo);
}
