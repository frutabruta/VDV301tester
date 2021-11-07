#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "VDV301struktury/cestaudaje.h"
#include "xmlgenerator.h"

#include <QNetworkReply>
#include "VDV301struktury/zastavka.h"



//koment

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    deviceManagementService1_0("DeviceManagementService","_ibisip_http._tcp",47477,"1.0"),
    customerInformationService1_0("CustomerInformationService","_ibisip_http._tcp",47479,"1.0"),
    customerInformationService2_2CZ1_0("CustomerInformationService (2)","_ibisip_http._tcp",47480,"2.2CZ1.0"),
    ticketValidationService2_3CZ1_0("TicketValidationService","_ibisip_http._tcp",47481,"2.2CZ1.0"),
    konfigurace(QCoreApplication::applicationDirPath())
{
    qDebug()<<"MainWindow::MainWindow";
    ui->setupUi(this);
    ui->prepinadloStran->setCurrentIndex(1);
    ui->prepinadloStran->setWindowState(Qt::WindowFullScreen);
    startDatabaze();
    //seznamSubscriberu.push_back(QUrl("http://192.168.12.128:60011"));
    //seznamSubscriberu.push_back(QUrl("http://127.0.0.1:48479"));
    /*


    connect(&DeviceManagementService,&HttpSluzba::pridejSubscribera,this,&MainWindow::novySubsriber);
    connect(&CustomerInformationService,&HttpSluzba::pridejSubscribera,this,&MainWindow::novySubsriber);
    */
    connect(&customerInformationService1_0,&HttpSluzba::vypisSubscriberu,this,&MainWindow::vypisSubscribery);
    connect(&customerInformationService2_2CZ1_0,&HttpSluzba::vypisSubscriberu,this,&MainWindow::vypisSubscribery2);
    //this->bonjourStartPublish2("CustomerInformationService","_ibisip_http._tcp",47450,zeroConf);
    this->vypisSubscribery(customerInformationService1_0.seznamSubscriberu);
    this->vypisSubscribery2(customerInformationService2_2CZ1_0.seznamSubscriberu);
    connect(&mpvParser,SIGNAL(stazeniHotovo()),this,SLOT(MpvNetReady()));
    connect(&mojesql,&SqlPraceRopid::odesliChybovouHlasku,this,&MainWindow::vypisSqlVysledek);
    connect(&xmlRopidParser,&XmlRopidParser::odesliChybovouHlasku,this,&MainWindow::vypisSqlVysledek);
    //MainWindow::setWindowState(Qt::WindowFullScreen);
    QString compilationTime = QString("%1T%2").arg(__DATE__).arg(__TIME__);
    ui->label_build->setText(compilationTime);
    hlasic.zmenUmisteniProgramu(umisteniProgramu);
    konfigurace.vytvorDefaultniKonfiguraci();
    konfigurace.otevriSoubor();


}


