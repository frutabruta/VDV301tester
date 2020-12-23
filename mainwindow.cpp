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
    ui(new Ui::MainWindow),
    DeviceManagementService("DeviceManagementService","_ibisip_http._tcp",47477),
    CustomerInformationService("CustomerInformationService","_ibisip_http._tcp",47479)
{
    qDebug()<<"MainWindow::MainWindow";
    ui->setupUi(this);
    ui->prepinadloStran->setCurrentIndex(3);
    ui->prepinadloStran->setWindowState(Qt::WindowFullScreen);
    startDatabaze();
    seznamSubscriberu.push_back(QUrl("http://192.168.12.128:60011"));
    seznamSubscriberu.push_back(QUrl("http://127.0.0.1:47475"));
    //this->bonjourStartPublish2("CustomerInformationService","_ibisip_http._tcp",47450,zeroConf);


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

    //ui->locationStateIndicator->setText(novatrida.locationState);
    QDomDocument vstupniDomXmlPrestupy;
    if (novatrida.prestupy==true)
    {

        mpvParser.StahniMpvXml(globalniSeznamZastavek[novatrida.cislo].cisloCis,globalniSeznamZastavek[novatrida.cislo].ids);
        connect(&mpvParser,SIGNAL(stazeniHotovo()),this,SLOT(MpvNetReady()));
    }

    OdeslatDataDoDispleju(vstupniDomXmlPrestupy,VDV301verze);

}

