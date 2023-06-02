#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <QByteArray>
#include <QDebug>

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
    QByteArray registration(const QByteArray &array);
    QByteArray sendTask(const QByteArray &array);

    QString checkStats(const QByteArray &array);
    QString getTaskAnswer(int taskID);
    //void sendMessage(const QString &message);//для более понятного кода, вынос функции отправки сообщения я в сессию

};

#endif // SERVERHANDLER_H
