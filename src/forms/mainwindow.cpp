#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <ctime>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateEditAllSalary->setDateTime(QDateTime::currentDateTime());

    ui->tableWidget->setRowCount(20); // указываем количество строк
        ui->tableWidget->setColumnCount(5); // указываем количество столбцов

        // выделяем память под все ячейки таблицы
        for(int stroka = 0; stroka <   ui->tableWidget->rowCount(); stroka++)
        for(int stolbeu = 0; stolbeu <   ui->tableWidget->columnCount(); stolbeu++)

            ui->tableWidget->setItem(stroka, stolbeu, new QTableWidgetItem());


        // выделяем память под все ячейки таблицы
        for(int stroka = 0; stroka < ui->tableWidget->rowCount(); stroka++)
          for(int stolbeu = 0; stolbeu < ui->tableWidget->columnCount(); stolbeu++)
          {
               QTableWidgetItem *item = new QTableWidgetItem(); // выделяем память под ячейку
               item->setText(QString("%1_%2").arg(stroka).arg(stolbeu)); // вставляем текст

               ui->tableWidget->setItem(stroka, stolbeu, item); // вставляем ячейку
          }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonCountAllSalary_clicked()
{
    int64_t time = ui->dateEditAllSalary->dateTime().toMSecsSinceEpoch()/1000;

    double allSalary = salaryService->countSalaryExpences(time);
    ui->labelAllSalary->setText(QString::number(allSalary, 'f', 2));
}

void MainWindow::on_pushButtonCount_clicked()
{
    int id = 1;
    int64_t time = ui->dateEdit->dateTime().toMSecsSinceEpoch()/1000;

    double allSalary = salaryService->getWorkerSalary(id,time);
    ui->labelWorkerSalary->setText(QString::number(allSalary, 'f', 2));
}

