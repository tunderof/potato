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
        res= sendTask(array);
    }
    else if(array.contains("check")){
        res = checkStats(array).toUtf8();
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

QString serverHandler::getTaskAnswer(int taskID){
    QString answer;
    QSqlQuery query = DatabaseControl::getInstance()->doSQLQuery(
        "SELECT Answer FROM Tasks WHERE id = '" + QString::number(taskID) + "'");
    if(query.next()){
        answer = query.value(0).toString();
    }
    return answer;
}

QByteArray serverHandler::sendTask(const QByteArray &array){
    QVector<QString> args = getArgs(array);

    int task_id = args[0].toInt();
    int user_id = args[1].toInt();
    QString user_answer = args[2];
    QString answer = getTaskAnswer(task_id);
    bool is_correct = false;
    if (answer == user_answer){
        is_correct = true;
    }

    QSqlQuery query = DatabaseControl::getInstance()->doSQLQuery(
        "INSERT INTO Answers (TaskId, UserId, Answer, IsCorrect) VALUES('" + args[0] + "','" + user_id + "','" + user_answer + "','" + is_correct + "');");
    if (query.next()) {
        return "true";
    } else {
        return "false";
    }
}



QString serverHandler::checkStats(const QByteArray &array){
    QVector<QString> args = getArgs(array);

    int total = 0, correct = 0;

    QString user_id = args[0];

    QSqlQuery query = DatabaseControl::getInstance()->doSQLQuery(
        "SELECT isCorrect FROM Answers WHERE UserId = '" + user_id + "';");
    while (query.next())
        {
            if (query.value(0).toBool()) {
                correct++;
            }
            total++;
        }
    QString result = "Правильных:" + QString::number(correct);
    result += "Из:" + QString::number(total);

    return result;
}
