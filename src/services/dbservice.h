#ifndef DBSERVICE_H
#define DBSERVICE_H

#include <QSqlDatabase>
#include <QSqlQuery>

class DbService
{

private:
    QSqlDatabase db;
    QSqlQuery query;
public:
    DbService();
    int openDatabase(QString path = "./database.db3");
    int insertTable(QString tableName, QString attributes);
    int insertRow();
    int executeQuery();
};

#endif // DBSERVICE_H
