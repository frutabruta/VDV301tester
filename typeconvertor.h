#ifndef TYPECONVERTOR_H
#define TYPECONVERTOR_H

#include <QObject>
#include "VDV301publisher/VDV301DataStructures/connection.h"
#include "GolemioClient/connectiongolemio.h"
#include "GolemioClient/connectiongolemiov4.h"

class TypeConvertor
{
public:
    TypeConvertor();
    static Connection connectionGolemioToConnection(ConnectionGolemio input);
    static QDateTime minutesToTimestamp(QDateTime referenceDateTime, QString minutesString);
    QVector<Connection> ConnectionGolemioV4ListToConnectionList(QVector<ConnectionGolemioV4> inputList);
};

#endif // TYPECONVERTOR_H
