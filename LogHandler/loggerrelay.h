#ifndef LOGGERRELAY_H
#define LOGGERRELAY_H


#include <QObject>
#include <QString>

class LoggerRelay : public QObject
{
    Q_OBJECT

public:
    explicit LoggerRelay(QObject *parent = nullptr);

signals:
    void message(const QString &text);
};


#endif // LOGGERRELAY_H
