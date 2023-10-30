#ifndef TESTODBERUSERVER_H
#define TESTODBERUSERVER_H
#include "vdv301testy.h"
#include "../VDV301publisher/httpservice.h"

class TestOdberuServer : public Vdv301testy
{
    Q_OBJECT

public:
    TestOdberuServer();

    int prubehTestu();
    void inicializujPolozky();
    //void stop();
    void start();

    void slotVypisOdpovedServeru(QNetworkReply *odpoved);
    void slotKrok();

private:

    void startFaze0();
    void startFaze1();
    void startFaze2();
    void startFaze3();
public slots:
    void slotVysledekOdberu(bool vysledek, QString poznamka);
    void slotAktualizaceSubscriberu(QVector<Subscriber> seznamSubscriberuInt);
   // void slotTimeoutFazeVyprsel();
  //  void slotOdpovedNaData(QString status);
signals:
    void signalNastartujSluzbu(bool parametr);
    void signalVymazSeznamOdberatelu();
    void signalZastavCisTimer();
    void signalOdesliDataDoPanelu();
    void signalDalsiKrok();

};

#endif // TESTODBERUSERVER_H
