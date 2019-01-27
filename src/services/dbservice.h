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

    /**
     * @brief Opens the database, if not return -1
     * @param path
     * @return int
     */
    int openDatabase(QString path = "./database.db3");

    /**
     * @brief wrapper closes the database
     * @return
     */
    void closeDatabase();

    /**
     * @brief inserts new table into the database
     * @param tableName
     * @param attributes
     * @return
     */
    int insertTable(QString tableName, QString attributes);

    /**
     * @brief inserts a row into a table
     * @param tableName
     * @param attributes
     * @return
     */
    int insertRow(QString tableName, QString attributes);

    /**
     * @brief executes Query
     * @param query
     * @return
     */
    int execute(QString query);
};

#endif // DBSERVICE_H
