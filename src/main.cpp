#include <QApplication>
#include "./forms/mainwindow.h"
#include "./services/dbservice.h"
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::shared_ptr<DbService> dBService = std::shared_ptr<DbService>(new DbService);
    dBService->openDatabase();

    MainWindow w;
    w.show();

    return a.exec();
}
