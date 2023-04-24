#ifndef MNOZINABODU_H
#define MNOZINABODU_H
#include "mapabod.h"
#include <QString>
#include <QVector>


class MnozinaBodu
{
public:
    MnozinaBodu();
    enum SouradnicovySystem {
        WGS84,
        J_STSK
    };

    QVector<MapaBod> seznamMapaBodu;
    bool vykresliBody=false;
    bool vykresliSpojnici=false;
    bool vykresliTrasu=false;
    SouradnicovySystem souradnicovySystem=MnozinaBodu::WGS84;
};

#endif // MNOZINABODU_H
