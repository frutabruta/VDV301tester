#ifndef CUSTOMERINFORMATIONSERVICE_H
#define CUSTOMERINFORMATIONSERVICE_H


#include "httpsluzba.h"

class CustomerInformationService : public HttpSluzba
{
public:
    explicit CustomerInformationService(QString nazevSluzby, QString typSluzby, int cisloPortu, QString verze);;

signals:

};

#endif // CUSTOMERINFORMATIONSERVICE_H
