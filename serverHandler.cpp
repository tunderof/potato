#include "serverHandler.h"

QByteArray serverHandler::parse(const QByteArray &array)
{
    QByteArray res = "";
    if(array.contains("stop")) {
        res= "stop";
    }
    if(array.contains("auth")){
        res=login(array);
    }
    if(array.contains("reg")){
        res= "reg";

        QVector<QString> vec = getArgs(array); //просто пример
        for(int i =0; i < vec.size();i++){
            qDebug() << vec[i];
        }
    }
    if(array.contains("task")){
        res="task";
    }
    if(array.contains("check")){
        res="check";
    }
    qDebug()<<"Server result: " + res;
    return res;
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
                //qDebug() << item << " "; вывод вводимых аргументов
            }
        }
        else{
            vectorData.append(data);
            //qDebug() << data; вывод вводимого аргумента
        }
        return vectorData;
    }
    qDebug() << "ERROR in getArgs function";
    vectorData.append("\0");
    return vectorData;
}

QByteArray serverHandler::login(const QByteArray &array){
    QVector<QString> args = getArgs(array);

    QString input_login = args[0];
    QString input_password = args[1];
    qDebug() << input_login << "\t" << input_password;
    //TODO: Добавить хэширование

    QSqlQuery query = DatabaseControl::getInstance()->doSQLQuery(
        "SELECT * FROM User WHERE login = '" + input_login + "' AND password = '" + input_password + "'");
    if (query.next()) {
        return "Valid";
    } else {
        return "ERROR";
    }
}

QByteArray registration(){
    return "Reg";
}

QByteArray sendTask(){
    return "Send Task";
}

QByteArray checkStats(){
    return "Check Stats";
}
