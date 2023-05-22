#ifndef MAPABOD_H
#define MAPABOD_H

#include <QString>


class MapaBod
{
public:
    MapaBod();
    QString hlavicka="";
    QString obsah="";
    QString kapka="";
    double lat=0.0;
    double lng=0.0;
    int radius=0;
};

#endif // MAPABOD_H
