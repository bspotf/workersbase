/**
 * DbService class written as Singleton implementation
 * Has all that needed to manipulate with db in this project
 */

#ifndef DBSERVICE_H
#define DBSERVICE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <memory>
#include <QSqlQuery>


class DbService
{
private:

    QSqlDatabase db;
    QSqlQuery query;

    static DbService instance;

    DbService();

public:
    static std::shared_ptr<DbService> getInstance();

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
     * @brief DbService::find
     * @param tableName
     * @param neededColumns
     * @param attributes
     * @return
     */
    QSqlQuery find(QString tableName, QString neededColumns, QString attributes = "");

    /**
     * @brief findAndLeftJoin
     * @param tableName
     * @param attributes
     * @param joinedTable
     * @param joinCondition
     * @param neededColumns
     * @return
     */
    QSqlQuery findAndLeftJoin(
        QString tableName,
        QString attributes,
        QString joinedTable,
        QString joinCondition,
        QString neededColumns = "*"
    );
    /**
     * @brief executes Query
     * @param query
     * @return
     */
    QSqlQuery execute(QString query);
};

#endif // DBSERVICE_H
