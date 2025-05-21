#include "mainwindow.h"
#include <QApplication>
//#include "cestaudaje.h"
#include <QDebug>
#include <QTranslator>
#include <QSettings>

//#include "QHT





void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);



    QString dt = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    QString txt = QString("[%1] ").arg(dt);

    // txt += QString("{Critical} \t %1").arg(msg);
    if(type==QtDebugMsg){txt += QString("{Debug} \t\t %1").arg(msg);};
    if(type==QtWarningMsg){  txt += QString("{Warning} \t %1").arg(msg);};
    if(type==QtCriticalMsg){txt += QString("{Critical} \t %1").arg(msg);};
    if(type==QtFatalMsg)
    {
        txt += QString("{Fatal} \t\t %1").arg(msg);
        abort();
    };

    QString cestaLogu=QCoreApplication::applicationDirPath()+"/logfile.log";

    QFile outFile(cestaLogu);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);

    // outFile.open(QIODevice::WriteOnly);

    QTextStream textStream(&outFile);
    textStream << txt << Qt::endl;

    outFile.close();
}


void createEmptyFile()
{


    QString cestaLogu=QCoreApplication::applicationDirPath()+"/logfile.log";

    QFile outFile(cestaLogu);
   // outFile.open(QIODevice::WriteOnly | QIODevice::Append);

    outFile.open(QIODevice::WriteOnly);

    QTextStream textStream(&outFile);
    textStream << "log start" << Qt::endl;

    outFile.close();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);





    QCommandLineParser qCommandLineParser;
    qCommandLineParser.addOption(QCommandLineOption("config", "Input file path", "file"));
    qCommandLineParser.process(a.arguments());


    QString filepath="";
    //QApplication::applicationDirPath()+"/settings.ini";

    if(!qCommandLineParser.value("config").isEmpty())
    {
        filepath=QCoreApplication::applicationDirPath()+"/"+qCommandLineParser.value("config");
    }
    else
    {
        filepath=QCoreApplication::applicationDirPath()+"/settings.ini";
    }

    QSettings*  qSettings= new QSettings(filepath, QSettings::IniFormat);


    //   qSettings->setValue("debug/logToFile",true);
    if(qSettings->value("debug/logToFile").toBool())
    {
        createEmptyFile();
        qInstallMessageHandler(customMessageHandler);
    }

    /*
    qCommandLineParser.addPositionalArgument("file", QCoreApplication::translate("main", "The file to open."));
    qCommandLineParser.process(a);

    QStringList filename=qCommandLineParser.positionalArguments();

    if(filename.isEmpty())
    {
        filename.append("");
    }
*/



    MainWindow w(qSettings,filepath);
    w.show();
    return a.exec();
}
