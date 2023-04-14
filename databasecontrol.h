#ifndef DATABASECONTROL_H
#define DATABASECONTROL_H

#include <QSqlDatabase>

class DatabaseControl;

class DatabaseDestroyer
{
    private:
        DatabaseControl * pInstance;
    public:
        ~DatabaseDestroyer() {
            delete this->pInstance;
        }
        void initialize(DatabaseControl * p) {
            this->pInstance = p;
        }
};


class DatabaseControl
{
    private:
        static DatabaseControl * pInstance;
        void initDB();
        static QSqlDatabase dbInstance;
        static DatabaseDestroyer destroyer;
    protected:
        DatabaseControl();
        DatabaseControl(const DatabaseControl& ) = delete;
        DatabaseControl& operator = (DatabaseControl &)=delete;
        ~DatabaseControl();
        friend class DatabaseDestroyer;
    public:
        static DatabaseControl* getInstance() {
            if (!pInstance)
            {
                pInstance = new DatabaseControl();
                destroyer.initialize(pInstance);
            }
            return pInstance;
        }
        QSqlQuery doSQLQuery(QString stringQuery);

};

#endif // DATABASECONTROL_H
