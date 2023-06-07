#include <QCoreApplication>
#include <QTest>

#include "mytcpserver.h"
#include "unitTests.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer *server = MyTcpServer::getInstance();

    QTest::qExec(new TestFunctions, argc, argv);

    return a.exec();
}
