#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <QByteArray>
#include <QTcpSocket>
#include <QDebug>

class serverHandler
{
public:
    //void deploy(QTcpSocket *socket);
    void parse(const QByteArray &array);
private:
    QTcpSocket *socket;
    QVector<QString> getArgs(const QByteArray &array);

    bool login(const QByteArray &array);
    bool registration();
    void checkStats();
    bool sendTask();


    //QList<QTcpSocket *> mTcpSockets;
};

#endif // SERVERHANDLER_H
