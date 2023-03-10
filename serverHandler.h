#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <QByteArray>
#include <QTcpSocket>
#include <QDebug>

class serverHandler
{
public:
    serverHandler(QTcpSocket *socket);
    ~serverHandler();
    void parse(const QByteArray &array);
private:
    QTcpSocket *socket;
    QVector<QString> getArgs(const QByteArray &array);

    bool login(const QByteArray &array);
    bool registration();
    void checkStats();
    bool sendTask();
    void sendMessage(const QString &message);//для более понятного кода, вынос функции отправки сообщения я в сессию

};

#endif // SERVERHANDLER_H
