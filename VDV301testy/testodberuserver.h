#ifndef TESTODBERUSERVER_H
#define TESTODBERUSERVER_H
#include "vdv301testy.h"
#include "../VDV301publisher/httpsluzba.h"

class TestOdberuServer : public Vdv301testy
{
Q_OBJECT
public:
    TestOdberuServer();

    int prubehTestu();
    void inicializujPolozky();
    void stop();
    void start();

public slots:
    void vysledekOdberu(bool vysledek, QString poznamka);
    void slotAktualizaceSubscriberu(QVector<Subscriber> seznamSubscriberuInt);
    void slotTimeoutFazeVyprsel();
    void slotOdpovedNaData(QString status);
signals:
    void nastartujSluzbu(bool parametr);
    void vymazSeznamOdberatelu();
    void zastavCisTimer();
    void odesliDataDoPanelu();

};

#endif // TESTODBERUSERVER_H
