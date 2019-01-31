#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./src/services/salaryservice.h"
#include "./src/services/dbservice.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SalaryService *salaryService;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonCountAllSalary_clicked();

    void on_pushButtonCount_clicked();

    void on_pushButtonFind_clicked();

    void on_pushButtonCreateNew_clicked();

    void on_pushButtonSeeWorkers_clicked();

private:

    std::vector<Worker> createWorkersList(QSqlQuery& query);
    void showTableWidget(std::vector<Worker>& workers);
    QString getCondition();
    void setTableItem(int row, int column,QString item);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
