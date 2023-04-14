#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <QByteArray>
#include <QDebug>
#include <QVariant>

#include "databasecontrol.h"

//database
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

class serverHandler
{
public:
    QByteArray parse(const QByteArray &array);
private:
    //QTcpSocket *socket;
    QVector<QString> getArgs(const QByteArray &array);

    QByteArray login(const QByteArray &array);
    QByteArray registration();
    QByteArray sendTask();

    QByteArray checkStats();
    //void sendMessage(const QString &message);//для более понятного кода, вынос функции отправки сообщения я в сессию

};

#endif // SERVERHANDLER_H
