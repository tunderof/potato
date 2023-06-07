#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QSqlDatabase>

class MyTcpServer : public QObject
{
    Q_OBJECT
private:
    MyTcpServer(QObject *parent = nullptr);
    static MyTcpServer* instance;
    QSqlDatabase db;
public:
    ~MyTcpServer();
    static MyTcpServer* getInstance();
public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();
private:
    QTcpServer *mTcpServer;
    QList<QTcpSocket *> mTcpSockets;
    int server_status;
};

#endif // MYTCPSERVER_H
