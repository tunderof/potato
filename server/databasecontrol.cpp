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
    query->exec("CREATE TABLE Users(id integer not null primary key, login TEXT, password TEXT);");

    query->prepare("INSERT INTO users (Login, Password) VALUES(:Login, :Password)");
    query->bindValue(":Login", "admin");
    query->bindValue(":Password", "202cb962ac59075b964b07152d234b70");
    query->exec();*/
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

