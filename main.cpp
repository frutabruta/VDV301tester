#include "mainwindow.h"
#include <QApplication>
#include "blabla.h"
#include <QDebug>

//#include "QHT



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    //HelloWorld hello;
    w.show();


    return a.exec();

}
