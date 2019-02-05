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
    Worker worker(
        NULL,
        ui->lineEditName->text(),
        ui->lineEditPatronimic->text(),
        ui->lineEditSurname->text(),
        static_cast<double>(ui->spinBoxSalary->value()),
        ui->comboBoxType->currentText(),
        ui->lineEditAddress->text(),
        ui->lineEditTelephone->text(),
        ui->dateEditDateOfEmployment->dateTime().toMSecsSinceEpoch()/1000
    );

    if (!this->validateForm())
    {
        ui->labelCheckParams->setText("ERROR: One or more empty params");
        return;
    }

    WorkerHelper::createWorker(worker);

    this->~CreateWorkerForm();
}

/**
 * Simple validator
 *
 * @brief CreateWorkerForm::validateForm
 * @param worker
 * @return
 */
bool CreateWorkerForm::validateForm()
{
    return !(
        ui->lineEditName->text() == ""
        || ui->lineEditPatronimic->text() == ""
        || ui->lineEditSurname->text() == ""
        || ui->comboBoxType->currentText() == ""
        || ui->lineEditTelephone->text() == ""
        || ui->lineEditAddress->text() == ""
        || !ui->spinBoxSalary->value()
    );
}
