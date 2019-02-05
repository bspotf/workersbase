#ifndef CREATEWORKERFORM_H
#define CREATEWORKERFORM_H

#include <QWidget>

#include <src/helpers/workerhelper.h>

namespace Ui {
class CreateWorkerForm;
}

class CreateWorkerForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreateWorkerForm(QWidget *parent = 0);
    ~CreateWorkerForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CreateWorkerForm *ui;
    bool validateForm();
};

#endif // CREATEWORKERFORM_H
