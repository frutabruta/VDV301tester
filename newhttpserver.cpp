#include "newhttpserver.h"

NewHttpServer::NewHttpServer(quint16 ppp)
{
    cisloPortu=ppp;
    obsahRoot=vyrobHlavickuOk();
    proved();

}




int NewHttpServer::proved()
{
    qDebug()<<"NewHttpServer::proved()";



    /*QHostAddress test;
test.setAddress("127.0.0.1:47474");*/

    this->route(obsahGet,obsahSubscribe,obsahRoot);
    this->listen();

    return 1;
}
//return app.exec();



int NewHttpServer::route(QString &intObsahGet, QString &intObsahSubscribe, QString &intObsahRoot)
{

    qDebug() <<"NewHttpServer::route";
    httpServer.route("/CustomerInformationService/SubscribeAllData", [this ](const QHttpServerRequest &request)
    {
        //qDebug()<<request.headers()["Connection"].isNull();
        qDebug()<<request.body();
        qDebug()<<"tady se mel spustit emit";

        QString textVysledek="true";
        QString odpoved="";
        odpoved+="<?xml version=\"1.0\" encoding=\"utf-16\"?>";
        odpoved+="<SubscribeResponse xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">";
        odpoved+="<Active><Value>";
        odpoved+=textVysledek;
        odpoved+="</Value></Active>";
        odpoved+="</SubscribeResponse>";
        this->bodyPozadavku=request.body();
        emit zmenaObsahu(request.body());
        //odpoved=this->obsahSubscribe;

        return this->obsahSubscribe;
        //return odpoved;
        //return "Hello world";
    });

    qDebug()<<"vnejsi intObsahGet="<<intObsahGet;
    httpServer.route("/CustomerInformationService/GetAllData", [&intObsahGet](const QHttpServerRequest &request)
    {
        //qDebug()<<request.body();
        return intObsahGet;
    });

    httpServer.route("/", [this](const QHttpServerRequest &request)
    {
        //this->obsahRoot;
        qDebug()<<"request HEAD "<<request.headers();
        qDebug()<<"request BODY "<<request.body();
        emit prijemDat(request.body());
        return this->obsahRoot;
        //return intObsahGet;
    });

    httpServer.afterRequest([](QHttpServerResponse &&resp)
    {
        resp.setHeader("Server", "Super server!");
        resp.setHeader("Content-Type", "text/xml");
        return std::move(resp);
    });
    return 1;
}


int NewHttpServer::listen()
{
    qDebug() <<"NewHttpServer::listen";
    const auto port = httpServer.listen(QHostAddress::Any,cisloPortu);
    if (!port)
    {
        qDebug() << QCoreApplication::translate(
                        "QHttpServerExample", "Server failed to listen on a port.");
        return 0;
    }
    /* automaticky port
     const auto port = httpServer.listen(QHostAddress::Any);
    if (!port) {
        qDebug() << QCoreApplication::translate(
                "QHttpServerExample", "Server failed to listen on a port.");
        return 0;
    }
    */
    qDebug() << QCoreApplication::translate("QHttpServerExample", "Running on http://127.0.0.1:%1/ (Press CTRL+C to quit)").arg(port);
    return 1;
}


void NewHttpServer::zapisDoPromenneGet(QString vstup)
{
    qDebug() <<"NewHttpServer::zapisDoPromenneGet";
    this->obsahGet=vstup;

}

void NewHttpServer::zapisDoSubscribe(QString vstup)
{
    qDebug() << "NewHttpServer::zapisDoSubscribe";
    this->obsahSubscribe=vstup;
}


QString NewHttpServer::vyrobHlavickuOk()
{
    qDebug()<<"HttpSluzba::vyrobHlavicku()";
    QString hlavicka;
    //this->hlavickaInterni="";
    QByteArray argumentXMLserveru = "";
    hlavicka+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    hlavicka+=("Content-Type: application/xml\r\n");
    hlavicka+=("Connection: close\r\n");
    hlavicka+=("Pragma: no-cache\r\n");
    hlavicka+=("\r\n");
    return hlavicka;
}





