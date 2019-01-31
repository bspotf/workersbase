#include "createworkerform.h"
#include "ui_createworkerform.h"
#include "./src/services/dbservice.h"

CreateWorkerForm::CreateWorkerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateWorkerForm)
{
    ui->setupUi(this);
    ui->dateEditDateOfEmployment->setDateTime(QDateTime::currentDateTime());

                ui->comboBoxType->insertItem(1,"Employee");
                ui->comboBoxType->insertItem(2,"Manager");
                ui->comboBoxType->insertItem(3,"Sales");

}

CreateWorkerForm::~CreateWorkerForm()
{
    delete ui;
}

void CreateWorkerForm::on_pushButton_clicked()
{
    QString name = ui->lineEditName->text();
    QString patronimic = ui->lineEditPatronimic->text();
    QString surname = ui->lineEditSurname->text();
    int type = ui->comboBoxType->currentIndex() + 1;
    QString telephone = ui->lineEditTelephone->text();
    QString address = ui->lineEditAddress->text();
    double baseSalary = ui->spinBoxSalary->value();
    int64_t dateOfEmployment = ui->dateEditDateOfEmployment->dateTime().toMSecsSinceEpoch()/1000;

    if (name == "" || patronimic == "" || surname == ""
            || !type || telephone == "" || address == "" || !baseSalary)
    {
        ui->labelCheckParams->setText("ERROR:Check parameters");
        return;
    }

    QString values = "\"" + name + "\", \"" + patronimic + "\", \""
            + surname + "\", \"" + address + "\", "
            + QString::number(type) + ", " + telephone + ", "
            + QString::number(dateOfEmployment) + ", "
            + QString::number(baseSalary);

    //костыль, есть риск получить инъекцию, так делать не нужно)
    DbService::getInstance()->execute("INSERT INTO worker "
        "(name,patronimic,surname,address,type_id,telephone,date_of_employment, base_salary)"
        " VALUES (" + values + ")");

    this->~CreateWorkerForm();
}
