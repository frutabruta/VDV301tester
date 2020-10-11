#include "myhttpserver.h"
#include <QHostAddress>
#include <QTime>
using namespace std;


myHTTPserver::myHTTPserver(quint16 ppp)
{

    qDebug()<<"myHTTPserver::myHTTPserver";
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()),this, SLOT(myConnection()));
    QHostAddress adresaHttpServeru;

    quint16 cisloPortu=47474;
    cisloPortu=ppp;
    adresaHttpServeru.setAddress("127.0.0.1/CustomerInformationService/GetAllData"); ///DeviceManagementService/GetDeviceStatus
    // if(!server->listen(ahoj,47474))cout<< "\nWeb server     could not start";
    //if(!server->listen(adresaHttpServeru,47474))cout<< "\nWeb server     could not start";
    if(!server->listen(adresaHttpServeru,cisloPortu))cout<< "\nWeb server     could not start";
    else cout<<"\nWeb server is waiting for a connection on port "<<cisloPortu ;
    //this->obsah="xx";
}
myHTTPserver::myHTTPserver()
{

    qDebug()<<"myHTTPserver::myHTTPserver";
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()),this, SLOT(myConnection()));
    QHostAddress adresaHttpServeru;
    quint16 cisloPortu=47474;
    adresaHttpServeru.setAddress("127.0.0.1/CustomerInformationService/GetAllData"); ///DeviceManagementService/GetDeviceStatus
    // if(!server->listen(ahoj,47474))cout<< "\nWeb server     could not start";
    //if(!server->listen(adresaHttpServeru,47474))cout<< "\nWeb server     could not start";
    if(!server->listen(adresaHttpServeru,cisloPortu))cout<< "\nWeb server     could not start";
    else cout<<"\nWeb server is waiting for a connection on port "<<cisloPortu ;
    //this->obsah="xx";
}
/*myHTTPserver::myHTTPserver(QObject *parent) : QObject(parent)
{
    qDebug()<<"myHTTPserver::myHTTPserver";
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()),this, SLOT(myConnection()));
    QHostAddress adresaHttpServeru;
    quint16 cisloPortu=47474;
    adresaHttpServeru.setAddress("127.0.0.1/CustomerInformationService/GetAllData"); ///DeviceManagementService/GetDeviceStatus
    // if(!server->listen(ahoj,47474))cout<< "\nWeb server     could not start";
    //if(!server->listen(adresaHttpServeru,47474))cout<< "\nWeb server     could not start";
    if(!server->listen(adresaHttpServeru,cisloPortu))cout<< "\nWeb server     could not start";
    else cout<<"\nWeb server is waiting for a connection on port "<<cisloPortu ;
    //this->obsah="xx";
}*/


void myHTTPserver::zapisDoPromenneGet(QByteArray vstup)
{
    this->obsahGet=vstup;
    qInfo() << "myHTTPserver::zapisDoPromenne";
}

void myHTTPserver::zapisDoSubscribe(QByteArray vstup)
{
    this->obsahSubscribe=vstup;
    qInfo() << "myHTTPserver::zapisDoSubscribe";
}

void myHTTPserver::myConnection()
{
    qDebug()<<"";
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(txRx()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(closingClient()));
}
void myHTTPserver::txRx()
{
    qDebug()<<"myHTTPserver::txRx";
    const int maxPocetBytu=3000;
    char webBrowerRXData[maxPocetBytu];
    qint64 pocetPrijatychBytu=socket->read(webBrowerRXData,maxPocetBytu);
    cout<<"\nreading web browser data\n";
    QString prijataData="";
    for(int i=0;i<pocetPrijatychBytu;i++)
    {
        prijataData+=webBrowerRXData[i];
    }


    if ( prijataData.contains("Get"))
    {
        socket->write(obsahGet);
        qDebug()<<"ano, obsahuje Get";
    }
    else
    {
        if ( prijataData.contains("Subscribe"))
        {
            socket->write(obsahSubscribe);
            qDebug()<<"ano, obsahuje Subscribe";
        }
    }

    qDebug()<< prijataData;
    //cout<<"\n";

    socket->disconnectFromHost();
}

void myHTTPserver::closingClient()
{
    qDebug()<<"myHTTPserver::closingClient";
    socket->deleteLater();
}

myHTTPserver::~myHTTPserver()
{
    qDebug()<<"myHTTPserver::~myHTTPserver";
    cout<<"\nclosing socket\n";
    socket->close();
}
