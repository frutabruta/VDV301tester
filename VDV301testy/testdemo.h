#ifndef TESTDEMO_H
#define TESTDEMO_H
#include <QTimer>
#include "vdv301testy.h"
class TestDemo : public Vdv301testy
{
Q_OBJECT
public:
       TestDemo();
     QTimer *timer = new QTimer(this);

     void start();
     void stop();
     void inicializujPolozky();
     void prubehTestu();

private:

public slots:

     void slotCasovacVyprsel();
private slots:

};

#endif // TESTDEMO_H
