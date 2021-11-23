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
    void aktualizaceSubscriberu(QVector<Subscriber> seznamSubscriberuInt);
signals:
    void nastartujSluzbu(bool parametr);
    void vymazSeznamOdberatelu();

};

#endif // TESTODBERUSERVER_H