void MainWindow::OdeslatDataDoDispleju(QDomDocument prestupyDomDocument, int verzeVDV301) //novy
{
    qDebug()<<"MainWindow::OdeslatDataDoDispleju";
    QByteArray zpracovanoMPV="";
    QByteArray vysledek2="";
    if (verzeVDV301==0)
    {
        vysledek2=TestXmlGenerator.AllData2( novatrida.cislo,globalniSeznamZastavek, novatrida.aktlinka, novatrida.doorState, novatrida.locationState,prestupyDomDocument, false);
    }
    else
    {
        vysledek2=TestXmlGenerator.AllDataRopid( novatrida.cislo,globalniSeznamZastavek, novatrida.aktlinka, novatrida.doorState, novatrida.locationState,prestupyDomDocument, false);
    }


    ObnoveniServeru(vysledek2);
      /*
    QUrl seznamAdres[]={QUrl("http://192.168.12.128:60011"),QUrl("http://127.0.0.1:47475")};

    int pocetAdres=2;
    for(int i=0;i<pocetAdres;i++ )
    {
        PostDoDispleje(seznamAdres[i],vysledek2);
    }
    */



    for(int i=0;i<seznamSubscriberu.count();i++ )
    {
        PostDoDispleje(seznamSubscriberu[i],vysledek2);
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
    OdeslatDataDoDispleju(mpvParser.prestupyXmlDokumentVystup,VDV301verze);
}

void MainWindow::ObnoveniServeru(QByteArray dataDoServeru)
{
    qDebug()<<"MainWindow::ObnoveniServeru";




    //CustomerInformationService.nastavHlavicku(hlavicka);
    CustomerInformationService.nastavObsah(dataDoServeru);
    CustomerInformationService.aktualizuj();
    /*
     *
    QByteArray argumentXMLserveru = "";
    argumentXMLserveru.append(hlavicka);
    argumentXMLserveru.append(dataDoServeru);
    QByteArray hlavicka="";

    hlavicka+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    hlavicka+=("Content-Type: application/xml\r\n");
    hlavicka+=("Connection: close\r\n");
    hlavicka+=("Pragma: no-cache\r\n");
    hlavicka+=("\r\n");

    HHserver.zapisDoPromenne(argumentXMLserveru);
    HHserver2.zapisDoPromenne(argumentXMLserveru)
;*/
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
    novatrida.cislo=0;
    //mojesql.zjistiPocet(novatrida.pocetZastavek,novatrida.cislo, novatrida.aktlinka,novatrida.aktspoj);
    QString textDoPole="";
    int vysledek=mojesql.StahniSeznam( novatrida.aktlinka,novatrida.aktspoj,globalniSeznamZastavek,platnostSpoje);
    if (vysledek==0)
    {
        textDoPole="spoj neexistuje";
        ui->prikazovyvysledek->setText(textDoPole);
        return 0;

    }

    xmlHromadnyUpdate();


    if(globalniSeznamZastavek.empty()==1)
    {
        qDebug()<<"seznam zastavek  je prazdny";

        return 0;
    }
    else
    {
        AktualizaceDispleje();
        ui->prepinadloStran->setCurrentIndex(0);
        /*
        mojesql.vytvorHlavniText(textDoPole,novatrida.cislo,novatrida.aktlinka,novatrida.aktspoj,globalniSeznamZastavek,novatrida.pocetZastavek);
        ui->prikazovyvysledek->setText(textDoPole);
        */



    }
    return 1;
}

void MainWindow::on_sipkaNahoru_clicked()
{
    qDebug()<<"\n MainWindow::on_sipkaNahoru_clicked() \n";
    if (novatrida.cislo<(globalniSeznamZastavek.count()-1))
    {
        if(novatrida.locationState=="AtStop")
        {
            novatrida.locationState="AfterStop";
            novatrida.cislo++;
            priOdjezdu();
        }
        else
        {
            if(novatrida.locationState=="BeforeStop")
            {
                novatrida.locationState="AtStop";
                priPrijezdu();
            }

            if(novatrida.locationState=="BetweenStop")
            {novatrida.locationState="BeforeStop";}

            if(novatrida.locationState=="AfterStop")
            {novatrida.locationState="BetweenStop";}



        }
    }
    QString textDoPole="";
    AktualizaceDispleje();

    /*
    mojesql.vytvorHlavniText(textDoPole,novatrida.cislo,novatrida.aktlinka,novatrida.aktspoj,globalniSeznamZastavek,novatrida.pocetZastavek);
    ui->prikazovyvysledek->setText(textDoPole);
    */
    novatrida.doorState="AllDoorsClosed";
    //novatrida.locationState="BetweenStop";
    ui->popisek->setText(QString::number(novatrida.cislo));
    xmlHromadnyUpdate();
    // int vysledek=mojesql.StahniSeznam(novatrida.pocetZastavek, novatrida.aktlinka,novatrida.aktspoj,globalniSeznamZastavek,platnostSpoje);
    //xmlUpdate(QUrl("http://192.168.1.128:60011"));

    /*
int vysledek=1;
if (vysledek==1)
    {
        xmlHromadnyUpdate();
    }
    */


}

void MainWindow::on_sipkaDolu_clicked()
{
    qDebug()<<"\n on_sipkaDolu_clicked \n";
    if (novatrida.cislo>=1)
    {
            if(novatrida.locationState=="AfterStop")
            {
                novatrida.locationState="AtStop";
                novatrida.cislo--;
                priPrijezdu();
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
            AktualizaceDispleje();

        /*
        mojesql.vytvorHlavniText(textDoPole,novatrida.cislo,novatrida.aktlinka,novatrida.aktspoj,globalniSeznamZastavek,novatrida.pocetZastavek);
        ui->prikazovyvysledek->setText(textDoPole);
        */
    }
    //novatrida.doorState="AllDoorsClosed";
    ui->popisek->setText(QString::number(novatrida.cislo));
    xmlHromadnyUpdate();
}


void MainWindow::on_pripojeniTlacitko_clicked()
{
    qDebug()<<"\n on_pripojeniTlacitko_clicked \n";
   startDatabaze();
}

void MainWindow::startDatabaze()
{
    qDebug()<<"MainWindow::startDatabaze()";

    mojesql.Pripoj(ui->lineEditSqlServer->text() );

    if (mojesql.VytvorSeznamLinek(seznamLinek)==1)
    {
    NaplnVyberLinky(seznamLinek);
    ui->NazevVysledku->setText("OK2");
    }
    else
    {
        ui->NazevVysledku->setText("FAIL2");
        qDebug()<<"chyba nacitani linek";
    }
}

void MainWindow::NaplnVyberLinky(QVector<Linka> docasnySeznamLinek)
{
    ui->listLinek->clear();
    for (int i = 0; i < docasnySeznamLinek.length(); ++i)
    {

        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(QString::number(docasnySeznamLinek.at(i).c));
        newItem->setData(Qt::UserRole, QString::number(docasnySeznamLinek.at(i).lc));
        ui->listLinek->addItem( newItem);
    }

}

void MainWindow::NaplnVyberSpoje(QVector<Spoj> docasnySeznamSpoju)
{
    qDebug()<<"MainWindow::NaplnVyberSpoje";
    if (ui->listSpoje->count()!=0)
    {
    ui->listSpoje->clear();
    }
    qDebug()<<"MainWindow::NaplnVyberSpoje_dp1";
    for (int i = 0; i < docasnySeznamSpoju.length(); ++i)
    {

        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(QString::number(docasnySeznamSpoju.at(i).cisloRopid));
        newItem->setData(Qt::UserRole, QString::number(docasnySeznamSpoju.at(i).cisloRopid ));
        ui->listSpoje->addItem( newItem);
        qDebug()<<"MainWindow::NaplnVyberSpoje_"<<QString::number(i);
    }
    qDebug()<<"MainWindow::NaplnVyberSpoje_konec";

}


void MainWindow::AktualizaceDispleje()
{
    qDebug()<<"MainWindow::AktualizaceDispleje()";
    QString textDoPole="";
    QString textPoleCasu="";
    mojesql.vytvorHlavniText(textDoPole,textPoleCasu,novatrida.cislo,globalniSeznamZastavek);
    ui->prikazovyvysledek->setText(textDoPole);
    ui->prikazovyvysledek_cas->setText(textPoleCasu);

    ui->locationStateIndicator->setText(novatrida.locationState);


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
    if (novatrida.cislo<(globalniSeznamZastavek.count()-1))
    {
        novatrida.cislo++;
    }

    ui->popisek->setText(QString::number(novatrida.cislo));
    AktualizaceDispleje();
    xmlHromadnyUpdate();
}

void MainWindow::on_ubratTlacitko_clicked()
{
    qDebug()<<"\n on_ubratTlacitko_clicked \n";
    if (novatrida.cislo>=2)
    {
        novatrida.cislo--;
    }
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
    /*
    mojesql.StahniSeznam(novatrida.pocetZastavek, novatrida.aktlinka,novatrida.aktspoj,globalniSeznamZastavek,platnostSpoje);
    QByteArray vysledekMpvnetu = "<TBL cas=\"2019-08-08T13:22:47\" ver=\"1.0.7145.21217\" text=\"Ověřovací provoz. Bez záruky.\"><t id=\"62887\" stan=\"A,B,M1,M2\" zast=\"Národní třída\"><o stan=\"B\" lin=\"9\" alias=\"9\" spoj=\"46\" smer=\"Praha,Sídliště Řepy\" odj=\"2019-08-08T13:23:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"50697\"/><o stan=\"A\" lin=\"18\" alias=\"18\" spoj=\"95\" smer=\"Praha,Vozovna Pankrác\" odj=\"2019-08-08T13:23:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"59386\"/><o stan=\"B\" lin=\"18\" alias=\"18\" spoj=\"158\" smer=\"Praha,Nádraží Podbaba\" odj=\"2019-08-08T13:23:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"63414\"/><o stan=\"M2\" lin=\"B\" alias=\"B\" spoj=\"9\" smer=\"Praha,Černý Most\" odj=\"2019-08-08T13:23:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Metro\" dd=\"1\" smer_c=\"47090\"/><o stan=\"A\" lin=\"16\" alias=\"16\" spoj=\"83\" smer=\"Praha,Lehovec\" odj=\"2019-08-08T13:24:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27872\"/><o stan=\"A\" lin=\"23\" alias=\"23\" spoj=\"22\" smer=\"Praha,Zvonařka\" odj=\"2019-08-08T13:24:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"62902\"/><o stan=\"A\" lin=\"9\" alias=\"9\" spoj=\"139\" smer=\"Praha,Spojovací\" odj=\"2019-08-08T13:25:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27891\"/><o stan=\"B\" lin=\"10\" alias=\"10\" spoj=\"102\" smer=\"Praha,Sídliště Řepy\" odj=\"2019-08-08T13:25:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"50697\"/><o stan=\"B\" lin=\"22\" alias=\"22\" spoj=\"133\" smer=\"Praha,Vypich\" odj=\"2019-08-08T13:25:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"51451\"/><o stan=\"M1\" lin=\"B\" alias=\"B\" spoj=\"197\" smer=\"Praha,Zličín\" odj=\"2019-08-08T13:25:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Metro\" dd=\"1\" smer_c=\"28037\"/><o stan=\"A\" lin=\"22\" alias=\"22\" spoj=\"99\" smer=\"Praha,Nádraží Strašnice\" odj=\"2019-08-08T13:26:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"57696\"/><o stan=\"B\" lin=\"2\" alias=\"2\" spoj=\"35\" smer=\"Praha,Sídliště Petřiny\" odj=\"2019-08-08T13:27:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"63906\"/><o stan=\"M2\" lin=\"B\" alias=\"B\" spoj=\"79\" smer=\"Praha,Černý Most\" odj=\"2019-08-08T13:28:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Metro\" dd=\"1\" smer_c=\"47090\"/><o stan=\"B\" lin=\"9\" alias=\"9\" spoj=\"54\" smer=\"Praha,Sídliště Řepy\" odj=\"2019-08-08T13:29:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"true\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"50697\"/><o stan=\"A\" lin=\"10\" alias=\"10\" spoj=\"47\" smer=\"Praha,Sídliště Ďáblice\" odj=\"2019-08-08T13:29:00+02:00\" sled=\"false\" zpoz=\"0\" np=\"false\" nad=\"false\" t=\"Tram\" dd=\"2\" smer_c=\"27916\"/></t></TBL>";
    mpvParser.naplnVstupDokument(vysledekMpvnetu);
    mpvParser.VytvorVystupniDokument(mpvParser.parsujDomDokument(),mpvParser.prestupyXmlDokumentVystup);
*/

    if (MainWindow::windowState()==Qt::WindowFullScreen )
    {
        MainWindow::setWindowState(Qt::WindowMaximized);
    }
    else
    {
        MainWindow::setWindowState(Qt::WindowFullScreen);
    }
}

void MainWindow::on_prijezd_clicked()
{


    qDebug()<<"\n MainWindow::on_prijezd_clicked() \n";
    this->priPrijezdu();


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
    qDebug()<<"";
    //   hlasic.gong();
    // hlasic.vyhlasZastavku2(globalniSeznamZastavek[novatrida.cislo].cisloOis,globalniSeznamZastavek[novatrida.cislo].cisloCis);
    priPrijezdu();

}

void MainWindow::on_AfterStop_clicked()
{
    qDebug()<<"";
    novatrida.locationState="AfterStop";
    xmlHromadnyUpdate();
}

void MainWindow::on_BetweenStop_clicked()
{
    qDebug()<<"";
    novatrida.locationState="BetweenStop";
    xmlHromadnyUpdate();
}

void MainWindow::on_prestupyCheckbox_stateChanged(int arg1)
{
    qDebug()<<"";
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    qDebug()<<"";
    novatrida.prestupy= ui->checkBox->checkState();
}



void MainWindow::on_tlacitkoNactiXMLropid_clicked()
{
    qDebug()<<"";
    xmlRopidParser.otevriSoubor();
}



void MainWindow::on_tlacitkoNastaveni_clicked()
{
    qDebug()<<"";
    ui->prepinadloStran->setCurrentIndex(2);
}

void MainWindow::on_tlacitkoSQL_clicked()
{
    qDebug()<<"";
    if (    xmlRopidParser.databazeStart(ui->lineEditSqlServer->text()) )
    {
      ui->NazevVysledku->setText("OK");
    }
    else
    {
        ui->NazevVysledku->setText("DB fail");
    }
}

void MainWindow::on_tlacitkoTruncate_clicked()
{
    qDebug()<<"";
    xmlRopidParser.truncateAll();
}

void MainWindow::on_tlacitkoOdesliPrikaz_clicked()
{
    qDebug()<<"";
    // ibisOvladani.dopocetCelni("l006");
}

void MainWindow::on_tlacitkoNastavPort_clicked()
{
    qDebug()<<"";


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
    qDebug()<<"";
    ibisOvladani.dopocetCelni("xC2");
    ibisOvladani.odesliFrontKomplet(globalniSeznamZastavek,novatrida.cislo);
    ibisOvladani.odesliSideKomplet(globalniSeznamZastavek,novatrida.cislo);
    //ibisOvladani.odesliInnerKomplet(globalniSeznamZastavek,novatrida.cislo);
    ibisOvladani.odesliJKZKomplet(globalniSeznamZastavek,novatrida.cislo);
    ibisOvladani.odeslikompletBUSEjednoradekAA(globalniSeznamZastavek,novatrida.cislo);
    ibisOvladani.odesliRearKomplet(globalniSeznamZastavek,novatrida.cislo);
}


int MainWindow::priPrijezdu()
{
    qDebug()<<"MainWindow::priPrijezdu";

    novatrida.doorState="DoorsOpen";


    if (novatrida.cislo<(globalniSeznamZastavek.length()-1))
    {
        hlasic.kompletZastavka(globalniSeznamZastavek[novatrida.cislo].cisloCis,globalniSeznamZastavek[novatrida.cislo].cisloOis,globalniSeznamZastavek[novatrida.cislo+1].cisloCis,globalniSeznamZastavek[novatrida.cislo+1].cisloOis);
    }
    else
    {
        hlasic.kompletKonecna(globalniSeznamZastavek[novatrida.cislo].cisloCis,globalniSeznamZastavek[novatrida.cislo].cisloOis );
    }
    novatrida.locationState="AtStop";
    xmlHromadnyUpdate();

    return 1;
}

int MainWindow::priOdjezdu()
{
    qDebug()<<"MainWindow::priOdjezdu()";
    //this->bonjourStartKomplet();

    //bonjourStartPublish();

    return 1;
}




void MainWindow::on_listLinek_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->polelinky->setText(ui->listLinek->currentItem()->data(Qt::UserRole ).toString() );
    novatrida.aktlinka=ui->listLinek->currentItem()->data(Qt::UserRole).toInt();
    if (mojesql.VytvorSeznamSpoju(seznamSpoju,novatrida.aktlinka)==1)
    {
        NaplnVyberSpoje(seznamSpoju);
    }
}

void MainWindow::on_listSpoje_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug()<<"MainWindow::on_listSpoje_currentItemChanged";
    if (ui->listSpoje->count()!=0)
    {
        qDebug()<<"pocetNeniNula";
        ui->polespoje->setText(ui->listSpoje->currentItem()->data(Qt::UserRole).toString());
        novatrida.aktspoj=ui->listSpoje->currentItem()->data(Qt::UserRole).toInt() ;
    }


}




