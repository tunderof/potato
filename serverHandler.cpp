#include "serverHandler.h"

serverHandler::serverHandler(QTcpSocket *clientSocket){
qDebug()<<"init";
this->socket = clientSocket;
}

serverHandler::~serverHandler(){
qDebug()<<"close";
}

void serverHandler::parse(const QByteArray &array)
{
    if(array.contains("stop")) {
        qDebug() << "stop";
    }
    if(array.contains("auth")){
        qDebug() << "auth";
        login(array);
    }
    if(array.contains("reg")){
        qDebug() << "reg";

        QVector<QString> vec = getArgs(array); //просто пример
        for(int i =0; i < vec.size();i++){
            qDebug() << vec[i];
        }
    }
    if(array.contains("task")){
        qDebug() << "task";
    }
    if(array.contains("check")){
        qDebug() << "check";
    }
}

QVector<QString> serverHandler::getArgs(const QByteArray &array){
    QString str = QString::fromUtf8(array);
    QStringList parts = str.split("=");

    QVector<QString> vectorData;

    if (parts.size() > 1) {
        QString data = parts.at(1); // data после знака =
        data.chop(1); // удаляется символ \n

        if(data.contains("+")){
            QStringList dataList = data.split("+");
            for (int i = 0; i < dataList.size(); i++) {
                QString item = dataList.at(i);
                vectorData.append(item);
                qDebug() << item << " ";
            }
        }
        else{
            vectorData.append(data);
            qDebug() << data;
        }
        return vectorData;
    }
    qDebug() << "ERROR in getArgs function";
    vectorData.append("\0");
    return vectorData;
}

void serverHandler::sendMessage(const QString &message){
    QByteArray data = message.toUtf8();
    socket->write(data);
}

bool serverHandler::login(const QByteArray &array){
    QVector<QString> args = getArgs(array);
    if(args.size() == 2){
        qDebug() << "login: " << args[0] << "\n password:" << args[1];
        sendMessage("Login Success");

        return true;
    }
    return false;
}
bool registration(){
    return 0;
}
void checkStats(){

}
bool sendTask(){
    return 0;
}
