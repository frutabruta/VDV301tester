#include "mainwindow.h"
#include <QApplication>
//#include "cestaudaje.h"
#include <QDebug>
#include <QTranslator>
#include <QSettings>

//#include "QHT



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    MainWindow w;
    w.show();
    return a.exec();
}
