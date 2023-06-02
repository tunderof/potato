#include "serverHandler.h"

#include <QCryptographicHash>

QByteArray serverHandler::parse(const QByteArray &array)
{
    QByteArray res = "";
    if(array.contains("stop")) {
        res= "stop";
    }
    else if(array.contains("auth")){
        res = login(array);
    }
    else if(array.contains("reg")){
        res= registration(array);
    }
    else if(array.contains("task")){
        res="task";
    }
    else if(array.contains("check")){
        res="check";
    }
    else{
        res="Wrong command";
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
    QString hashed_pass = QString(QCryptographicHash::hash((input_password.toUtf8()),QCryptographicHash::Md5).toHex());
    qDebug() << input_login << "\t" << hashed_pass;

    QSqlQuery query = DatabaseControl::getInstance()->doSQLQuery(
        "SELECT * FROM Users WHERE login = '" + input_login + "' AND password = '" + hashed_pass + "'");
    if (query.next()) {
        return "true";
    } else {
        return "false";
    }
}

QByteArray serverHandler::registration(const QByteArray &array){
    QVector<QString> args = getArgs(array);

    QString input_login = args[0];
    QString input_password = args[1];
    QString hashed_pass = QString(QCryptographicHash::hash((input_password.toUtf8()),QCryptographicHash::Md5).toHex());

    QSqlQuery query = DatabaseControl::getInstance()->doSQLQuery(
        "INSERT INTO Users (login, password) VALUES('" + input_login + "','" + hashed_pass + "')");
    if (query.next()) {
        return "true";
    } else {
        return "false";
    }
}

QByteArray sendTask(){
    return "Send Task";
}

QByteArray checkStats(){
    return "Check Stats";
}
