#ifndef PRESTUPMPV_H
#define PRESTUPMPV_H

#include <QMainWindow>
#include <QObject>


class prestupMPV
{
public:
    prestupMPV();

    void setLin(int pLin);
    QString stan="";
    QString lin="";
    QString alias="";
    int spoj=0;
    QString smer="";
    QString odj="";
    int zpoz=0;
    bool np=false;
    bool nad=false;
    QString t="";
    int dd=0;
    int smer_c=0;
    bool sled=false;
private:

};

#endif // PRESTUPMPV_H