void MainWindow::xmlHromadnyUpdate()
{
    qDebug()<<"MainWindow::xmlHromadnyUpdate()";
    qDebug()<<"delka seznamu tripu "<<seznamTripu.length();
    if (seznamTripu.isEmpty())
    {
        qDebug()<<"seznam tripu je prazdny";
        return;
    }

    //ui->locationStateIndicator->setText(novatrida.locationState);
    QDomDocument vstupniDomXmlPrestupy;
    if (stavSystemu.prestupy==true)
    {

        mpvParser.StahniMpvXml( this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.cisloCis,this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.ids);
        // connect(&mpvParser,SIGNAL(stazeniHotovo()),this,SLOT(MpvNetReady()));
    }
    qDebug()<<QString::number(stavSystemu.indexAktZastavky);
    QVector<prestupMPV> prestupy;
    customerInformationService1_0.aktualizaceObsahuSluzby(prestupy,VDV301verze,stavSystemu,this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek);
    customerInformationService2_2CZ1_0.aktualizaceObsahuSluzby(prestupy,VDV301verze,stavSystemu,this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek);
    //ticketValidationService2_3CZ1_0.aktualizaceInternichPromennychOdeslat(vstupniDomXmlPrestupy,VDV301verze,stavSystemu,globalniSeznamZastavek);
    ticketValidationService2_3CZ1_0.aktualizaceObsahuSluzby(prestupy,VDV301verze,stavSystemu,this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek);

}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::MpvNetReady()
{
    qDebug()<<"MainWindow::MpvNetReady";
    mpvParser.naplnVstupDokument(mpvParser.stazenaData);
    //mpvParser.prestupyXmlDokumentVystup1_0=mpvParser.connections1_0( mpvParser.parsujDomDokument());
    QVector<prestupMPV> prestupy=mpvParser.parsujDomDokument();

    //mpvParser.prestupyXmlDokumentVystup2_2CZ1_0 =mpvParser.connections2_2CZ1_0(mpvParser.parsujDomDokument());
    customerInformationService1_0.aktualizaceObsahuSluzby(prestupy,VDV301verze,stavSystemu,this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek);
    customerInformationService2_2CZ1_0.aktualizaceObsahuSluzby(prestupy, VDV301verze,stavSystemu,this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek);
    //customerInformationService2_2CZ1_0.aktualizaceObsahuSluzby(mpvParser.prestupyXmlDokumentVystup2_2CZ1_0, VDV301verze,stavSystemu,globalniSeznamZastavek);

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
    stavSystemu.doorState="AllDoorsClosed";
    stavSystemu.aktspoj.linka.c =ui->polelinky->text().toInt();
    stavSystemu.aktspoj.cisloRopid=ui->polespoje->text().toInt();
    /*
    if (!seznamSpoju.isEmpty())
    {
            stavSystemu.aktspoj=seznamSpoju.at(ui->listSpoje->selectionModel()->selectedRows().at(stavSystemu.indexTripu).row());
    }
    */
         //   ui->polespoje->text().toInt();
    stavSystemu.indexAktZastavky=0;
    //mojesql.zjistiPocet(novatrida.pocetZastavek,novatrida.cislo, novatrida.aktlinka,novatrida.aktspoj);
    QString textDoPole="";
    //int vysledek=mojesql.StahniSeznam( stavSystemu.aktlinka,stavSystemu.aktspoj,this->seznamTripu,platnostSpoje);


    int vysledek=mojesql.StahniSeznam( stavSystemu.aktspoj.linka,stavSystemu.aktspoj.cisloRopid,this->seznamTripu,platnostSpoje);
    if (vysledek==2)
    {
        qDebug()<<"existuje navazujici spoj";
    }




    if (vysledek==0)
    {
        textDoPole="spoj neexistuje";
        ui->prikazovyvysledek->setText(textDoPole);
        return 0;

    }
    xmlHromadnyUpdate();
    if(this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek.empty()==1)
    {
        qDebug()<<"seznam zastavek  je prazdny";
        return 0;
    }
    else
    {
        AktualizaceDispleje();
        stavSystemu.locationState="AtStop";
        ui->tlacitkoZpetVydej->setChecked(1);
        ui->prepinadloStran->setCurrentIndex(0);
    }
    return 1;
}


int MainWindow::on_prikazTlacitkoTurnus_clicked()
{
    qDebug()<<"MainWindow::on_prikaztTurnuslacitko_clicked";
    stavSystemu.doorState="AllDoorsClosed";
    stavSystemu.aktlinka.LineNumber =ui->poleLinkyTurnus->text().toInt();
    /*
    if (!seznamSpoju.isEmpty())
    {
            stavSystemu.aktspoj=seznamSpoju.at(ui->listTurnusSpoje->selectionModel()->selectedRows().at(stavSystemu.indexTripu).row());
    }*/
    //stavSystemu.aktspoj=ui->poleSpojeTurnus->text().toInt();
    stavSystemu.indexAktZastavky=0;
    //mojesql.zjistiPocet(novatrida.pocetZastavek,novatrida.cislo, novatrida.aktlinka,novatrida.aktspoj);
    QString textDoPole="";
    //int vysledek=mojesql.StahniSeznam( stavSystemu.aktlinka,stavSystemu.aktspoj,this->seznamTripu,platnostSpoje);


    //int vysledek=mojesql.StahniSeznam( stavSystemu.aktspoj.linka,stavSystemu.aktspoj.cisloRopid,this->seznamTripu,platnostSpoje);
    seznamTripu.clear();


      int vysledek=0;
        Spoj iterSpoj;
        stavSystemu.indexTripu=ui->listTurnusSpoje->currentRow();
        foreach (iterSpoj, stavSystemu.aktObeh.seznamSpoju )
        {

               vysledek=mojesql.StahniSeznamCelySpoj(iterSpoj,this->seznamTripu,platnostSpoje);
               qDebug()<<"nacetl jsem spoj s vysledkem "<<vysledek;
        }

                  qDebug()<<"je nacteno "<<stavSystemu.aktObeh.seznamSpoju.length()<<" spoju";



  //  int vysledek=mojesql.StahniSeznamCelySpoj(stavSystemu.aktspoj,this->seznamTripu,platnostSpoje);
    if (vysledek==2)
    {
        qDebug()<<"existuje navazujici spoj";
    }




    if (vysledek==0)
    {
        textDoPole="spoj neexistuje";
        ui->prikazovyvysledek->setText(textDoPole);
        return 0;

    }
    xmlHromadnyUpdate();
    if(this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek.empty()==1)
    {
        qDebug()<<"seznam zastavek  je prazdny";
        return 0;
    }
    else
    {
        AktualizaceDispleje();
        stavSystemu.locationState="AtStop";
        ui->tlacitkoZpetVydej->setChecked(1);
        ui->prepinadloStran->setCurrentIndex(0);
    }
    return 1;
}

