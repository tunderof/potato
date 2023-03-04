#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>

#define PORT 33333

MyTcpServer::~MyTcpServer()
{
    //mTcpSocket->close();
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
        socket->write("Hello, World!!! I am echo server!\r\n");
        connect(socket, &QTcpSocket::readyRead, this, [this, socket] { slotServerRead(mTcpSockets.indexOf(socket)); });
        connect(socket, &QTcpSocket::disconnected, this, [this, socket] { slotClientDisconnected(mTcpSockets.indexOf(socket)); });
    }
}

void MyTcpServer::slotServerRead(int clientId){
    QTcpSocket *socket = mTcpSockets.at(clientId);
    while (socket->bytesAvailable() > 0)
    {
        QByteArray array = socket->readAll();
        socket->write(array);
    }
}

void MyTcpServer::slotClientDisconnected(int clientId){
    QTcpSocket *socket = mTcpSockets.takeAt(clientId);
    socket->close();
}
