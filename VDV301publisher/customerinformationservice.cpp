#include "customerinformationservice.h"
#include "httpsluzba.h"


CustomerInformationService::CustomerInformationService(QString nazevSluzby, QString typSluzby, int cisloPortu,QString verze):HttpSluzba( nazevSluzby,typSluzby, cisloPortu,verze)
{

}
