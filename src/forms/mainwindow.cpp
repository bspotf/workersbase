#include "mainwindow.h"
#include "createworkerform.h"
#include "ui_mainwindow.h"
#include "./src/helpers/workerhelper.h"

#include <ctime>
#include "QtSql/QSqlDatabase"
#include <QSqlQuery>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateEditAllSalary->setDateTime(QDateTime::currentDateTime());
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

void MainWindow::on_pushButtonFind_clicked()
{
    QString condition = this->getCondition();
    auto query = WorkerHelper::getWorkers(condition);
    std::vector<Worker> workers;
    while(query.next())
    {
        Worker worker(
                    query.value(0).toInt(),
                    query.value(1).toString(),
                    query.value(2).toString(),
                    query.value(3).toString(),
                    query.value(4).toDouble(),
                    query.value(5).toString()
                    );
        workers.push_back(worker);
    }
    this->showTableWidget(workers);
}

QString MainWindow::getCondition(){
    QString condition;
    if (this->ui->textEditId->toPlainText() != "")
    {
        condition += "w.id = " + this->ui->textEditId->toPlainText() + " ";
    }
    if (this->ui->textEditName->toPlainText() != "")
    {
        if (condition != ""){
            condition += "AND ";
        }
        condition += "w.name LIKE \'" + this->ui->textEditName->toPlainText() + "%\' ";
    }
    if (this->ui->textEditPatronimyc->toPlainText() != "")
    {
        if (condition != ""){
            condition += "AND ";
        }
        condition += "w.patronimic LIKE \'" + this->ui->textEditPatronimyc->toPlainText() + "%\' ";
    }
    if (this->ui->textEditSurname->toPlainText() != "")
    {
        if (condition != ""){
            condition += "AND ";
        }
        condition += "w.surname LIKE \'" + this->ui->textEditSurname->toPlainText() + "%\' ";
    }
    return condition;
}

void MainWindow::showTableWidget(std::vector<Worker>& workers)
{

    ui->tableWidget->setRowCount(workers.size());
    ui->tableWidget->setColumnCount(6);

    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Id"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Name"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Patronimic"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Surname"));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Salary"));
    ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Type"));

    for(int row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        setTableItem(row, 0, QString::number(workers[row].id));
        setTableItem(row, 1, workers[row].name);
        setTableItem(row, 2, workers[row].patronimic);
        setTableItem(row, 3, workers[row].surname);
        setTableItem(row, 4, QString::number(workers[row].baseSalary));
        setTableItem(row, 5, workers[row].type);
    }
}

void MainWindow::setTableItem(int row, int column,QString item)
{
    QTableWidgetItem *widgetItem = new QTableWidgetItem();
    widgetItem->setText(item);
    ui->tableWidget->setItem(row, column, widgetItem);
}

void MainWindow::on_pushButtonCreateNew_clicked()
{
    CreateWorkerForm *w = new CreateWorkerForm();
    w->show();
}
