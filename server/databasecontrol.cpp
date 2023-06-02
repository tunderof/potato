#include "databasecontrol.h"

#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#define _DB_NAME "potato.db"

DatabaseControl::DatabaseControl()
{
    this->dbInstance = QSqlDatabase::addDatabase("QSQLITE");
    this->dbInstance.setDatabaseName(_DB_NAME);
    if (!this->dbInstance.open()) {
        qDebug() << this->dbInstance.lastError().text();
    };
    /*QSqlQuery *query = new QSqlQuery(this->dbInstance);
    query->exec("CREATE TABLE Users(id integer not null primary key AUTOINCREMENT, login TEXT, password TEXT);");
    query->exec("CREATE TABLE Tasks(id integer not null primary key AUTOINCREMENT, Name TEXT, Description TEXT, Answer TEXT);");
    query->exec("CREATE TABLE Answers(id integer not null primary key AUTOINCREMENT, TaskId INTEGER, UserId INTEGER, Answer TEXT, IsCorrect BOOLEAN);");

    query->exec("INSERT INTO Tasks (Name, Description, Answer) VALUES ('Task 1', 'Task 1', '1');");
    */
}

DatabaseControl::~DatabaseControl() {
    this->dbInstance.close();
}

QSqlQuery DatabaseControl::doSQLQuery(QString stringQuery) {
    QSqlQuery query(this->dbInstance);
    if(!query.exec(stringQuery)) {
        qDebug() << "Error SQL query:" << query.lastError().text();
    }
    return query;
}

DatabaseDestroyer DatabaseControl::destroyer; // под вопросом

DatabaseControl* DatabaseControl::pInstance = nullptr;
QSqlDatabase DatabaseControl::dbInstance;

