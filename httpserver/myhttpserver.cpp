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




myHTTPserver::myHTTPserver(const int port,QObject *parent) : QObject(parent)
    {
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()),this, SLOT(myConnection()));
    /*if(!server->listen(QHostAddress::Any,4711))cout<< "\nWeb server     could not start";
    else cout<<"\nWeb server is waiting for a connection on port 8080"; */
    QHostAddress ahoj;
    ahoj.setAddress("127.0.0.1/ahoj");
    // if(!server->listen(ahoj,47474))cout<< "\nWeb server     could not start";
    if(!server->listen(ahoj,port))cout<< "\nWeb server     could not start";
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
    socket->write(obsahStrankyDoServeru);
     /*

     QByteArray pozadavek ="";
     QByteArray hlavicka="";
     QByteArray telo="";
     QByteArray deviceState="running";
     QByteArray TgetDeviceStatusResponse="";
     QByteArray TgetDeviceStatusResponseData="";
     QByteArray TtimeStamp="";
     QByteArray TdeviceState="";

    deviceState=test;

      QDateTime casovaZnacka = QDateTime::currentDateTime();
      QString casnaformatovanoString= casovaZnacka.toString("yyyy-MM-ddThh:mm:ss");



     TtimeStamp+="<TimeStamp>"+casnaformatovanoString+"</TimeStamp>";
     TdeviceState+="<DeviceState>"+deviceState+"</DeviceState>";
     TgetDeviceStatusResponseData+="<DeviceManagementService.GetDeviceStatusResponseData>"+TtimeStamp+TdeviceState+"</DeviceManagementService.GetDeviceStatusResponseData>";
     TgetDeviceStatusResponse+="<DeviceManagementService.GetDeviceStatusResponse>"+TgetDeviceStatusResponseData+"</DeviceManagementService.GetDeviceStatusResponse>";


     hlavicka+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
     hlavicka+=("Content-Type: application/xml\r\n");
     hlavicka+=("Connection: close\r\n");
     hlavicka+=("Pragma: no-cache\r\n");
     hlavicka+=("\r\n");

     telo+=("<?xml version=\"1.0\" encoding=\"UTF-8\"?>  ")+TgetDeviceStatusResponse;




       pozadavek=hlavicka+telo;





        socket->write(pozadavek);
         */
   /*
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
