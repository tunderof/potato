#include <QCoreApplication>
#include <QVariant>
#include <QDebug>

//database

#include "mytcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer *server = MyTcpServer::getInstance();

    return a.exec();
}
