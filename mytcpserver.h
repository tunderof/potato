#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket> // для создания 1 подключения

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

class MyTcpServer : public QObject
{
    Q_OBJECT // чето тут наследуется
public:
    explicit MyTcpServer(QObject *parent = nullptr); // должна вызвать вопросы, берутся константы из QT, можно использовать только опредленный тип объекта
    ~MyTcpServer();
public slots: // обработчики событий
    //clientId - пользователь
    void slotNewConnection();

    void slotClientDisconnected(int clientId);

    void slotServerRead(int clientId);
private:
    QTcpServer * mTcpServer;
    QList<QTcpSocket *> mTcpSockets;
    int server_status;
};
#endif // MYTCPSERVER_H
