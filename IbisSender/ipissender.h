#ifndef IPISSENDER_H
#define IPISSENDER_H

#include "IbisSender/ibissender.h"

class IpisSender : public IbisSender
{
public:
    IpisSender();
    QString nahradDiakritikuKamenicky(QString vstup);
    void sendIpisTelegram(QString input);
    QString nahradDiakritikuKoi8Cs(QString vstup);

    bool useKoi8=false;
};

#endif // IPISSENDER_H