void MainWindow::on_sipkaNahoru_clicked()
{
    qDebug()<<"\n MainWindow::on_sipkaNahoru_clicked() \n";
    if (stavSystemu.indexAktZastavky<(this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek.count()-1))
    {
        if(stavSystemu.locationState=="AtStop")
        {
            stavSystemu.locationState="AfterStop";
            ui->AfterStop->setChecked(true);
            stavSystemu.indexAktZastavky++;
            priOdjezdu();
        }
        else
        {
            if(stavSystemu.locationState=="BeforeStop")
            {
                stavSystemu.locationState="AtStop";
                ui->AtStop_2->setChecked(true);
                priPrijezdu();
            }

            if(stavSystemu.locationState=="BetweenStop")
            {
                stavSystemu.locationState="BeforeStop";
                ui->BeforeStop->setChecked(true);
            }

            if(stavSystemu.locationState=="AfterStop")
            {stavSystemu.locationState="BetweenStop";
                ui->BetweenStop->setChecked(true);
            }
        }
    }
    //QString textDoPole="";
    AktualizaceDispleje();
    stavSystemu.doorState="AllDoorsClosed";
    ui->popisek->setText(QString::number(stavSystemu.indexAktZastavky));
    xmlHromadnyUpdate();
}

void MainWindow::on_sipkaDolu_clicked()
{
    qDebug()<<"\n on_sipkaDolu_clicked \n";
    if (stavSystemu.indexAktZastavky>=1)
    {
        if(stavSystemu.locationState=="AfterStop")
        {
            stavSystemu.locationState="AtStop";
            stavSystemu.indexAktZastavky--;
            priPrijezdu();
        }
        else
        {
            if(stavSystemu.locationState=="BetweenStop")
            {stavSystemu.locationState="AfterStop";}

            if(stavSystemu.locationState=="BeforeStop")
            {stavSystemu.locationState="BetweenStop";}

            if(stavSystemu.locationState=="AtStop")
            {stavSystemu.locationState="BeforeStop";}
        }
        QString textDoPole="";
        AktualizaceDispleje();
    }
    ui->popisek->setText(QString::number(stavSystemu.indexAktZastavky));
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
        QVector<Linka> kmenoveLinky;
        mojesql.VytvorSeznamKmenovychLinek(kmenoveLinky);
        NaplnKmenoveLinky(kmenoveLinky);
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
        //newItem->setData(Qt::UserRole, QString::number(docasnySeznamLinek.at(i).lc));
        newItem->setData(Qt::UserRole, QString::number(docasnySeznamLinek.at(i).c));
        ui->listLinek->addItem( newItem);
    }

}

