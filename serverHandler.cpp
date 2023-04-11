#include "serverHandler.h"

serverHandler::serverHandler(QTcpSocket *clientSocket){
qDebug()<<"init socket";
this->socket = clientSocket;
}

serverHandler::~serverHandler(){
qDebug()<<"close socket";
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

void serverHandler::sendMessage(const QString &message){
    QByteArray data = message.toUtf8();
    socket->write(data);
}

bool serverHandler::login(const QByteArray &array){
    QVector<QString> args = getArgs(array);

    QSqlDatabase::removeDatabase("qt_sql_default_connection"); //разрыв прошлых соединений
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Test");

    if (!db.open()) {
        qDebug() << "ERROR database connection";
        return -1;
    }

    QString input_login = args[0];
    QString input_password = args[1];

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM User WHERE login = :login AND password = :password");
    query.bindValue(":login", input_login);
    query.bindValue(":password", input_password);

    if(query.exec()) {
        db.close();
        if(query.next()) {
            int count = query.value(0).toInt();
            if (count == 1) {
                sendMessage("Login Success\n");
                return true;
            }
        }
    }

    db.close();
    qDebug() << "ERROR Incorrect credentials";
    sendMessage("Incorrect credentials\n");
    return false;
}

bool registration(){
    return false;
}

bool sendTask(){
    return false;
}

void checkStats(){

}
