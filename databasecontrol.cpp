#include "databasecontrol.h"

#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#define _DB_NAME "Test"

DatabaseControl::DatabaseControl()
{
    this->dbInstance = QSqlDatabase::addDatabase("QSQLITE");
    this->dbInstance.setDatabaseName(_DB_NAME);
    if (!this->dbInstance.open()) {
        qDebug() << this->dbInstance.lastError().text();
    };
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

DatabaseDestroyer DatabaseControl::destroyer;

DatabaseControl* DatabaseControl::pInstance = nullptr;
QSqlDatabase DatabaseControl::dbInstance;

