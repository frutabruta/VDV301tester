#include "myhttpserver.h"
#include <QHostAddress>
#include <QTime>
using namespace std;

myHTTPserver::myHTTPserver(QObject *parent) : QObject(parent)
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

void myHTTPserver::zapisDoPromenne(QByteArray vstup)
{
    this->obsahStrankyDoServeru=vstup;
    qInfo() << "myHTTPserver::zapisDoPromenne";
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
    const int maxPocetBytu=1000;
    char webBrowerRXData[maxPocetBytu];
    qint64 pocetPrijatychBytu=socket->read(webBrowerRXData,maxPocetBytu);
    cout<<"\nreading web browser data\n";
    QString prijataData="";
    for(int i=0;i<pocetPrijatychBytu;i++)
    {
        prijataData+=webBrowerRXData[i];
    }
    qDebug()<< prijataData;
    //cout<<"\n";
    socket->write(obsahStrankyDoServeru);
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
