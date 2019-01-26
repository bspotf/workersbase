#include "dbservice.h"
#include <QSqlError>
#include <QVariant>

DbService::DbService()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE", "Connection");
    this->query = QSqlQuery(this->db);
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

int DbService::insertRow()
{
    this->query.prepare("INSERT INTO test VALUES (null, ?)");
    this->query.addBindValue("Some text");
    if (!this->query.exec()) {
        qDebug("Error occurred inserting.");
        qDebug("%s.", qPrintable(this->db.lastError().text()));
        return -1;
    }
    return 0;
}

int DbService::executeQuery()
{
    this->query.prepare("SELECT * FROM test");
    if (!this->query.exec()) {
        qDebug("Error occurred querying.");
        qDebug("%s.", qPrintable(this->db.lastError().text()));
        return -1;
    }
    while (this->query.next()) {
        qDebug("id = %d, text = %s.", this->query.value(0).toInt(),
               qPrintable(this->query.value(1).toString()));
    }
    return 0;
}
