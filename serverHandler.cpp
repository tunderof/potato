#include "serverHandler.h"

/*serverHandler::serverHandler(){
qDebug()<<"init";
}

serverHandler::~serverHandler(){
qDebug()<<"close";
}*/
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
    if (parts.size() > 1) {
        QString data = parts.at(1); // data после знака =
        data.chop(1); // удаляется символ \n
        QStringList dataList = data.split("+");
        QVector<QString> vectorData;
        for (int i = 0; i < dataList.size(); i++) {
            QString item = dataList.at(i);
            vectorData.append(item);
        }
        return vectorData;
    }
    qDebug() << "error";
    //TODO: подумать что возвращать в случае ошибки и в случае отсутвия +
}

bool serverHandler::login(const QByteArray &array){
    if(array.contains("auth1")) return true; //TODO: переделать под функцию getArgs
    qDebug() << "auth complite";
    return 0;
}
bool registration(){
    return 0;
}
void checkStats(){

}
bool sendTask(){
    return 0;
}
