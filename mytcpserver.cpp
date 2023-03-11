#include "mytcpserver.h"
#include "serverHandler.h"

#include <QDebug>
#include <QCoreApplication>

#define PORT 33333

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
    server_status=0;
}
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, PORT)){
        qDebug() << "server is not started";
    } else {
        server_status=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection(){
    if(server_status==1){
        QTcpSocket *socket = mTcpServer->nextPendingConnection();
        mTcpSockets.append(socket);
        QString message = QString("Hello, World!!! I am echo server!\r\nYou are user № %1\n").arg(mTcpSockets.size() - 1);
        QByteArray data = message.toUtf8();
        socket->write(data);
        connect(socket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
        connect(socket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
    }
}

void MyTcpServer::slotServerRead(){
    QTcpSocket *socket = (QTcpSocket*)sender();
    QByteArray array;
    serverHandler ServerFunc;
    while (socket->bytesAvailable() > 0) // чтение доступных данных
    {
        array = socket->readAll(); //считывание всех байтов
    }
    ServerFunc.parse(array);
    //socket->write(array); // отвечает обратно
}

void MyTcpServer::slotClientDisconnected(){
    QTcpSocket *socket = (QTcpSocket*)sender();
    mTcpSockets.removeOne(socket);
    socket->close();
}
