#include "mainwindow.h"
#include <QApplication>
//#include "cestaudaje.h"
#include <QDebug>
#include <QTranslator>
#include <QSettings>

//#include "QHT


#ifdef Q_OS_ANDROID
#include <QJniObject>
#include <QCoreApplication>

void keepScreenOn(bool enable)
{
    QJniObject activity = QJniObject::callStaticObjectMethod(
        "org/qtproject/qt/android/QtNative",
        "activity",
        "()Landroid/app/Activity;");

    if (!activity.isValid())
        return;

    QJniObject window = activity.callObjectMethod("getWindow", "()Landroid/view/Window;");
    if (!window.isValid())
        return;

    const int FLAG_KEEP_SCREEN_ON = 128; // WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON

    if (enable)
        window.callMethod<void>("addFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
    else
        window.callMethod<void>("clearFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
}
#endif


QString getWritableDirectory()
{
#ifdef Q_OS_ANDROID
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#else
    QString dir = QCoreApplication::applicationDirPath();
#endif
    QDir().mkpath(dir);
    return dir;
}



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
    QString cestaLogu=getWritableDirectory()+"/logfile.log";

    QFile outFile(cestaLogu);
   // outFile.open(QIODevice::WriteOnly | QIODevice::Append);

    outFile.open(QIODevice::WriteOnly);

    QTextStream textStream(&outFile);
    textStream << "log start" << Qt::endl;

    outFile.close();
}



void copyResourceRecursive(QString resourcePath, QString targetPath)
{
    QDir targetDir(targetPath);
    if (!targetDir.exists())
    {
        targetDir.mkpath(".");
    }

    QDir resourceDir(resourcePath);
    QFileInfoList entries = resourceDir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    QFileInfoList::const_iterator it;
    for (it = entries.constBegin(); it != entries.constEnd(); ++it)
    {
        QFileInfo entry = *it;
        QString destPath = targetPath + "/" + entry.fileName();

        if (entry.isDir())
        {
            copyResourceRecursive(entry.filePath(), destPath);
        }
        else
        {
            if (!QFile::exists(destPath))
            {
                QFile::copy(entry.filePath(), destPath);
                QFile::setPermissions(destPath, QFile::ReadOwner | QFile::WriteOwner);
            }
        }
    }
}

void initializeResources()
{
    copyResourceRecursive(":/", getWritableDirectory());
}

/*
void copyResource(QString fileName)
{
    QString dbPath = getWritableDirectory()+"/"+fileName;
    if (!QFile::exists(dbPath))
    {
        QFile::copy(":/"+fileName, dbPath);
        QFile::setPermissions(dbPath, QFile::ReadOwner | QFile::WriteOwner);
    }
}

void initializeResources()
{
    copyResource("data.sqlite");
    copyResource("settings.ini");
    copyResource("announcementList.xml");
}
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser qCommandLineParser;
    qCommandLineParser.addOption(QCommandLineOption("config", "Input file path", "file"));
    qCommandLineParser.process(a.arguments());

    qDebug()<<"main";
    initializeResources();

    #ifdef Q_OS_ANDROID
    keepScreenOn(true);
    #endif

    QString filepath="";

    QString writableDirectory=getWritableDirectory();

    if(!qCommandLineParser.value("config").isEmpty())
    {
        filepath=writableDirectory+"/"+qCommandLineParser.value("config");
    }
    else
    {
        filepath=writableDirectory+"/settings.ini";
    }

    QSettings  qSettings(filepath, QSettings::IniFormat);
    //QSettings*  qSettings= new QSettings(filepath, QSettings::IniFormat);


    //   qSettings->setValue("debug/logToFile",true);
    if(qSettings.value("debug/logToFile").toBool())
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

    MainWindow w(&qSettings,writableDirectory);
    w.show();
    return a.exec();
}
