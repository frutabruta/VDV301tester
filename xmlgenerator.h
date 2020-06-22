#ifndef XMLGENERATOR_H
#define XMLGENERATOR_H

#include <QMainWindow>
#include <QObject>

class xmlGenerator : public QMainWindow
{
    Q_OBJECT
public:
    explicit xmlGenerator(QWidget *parent = nullptr);
    QByteArray AllData();
    QByteArray devStatus();
    QByteArray createTimestamp();
signals:

public slots:
};

#endif // XMLGENERATOR_H