void MainWindow::NaplnKmenoveLinky(QVector<Linka> docasnySeznamLinek)
{
    ui->listKmenovychLinek->clear();
    for (int i = 0; i < docasnySeznamLinek.length(); ++i)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(QString::number(docasnySeznamLinek.at(i).c));
        newItem->setData(Qt::UserRole, QString::number(docasnySeznamLinek.at(i).c));
        ui->listKmenovychLinek->addItem( newItem);
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

void MainWindow::NaplnVyberTurnusSpoje(QVector<Spoj> docasnySeznamSpoju)
{
    qDebug()<<"MainWindow::NaplnVyberTurnusSpoje";
    if (ui->listTurnusSpoje->count()!=0)
    {
        ui->listTurnusSpoje->clear();
    }
    qDebug()<<"MainWindow::NaplnVyberSpoje_dp1";
    for (int i = 0; i < docasnySeznamSpoju.length(); ++i)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        QString linka=QString::number(docasnySeznamSpoju.at(i).linka.c);
        QString spoj=QString::number(docasnySeznamSpoju.at(i).cisloRopid);

        newItem->setText(linka+"/"+spoj);
        newItem->setData(Qt::UserRole, QString::number(docasnySeznamSpoju.at(i).cisloRopid ));
        ui->listTurnusSpoje->addItem( newItem);
        qDebug()<<"MainWindow::NaplnVyberTurnusSpoje_"<<QString::number(i);
    }
    qDebug()<<"MainWindow::NaplnVyberTurnusSpoje_konec";

}

void MainWindow::NaplnVyberPoradi(QVector<Obeh> docasnySeznamObehu)
{
    qDebug()<<"MainWindow::NaplnVyberPoradi";
    if (ui->listPoradi->count()!=0)
    {
        ui->listPoradi->clear();
    }
   // qDebug()<<"MainWindow::NaplnVyberSpoje_dp1";
    for (int i = 0; i < docasnySeznamObehu.length(); ++i)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(QString::number(docasnySeznamObehu.at(i).p));
        newItem->setData(Qt::UserRole, QString::number(docasnySeznamObehu.at(i).p ));
        ui->listPoradi->addItem( newItem);
        qDebug()<<"MainWindow::NaplnVyberPoradi_"<<QString::number(i);
    }
    qDebug()<<"MainWindow::NaplnVyberPoradi_konec";

}


void MainWindow::AktualizaceDispleje()
{
    qDebug()<<"MainWindow::AktualizaceDispleje()";
    QString textDoPoleAkt="";
    QString casDoPoleAkt="";
    QString textDoPoleNasl="";
    QString textPoleCasuNasl="";
    mojesql.vytvorHlavniAktualni(textDoPoleAkt,casDoPoleAkt,stavSystemu.indexAktZastavky,this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek,stavSystemu.locationState);
    mojesql.vytvorHlavniTextNasledujici(textDoPoleNasl,textPoleCasuNasl,stavSystemu.indexAktZastavky,this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek,stavSystemu.locationState);


    ui->labelAktZastJmeno->setText(textDoPoleAkt);
    ui->labelAktZastCas->setText(casDoPoleAkt);
    ui->prikazovyvysledek->setText(textDoPoleNasl);
    ui->prikazovyvysledek_cas->setText(textPoleCasuNasl);
    ui->label_aktLinka->setText(this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).linka.LineNumber);
    ui->label_aktSpoj->setText(QString::number(this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).spoj.cisloRopid));

    ui->locationStateIndicator->setText(stavSystemu.locationState);


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
    if (stavSystemu.indexAktZastavky<(this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek.count()-1))
    {
        stavSystemu.indexAktZastavky++;
    }
    ui->popisek->setText(QString::number(stavSystemu.indexAktZastavky));
    AktualizaceDispleje();
    xmlHromadnyUpdate();
}

void MainWindow::on_ubratTlacitko_clicked()
{
    qDebug()<<"\n on_ubratTlacitko_clicked \n";
    if (stavSystemu.indexAktZastavky>=2)
    {
        stavSystemu.indexAktZastavky--;
    }
    ui->popisek->setText(QString::number(stavSystemu.indexAktZastavky));
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

    stavSystemu.locationState="BeforeStop";
    xmlHromadnyUpdate();
}

void MainWindow::on_AtStop_2_clicked()
{
    qDebug()<<"";
    //   hlasic.gong();
    // hlasic.vyhlasZastavku2(globalniSeznamZastavek[novatrida.cislo].cisloOis,globalniSeznamZastavek[novatrida.cislo].cisloCis);
    //ui->AtStop_2->setChecked(1);

    priPrijezdu();

}

void MainWindow::on_AfterStop_clicked()
{
    qDebug()<<"";
    stavSystemu.locationState="AfterStop";
    xmlHromadnyUpdate();
}

void MainWindow::on_BetweenStop_clicked()
{
    qDebug()<<"";
    stavSystemu.locationState="BetweenStop";
    xmlHromadnyUpdate();
}

