#include "ipissender.h"

IpisSender::IpisSender() {}

void IpisSender::sendIpisTelegram(QString input)
{
    if(useKoi8)
    {
        sendTelegram(nahradDiakritikuKoi8Cs(input));
    }
    else
    {
        sendTelegram(nahradDiakritikuKamenicky(input));
    }
}

QString IpisSender::nahradDiakritikuKamenicky(QString vstup)
{
    qDebug() << Q_FUNC_INFO;
    if (vstup.isEmpty())
    {
        return vstup;
    }

    //IPIS kodovani
    vstup.replace("á","<0E><41>"); //chybička zobrazuje D
    vstup.replace("Á","<0E><61>");
    vstup.replace("č","<0E><43>");
    vstup.replace("Č","<0E><63>");
    vstup.replace("ď","<0E><44>");
    vstup.replace("Ď","<0E><64>");
    vstup.replace("é","<0E><57>");
    vstup.replace("É","<0E><77>");
    vstup.replace("ě","<0E><45>");
    vstup.replace("Ě","<0E><65>");
    vstup.replace("í","<0E><49>");
    vstup.replace("Í","<0E><69>");
    vstup.replace("ň","<0E><4E>");
    vstup.replace("Ň","<0E><6E>");
    vstup.replace("ó","<0E><4F>");
    vstup.replace("Ó","<0E><6F>");
    vstup.replace("ř","<0E><52>");
    vstup.replace("Ř","<0E><72>");
    vstup.replace("š","<0E><53>");
    vstup.replace("Š","<0E><73>");
    vstup.replace("ť","<0E><54>");
    vstup.replace("Ť","<0E><74>");
    vstup.replace("ú","<0E><55>");
    vstup.replace("Ú","<0E><75>");
    vstup.replace("ů","<0E><4A>");
    vstup.replace("Ů","<0E><6A>");
    vstup.replace("ý","<0E><59>");
    vstup.replace("Ý","<0E><79>");
    vstup.replace("ž","<0E><5A>");
    vstup.replace("Ž","<0E><7A>");

    return vstup;
}


QString IpisSender::nahradDiakritikuKoi8Cs(QString vstup)
{
    qDebug() << Q_FUNC_INFO;
    if (vstup.isEmpty())
    {
        return vstup;
    }
    //BUSE kodovani

    vstup.replace("á","<0E><20>");
    vstup.replace("Á","<0E><0F>");
    vstup.replace("č","<0E><07>");
    vstup.replace("Č","<0E><00>");
    vstup.replace("ď","<0E><03>");
    vstup.replace("Ď","<0E><05>");
    vstup.replace("é","<0E><02>");
    vstup.replace("É","<0E><10>");
    vstup.replace("ě","<0E><08>");
    vstup.replace("Ě","<0E><09>");
    vstup.replace("í","<0E><21>");
    vstup.replace("Í","<0E><0B>");
    vstup.replace("ň","<0E><24>");
    vstup.replace("Ň","<0E><25>");
    vstup.replace("ó","<0E><22>");
    vstup.replace("Ó","<0E><15>");
    vstup.replace("ř","<0E><29>");
    vstup.replace("Ř","<0E><1E>");
    vstup.replace("š","<0E><28>");
    vstup.replace("Š","<0E><1B>");
    vstup.replace("ť","<0E><1F>");
    vstup.replace("Ť","<0E><06>");
    vstup.replace("ú","<0E><23>");
    vstup.replace("Ú","<0E><17>");
    vstup.replace("ů","<0E><16>");
    vstup.replace("Ů","<0E><26>");
    vstup.replace("ý","<0E><18>");
    vstup.replace("Ý","<0E><1D>");
    vstup.replace("ž","<0E><11>");
    vstup.replace("Ž","<0E><12>");



    return vstup;
}
