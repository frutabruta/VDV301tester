#ifndef HLASIC_H
#define HLASIC_H

#include <QObject>
#include <QWidget>
#include <QMediaPlayer>
#include <QFileInfo>

class Hlasic
{
public:
    Hlasic();
    void gong();
    int vyhlasZastavku(int kodOis, int kodCis);
    bool souborExistuje(QString path);
private:
    int vyhlasZastavku2(int kodOis, int kodCis);
};

#endif // HLASIC_H