void MainWindow::on_prestupyCheckbox_stateChanged(int arg1)
{
    arg1=1;
    qDebug()<<"MainWindow::on_prestupyCheckbox_stateChanged";
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    arg1=1;
    qDebug()<<"MainWindow::on_checkBox_stateChanged";
    stavSystemu.prestupy= ui->checkBox->checkState();
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
    ibisOvladani.odesliFrontKomplet(this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek,stavSystemu.indexAktZastavky);
    ibisOvladani.odesliSideKomplet(this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek,stavSystemu.indexAktZastavky);
    //ibisOvladani.odesliInnerKomplet(globalniSeznamZastavek,novatrida.cislo);
    ibisOvladani.odesliJKZKomplet(this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek,stavSystemu.indexAktZastavky);
    ibisOvladani.odeslikompletBUSEjednoradekAA(this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek,stavSystemu.indexAktZastavky);
    ibisOvladani.odesliRearKomplet(this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek,stavSystemu.indexAktZastavky);
}


int MainWindow::priPrijezdu()
{
    qDebug()<<"MainWindow::priPrijezdu";

    stavSystemu.doorState="DoorsOpen";


    if (stavSystemu.indexAktZastavky<(this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek.length()-1))
    {
        hlasic.kompletZastavka(this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.cisloCis,this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.cisloOis,this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek[stavSystemu.indexAktZastavky+1].zastavka.cisloCis,this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek[stavSystemu.indexAktZastavky+1].zastavka.cisloOis);
    }
    else
    {
        hlasic.kompletKonecna(this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.cisloCis,this->seznamTripu.at(stavSystemu.indexTripu).globalniSeznamZastavek[stavSystemu.indexAktZastavky].zastavka.cisloOis );
    }
    stavSystemu.locationState="AtStop";
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
    stavSystemu.aktlinka.c=ui->listLinek->currentItem()->data(Qt::UserRole).toString().toInt();
    qDebug()<<"tady budu vypisovat vybrane spoje";
    qDebug()<<"raw "<<ui->listLinek->currentItem()->data(Qt::UserRole)<<" int "<<ui->listLinek->currentItem()->data(Qt::UserRole).toInt();
    if (mojesql.VytvorSeznamSpoju(seznamSpoju,stavSystemu.aktlinka)==1)
    {
        NaplnVyberSpoje(seznamSpoju);
    }
}

void MainWindow::on_listKmenovychLinek_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug()<<"on_listKmenovychLinek_currentItemChanged";
    ui->poleLinkyTurnus->setText(ui->listKmenovychLinek->currentItem()->data(Qt::UserRole ).toString() );

    stavSystemu.aktObeh.kmenovaLinka.c=ui->listKmenovychLinek->currentItem()->data(Qt::UserRole).toInt();

    ui->listPoradi->clear();

    ui->listTurnusSpoje->clear();

    if (mojesql.VytvorSeznamPoradi(seznamObehu,stavSystemu.aktObeh.kmenovaLinka )==1)
    {

        NaplnVyberPoradi(seznamObehu);


    }
}


void MainWindow::on_listPoradi_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug()<<"MainWindow::on_listPoradi_currentItemChanged";
    if (ui->listPoradi->count()!=0)
    {
        if(ui->listPoradi->currentRow()!=-1)
        {
            //ui->listSpoje->setCurrentRow(0);

            qDebug()<<"xx"+ QString::number( ui->listPoradi->currentRow());
            qDebug()<<"current item:"+ui->listPoradi->currentItem()->data(Qt::UserRole).toString();

            //ui->polespoje->setText(ui->listSpoje->currentItem()->data(Qt::UserRole).toString());
            stavSystemu.aktObeh.p=ui->listPoradi->currentItem()->data(Qt::UserRole).toInt() ;

            if (mojesql.VytvorSeznamTurnusSpoju(stavSystemu.aktObeh)==1)
            {
                NaplnVyberTurnusSpoje(stavSystemu.aktObeh.seznamSpoju);

            }


        }

    }
}


