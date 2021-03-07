#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define MAX_ZAST 100



void on_actionstahnoutXML_triggered();

#include <QMainWindow>
#include "xmlparser.h"
#include "httpserver2/myhttpserver.h"
#include "ibisipsubscriber.h"

class QByteArray;
class QNetworkAccessManager;
class QNetworkReply;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    XmlParser instanceXMLparser;
    //SeznamZastavek* globalniSeznamZastavek = new SeznamZastavek[MAX_ZAST];
    QVector <SeznamZastavek> globalniSeznamZastavek;
    QString nazevLinky = "";
    QString nazevCile="";
    myHTTPserver instanceHttpServeru;
    int indexZastavky=0;
    int pocetZastavek=0;
    int VykresleniPrijatychDat();
    int DoplneniPromennych ();
    int FormatZobrazeni();
    ~MainWindow();

    IbisIpSubscriber CustomerInformationService;
private slots:
    void on_actiontestPolozka_triggered();
    void OnRefreshClicked();
    void OnDataReadyToRead();
    void OnListReadFinished();
    //void OnStoryReadFinished();
    //void on_actionstahnoutXML_triggered();
    void on_refreshTlac_clicked();
    //void on_prepinaciOkno_currentChanged();
   // void on_prepinaciOkno_currentChanged();

public slots:
    void xmlDoPromenne(QString vstupniXml);
private:
    Ui::MainWindow *ui;
    //void BuildWindow();
    //void ReadStory();
    void NetworkCleanup();
   // QWidget * mPanelStories;
    QNetworkAccessManager * mNetMan;
    QNetworkReply * mNetReply;
    QByteArray * mDataBuffer;
    int mCurrStory;
};

#endif // MAINWINDOW_H