void MainWindow::bonjourStartKomplet() //nikdy se nepouzije
{
    zeroConf.clearServiceTxtRecords();
    zeroConf2.clearServiceTxtRecords();
    this->bonjourStartPublish2("CustomerInformationService","_ibisip_http._tcp",47474,zeroConf);
    this->bonjourStartPublish2("DeviceManagementService","_ibisip_http._tcp",64602,zeroConf2); //47475
}



void MainWindow::bonjourStartPublish2(QString nazevSluzby, QString typSluzby,int port, QZeroConf &instanceZeroConf)
{
    qDebug()<<"MainWindow::bonjourStartPublish"<<nazevSluzby;

    instanceZeroConf.addServiceTxtRecord("ver", "1.0");
    //zeroConf.addServiceTxtRecord("ZeroConf is nice too");
    instanceZeroConf.startServicePublish(nazevSluzby.toUtf8(), typSluzby.toUtf8(), "local", port);

}

void MainWindow::on_tlacitkoZpetVydej_clicked()
{
    ui->prepinadloStran->setCurrentIndex(0);
}

void MainWindow::on_tlacitkoLinkospoj_clicked()
{
    ui->prepinadloStran->setCurrentIndex(1);
}



void MainWindow::inicializacePoli()
{
    globalniSeznamZastavek.clear();
    seznamLinek.clear();
    seznamSpoju.clear();
    novatrida.vymaz();
}

void MainWindow::on_tlacitkoSmazOkno_clicked()
{
ui->plainTextEditCustomXml->clear();
}

void MainWindow::on_tlacitkoManual_clicked()
{
    ui->prepinadloStran->setCurrentIndex(3);
}

void MainWindow::on_tlacitkoOdesliXml_clicked()
{
    qDebug()<<"on_tlacitkoOdesliXml_clicked()";




    QByteArray vysledek2="";

    vysledek2.append(ui->plainTextEditCustomXml->toPlainText());

    ObnoveniServeru(vysledek2);
    //QUrl seznamAdres[]={QUrl("http://192.168.12.128:60011"),QUrl("http://127.0.0.1:47475")};
    //int pocetAdres=2;
    for(int i=0;i<seznamSubscriberu.count();i++ )
    {
        PostDoDispleje(seznamSubscriberu[i],vysledek2);
        //PostDoDispleje(seznamAdres[i],vysledek2);
    }
    qDebug()<<"\n MainWindow::xmlUpdate";
}


void MainWindow::vypisSubscribery(QVector<QUrl> adresy)
{

    for (int i = 0;  i < adresy.count(); i++)
    {
      ui->seznamOdberatelu->addItem(adresy[i].toString() );
    }

}