void MainWindow::on_listSpoje_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug()<<"MainWindow::on_listSpoje_currentItemChanged";
    if (ui->listSpoje->count()!=0)
    {
        if(ui->listSpoje->currentRow()!=-1)
        {
            //ui->listSpoje->setCurrentRow(0);
            qDebug()<<"xx"+ QString::number( ui->listSpoje->currentRow());
            qDebug()<<"current item:"+ui->listSpoje->currentItem()->data(Qt::UserRole).toString();
            ui->polespoje->setText(ui->listSpoje->currentItem()->data(Qt::UserRole).toString());
            //stavSystemu.aktspoj=ui->listSpoje->currentItem()->data(Qt::UserRole).toInt() ;
            int indexVyberu=ui->listSpoje->currentRow();
            stavSystemu.aktspoj=seznamSpoju.at(indexVyberu);
        }

    }
}

void MainWindow::on_listTurnusSpoje_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug()<<"MainWindow::on_listTurnusSpoje_currentItemChanged";
    if (ui->listTurnusSpoje->count()!=0)
    {
        if(ui->listTurnusSpoje->currentRow()!=-1)
        {
            //ui->listSpoje->setCurrentRow(0);
            qDebug()<<"xx"+ QString::number( ui->listTurnusSpoje->currentRow());
            qDebug()<<"current item:"+ui->listTurnusSpoje->currentItem()->data(Qt::UserRole).toString();
            int zvolenaPolozka=ui->listTurnusSpoje->currentRow();
            qDebug()<<"current row "<<zvolenaPolozka;
            qDebug()<<"delka seznamu spoju"<<stavSystemu.aktObeh.seznamSpoju.size()<<" zvolena polozka "<<zvolenaPolozka;
            stavSystemu.aktspoj=stavSystemu.aktObeh.seznamSpoju.at(zvolenaPolozka);
            ui->poleLinkyTurnus->setText(QString::number(stavSystemu.aktspoj.linka.c));
            //ui->poleSpojeTurnus->setText(ui->listTurnusSpoje->currentItem()->data(Qt::UserRole).toString());
            ui->poleSpojeTurnus->setText(QString::number(stavSystemu.aktspoj.cisloRopid));



        }

    }
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
    seznamTripu.clear();
    seznamLinek.clear();
    seznamSpoju.clear();
    stavSystemu.vymaz();
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

    //vysledek2.append(ui->plainTextEditCustomXml->toPlainText());
    vysledek2=vysledek2+ui->plainTextEditCustomXml->toPlainText().toUtf8();
    //CustomerInformationService.ObnoveniServeru(vysledek2);
    customerInformationService1_0.nastavObsahTela("AllData",vysledek2);
    customerInformationService2_2CZ1_0.nastavObsahTela("AllData",vysledek2);
    for(int i=0;i<customerInformationService1_0.seznamSubscriberu.count();i++ )
    {
        customerInformationService1_0.PostDoDispleje(customerInformationService1_0.seznamSubscriberu[i].adresa,vysledek2);
    }
    qDebug()<<"\n MainWindow::xmlUpdate";
}


void MainWindow::vypisSubscribery(QVector<Subscriber> adresy)
{
    qDebug()<<"MainWindow::vypisSubscribery";
    ui->seznamOdberatelu->setRowCount(0);
    qDebug()<<"smazano"<<" adresy.size="<<adresy.size();
    if (adresy.size()==0)
    {
        qDebug()<<"vracim 0";
        //return 0;
    }
    else
    {
        for (int i = 0;  i < adresy.count(); i++)
        {
            Subscriber odberatel=adresy.at(i);

            qint32 row;
            QTableWidgetItem *cell;
            row = ui->seznamOdberatelu->rowCount();
            ui->seznamOdberatelu->insertRow(row);
            cell = new QTableWidgetItem(odberatel.adresa.toString());
            ui->seznamOdberatelu->setItem(row, 0, cell);


            cell = new QTableWidgetItem(odberatel.struktura);
            ui->seznamOdberatelu->setItem(row, 1, cell);
            ui->seznamOdberatelu->resizeColumnsToContents();
        }
        qDebug()<<"vracim 1";
        //return 1;
    }


}

