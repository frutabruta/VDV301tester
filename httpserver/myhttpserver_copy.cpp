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
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()),this, SLOT(myConnection()));
    /*if(!server->listen(QHostAddress::Any,4711))cout<< "\nWeb server     could not start";
    else cout<<"\nWeb server is waiting for a connection on port 8080"; */
    QHostAddress ahoj;
    ahoj.setAddress("127.0.0.1/ahoj");
    if(!server->listen(ahoj,47474))cout<< "\nWeb server     could not start";
    else cout<<"\nWeb server is waiting for a connection on port 8080";
    //this->obsah="xx";
    cout<< "debug421";
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
    {cout<< "debug421";
    char webBrowerRXData[1000];
    int sv=socket->read(webBrowerRXData,1000);
    cout<<"\nreading web browser data\n";
    for(int i=0;i<sv;i++)cout<<webBrowerRXData[i];
    cout<<"\n";
    //QString ahoj = "ahoj";
    socket->write("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    //socket->write("Content-Type: text/html\r\n");
    socket->write("Content-Type: application/xml\r\n");
    socket->write("Connection: close\r\n");
    //socket->write("Refresh: 1\r\n");     //refreshes web browser every second. Require two \r\n.
    socket->write("Pragma: no-cache\r\n");
    socket->write("\r\n");
    /*socket->write("<!DOCTYPE html>\r\n");
    socket->write(" <head> <meta charset=\"UTF-8\"> </head><html><body>Number of seconds since connected.. ");
    socket->write("</body></html>");*/
     socket->write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>  ");
     socket->write("<DeviceManagementService.GetDeviceStatusResponse>");
     socket->write("<DeviceManagementService.GetDeviceStatusResponseData>");
     QDateTime casovaZnacka = QDateTime::currentDateTime();
     QString casnaformatovano= casovaZnacka.toString("yyyy-MM-ddThh:mm:ss");
    // socket->write("<TimeStamp>2014-03-05T12:53:06</TimeStamp>");


      QByteArray  casnaformatovano2;
       casnaformatovano2.append("<TimeStamp>");
      casnaformatovano2.append(casnaformatovano);
        casnaformatovano2.append("</TimeStamp>");
       socket->write(casnaformatovano2);
     socket->write("<DeviceState>running</DeviceState>");
     socket->write("</DeviceManagementService.GetDeviceStatusResponseData>");
     socket->write("</DeviceManagementService.GetDeviceStatusResponse>");

   /* QByteArray str;
    static qint16 count;  //count number to be displayed on web browser
    str.setNum(count++);   //convert int to string
    str="ahoj";
    QByteArray osel;
    osel=this->test;

    socket->write(str); */
    //this->obsah="bb";
    //socket->write(osel);
    //socket->write(this->obsah.));
    socket->disconnectFromHost();
}

void myHTTPserver::closingClient()
    {
        socket->deleteLater();
}

myHTTPserver::~myHTTPserver()
    {
    cout<<"\nclosing socket\n";
    socket->close();
}
