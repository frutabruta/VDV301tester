#include "myhttpserver.h"
#include <QHostAddress>
#include <QTime>
using namespace std;
/*
int main(int argc, char *argv[])
    {
    QCoreApplication a(argc, argv);
    myHTTPserver server;
    return a.exec();
}
*/




myHTTPserver::myHTTPserver(QObject *parent) : QObject(parent)
{
    qDebug()<< "\n myHTTPserver::myHTTPserver \n";
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()),this, SLOT(myConnection()));
    QHostAddress adresaHttpServeru;
    quint16 cisloPortu=47475;
    adresaHttpServeru.setAddress("127.0.0.1/CustomerInformationService/GetAllData"); ///DeviceManagementService/GetDeviceStatus
    if(!server->listen(adresaHttpServeru,cisloPortu))cout<< "\nWeb server     could not start";
    else cout<<"\nWeb server is waiting for a connection on port 8080";
}

void myHTTPserver::zapisDoPromenne(QByteArray vstup)
{
    this->obsahStrankyDoServeru=vstup;
    qInfo() << "zapisDoPromenne";
}



void myHTTPserver::myConnection()
{
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(txRx()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(closingClient()));
}
void myHTTPserver::txRx()
{
    qDebug()<<"myHTTPserver::txRx";
    char webBrowerRXData[20000];
    qint64 pocetPrijatychBytu=socket->read(webBrowerRXData,20000);
    cout<<"\nreading web browser data\n";
    QString prijato="";
    for(int i=0;i<pocetPrijatychBytu;i++)
    {
        prijato+=webBrowerRXData[i];
    }
    qDebug()<<"obsahPrijato:"<<prijato;
    QStringList prijataDataRozdeleno;
    prijataDataRozdeleno = prijato.split("\r\n\r\n");
    qDebug()<<"\n \n oddelena cast dat: \n \n"<<prijataDataRozdeleno[1];
    prijato=prijataDataRozdeleno[1];
    prijatoZeServeruTelo=prijato;
    qDebug()<<"prijatozeserveru/myHTTPserver::txRx "<<prijato;
    socket->write(obsahStrankyDoServeru);
    socket->disconnectFromHost();
}

void myHTTPserver::closingClient()
{
    qDebug()<<"myHTTPserver::closingClient()";
    emit dataNahrana(1);
    socket->deleteLater();
}

myHTTPserver::~myHTTPserver()
{
    qDebug()<<"myHTTPserver::~myHTTPserver()";
    cout<<"\nclosing socket\n";
    socket->close();
}
