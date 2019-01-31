#include "dbservice.h"
#include <QSqlError>
#include <QVariant>

DbService::DbService()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE", "Connection");
    this->query = QSqlQuery(this->db);
}

std::shared_ptr<DbService> DbService::getInstance()
{
    static DbService instance;
    return std::make_shared<DbService>(instance);
}

int DbService::openDatabase(QString path)
{
    this->db.setDatabaseName(path);
    if (!this->db.open()) {
        qDebug("Error occurred opening the database.");
        qDebug("%s.", qPrintable(this->db.lastError().text()));
        return -1;
    }
    return 0;
}

void DbService::closeDatabase()
{
    this->db.close();
}

int DbService::insertTable(QString tableName, QString attributes)
{
    this->query.prepare("CREATE TABLE IF NOT EXISTS ? (?)");
    this->query.addBindValue(tableName);
    this->query.addBindValue(attributes);
    if (!this->query.exec()) {
        qDebug("Error occurred creating table.");
        qDebug("%s.", qPrintable(this->db.lastError().text()));
        return -1;
    }
    return 0;
}

int DbService::insertRow(QString tableName, QString attributes)
{
    this->query.prepare("INSERT INTO ? VALUES (?)");
    this->query.addBindValue(tableName);
    this->query.addBindValue(attributes);
    if (!this->query.exec()) {
        qDebug("Error occurred inserting.");
        qDebug("%s.", qPrintable(this->query.lastError().text()));
//        qDebug("%s.", qPrintable(this->db.lastError().text()));
        return -1;
    }
    return 0;
}

QSqlQuery DbService::find(QString tableName, QString attributes)
{
    QString query = "SELECT * FROM " + tableName + " WHERE " + attributes;
    return this->execute(query);
}

QSqlQuery DbService::findAndLeftJoin(
    QString tableName,
    QString attributes,
    QString joinedTable,
    QString joinCondition,
    QString neededColumns
)
{
    QString query = "SELECT " + neededColumns + " FROM " + tableName + " LEFT JOIN "
            + joinedTable + " ON " + joinCondition + " WHERE " + attributes;
    return this->execute(query);
}

QSqlQuery DbService::execute(QString query)
{
    this->query.prepare(query);
    if (!this->query.exec()) {
        qDebug("Error occurred querying.");
        qDebug("%s.", qPrintable(this->db.lastError().text()));
    }
    return this->query;
}
