#include <QApplication>
#include "./forms/mainwindow.h"
#include "./services/dbservice.h"
#include "./services/salaryservice.h"
#include <memory>

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::shared_ptr<DbService> dBService = DbService::getInstance();
    dBService->closeDatabase();
    dBService->openDatabase();
    (new SalaryService)->getWorkerSalary(6);
    (new SalaryService)->countSalaryExpences(std::time(0));
    QString query = "SELECT * FROM worker";


//    QString query = "SELECT id, name, patronimic FROM worker WHERE id = 1;";
    QSqlQuery result = dBService->execute(query);
    result = dBService->find("worker", "worker.id = 1");
    while (result.next()) {
        qDebug("id = %d, text = %s.", result.value(0).toInt(),
               qPrintable(result.value(1).toString()));
    }

    return 0;

    MainWindow w;
    w.show();

    return a.exec();
}