void MainWindow::vypisSubscribery2(QVector<Subscriber> adresy)
{
    qDebug()<<"MainWindow::vypisSubscribery2";
    //ui->seznamOdberatelu->clear();
    ui->seznamOdberatelu2->setRowCount(0);
    //ui->odberatele_tableView->setRowCount(0);
    qDebug()<<"smazano"<<" adresy.size="<<adresy.size();
    if (adresy.size()==0)
    {
        qDebug()<<"vracim 0";
        //return 0;
    }
    else
    {
        for (int i = 0;  i < adresy.count(); i++)
        {
            //ui->seznamOdberatelu->addItem(adresy.at(i).adresa.toString()+"_"+adresy.at(i).struktura );
            Subscriber odberatel=adresy.at(i);

            qint32 row;
            QTableWidgetItem *cell;
            row = ui->seznamOdberatelu2->rowCount();
            ui->seznamOdberatelu2->insertRow(row);
            cell = new QTableWidgetItem(odberatel.adresa.toString());
            ui->seznamOdberatelu2->setItem(row, 0, cell);


            cell = new QTableWidgetItem(odberatel.struktura);
            ui->seznamOdberatelu2->setItem(row, 1, cell);
            ui->seznamOdberatelu2->resizeColumnsToContents();
            /*
            ui->tabulkaSubscriberu->setItem(row, 2, cell);
            ui->tabulkaSubscriberu->resizeColumnsToContents();

            cell = new QTableWidgetItem(QString::number(port));
            ui->tabulkaSubscriberu->setItem(row, 3, cell);
            ui->tabulkaSubscriberu->resizeColumnsToContents();
            */

        }
        qDebug()<<"vracim 1";
        //return 1;
    }


}





void MainWindow::on_tlacitkoAddsubscriber_clicked()
{
    vypisDiagnostika(customerInformationService1_0.novySubscriber(Subscriber(ui->lineEdit_ipadresaOdberatele->text(),ui->lineEdit_strukturaOdberu->text())));






}


void MainWindow::on_tlacitkoAddsubscriber_2_clicked()
{
    vypisDiagnostika( customerInformationService2_2CZ1_0.novySubscriber(Subscriber(ui->lineEdit_ipadresaOdberatele->text(),ui->lineEdit_strukturaOdberu->text())));
}




void MainWindow::on_tlacitkoRemoveSubscriber_clicked()
{
    if (ui->seznamOdberatelu->rowCount()==0)
    {

        vypisDiagnostika("seznam je prazdny");
        return;
    }

    if (ui->seznamOdberatelu->selectionModel()->selectedIndexes().size()==0)
    {
        vypisDiagnostika("nic neni vybrnao");
        return;
    }
    int indexPolozky = ui->seznamOdberatelu->selectionModel()->selectedIndexes().at(0).row() ;
    if (customerInformationService1_0.odstranitSubscribera(indexPolozky)==1)
    {
        vypisSubscribery(customerInformationService1_0.seznamSubscriberu);
        vypisDiagnostika("odstraneno");
    }
    else
    {

        vypisDiagnostika("nepovedlo se odstranit");
    }






}



void MainWindow::on_tlacitkoRemoveSubscriber_2_clicked()
{
    if (ui->seznamOdberatelu2->rowCount()==0)
    {
        vypisDiagnostika("seznam je prazdny");
        return;
    }

    if (ui->seznamOdberatelu2->selectionModel()->selectedIndexes().size()==0)
    {
        vypisDiagnostika("nic neni vybrano");

        return;
    }
    int indexPolozky = ui->seznamOdberatelu2->selectionModel()->selectedIndexes().at(0).row() ;
    if (customerInformationService2_2CZ1_0.odstranitSubscribera(indexPolozky)==1)
    {

        vypisSubscribery2(customerInformationService2_2CZ1_0.seznamSubscriberu);
        vypisDiagnostika("odstraneno");

    }
    else
    {
        vypisDiagnostika("nepovedlo se odstranit");
    }
}


void MainWindow::on_tlacitkoHlaseniSlozka_clicked()
{
    qDebug()<<"nastavena cesta k hlaseni na "<<ui->lineEditHlaseniCesta->text();
    hlasic.cesta=ui->lineEditHlaseniCesta->text();
}


void MainWindow::vypisDiagnostika(QString vstup)
{
    qDebug()<<"subscribe diag "<<vstup;
    ui->label_diagnostika_manual->clear();
    ui->label_diagnostika_manual->setText(vstup);
}


void MainWindow::vypisSqlVysledek(QString vstup)
{
    ui->label_diagnostika_sql->setText(vstup);
}

void MainWindow::on_tlacitkoTurnus_clicked()
{
    ui->prepinadloStran->setCurrentIndex(4);
}











