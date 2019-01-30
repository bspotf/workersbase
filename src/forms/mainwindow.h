#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./src/services/salaryservice.h"

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
