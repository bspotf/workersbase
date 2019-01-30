#include "salaryservice.h"
#include "dbservice.h"
#include "../helpers/datetimehelper.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>




SalaryService::SalaryService()
{

}

double SalaryService::getWorkerSalary(int id, int date)
{
    auto worker = this->getWorkerSalaryParams(id);

    double salary = this->countEmployeeSalary(
                worker->baseSalary,
                worker->percentPerYear,
                getYears(date - worker->dateOfEmployment),
                worker->yearIncreasePercentBorder);

    std::vector<int> managedEmployees;

    switch (worker->employeeLevelBonus) {
    case ALL: {
        managedEmployees = getAllManagedEmployees(id);
        break;
    }
    case FIRST:
        managedEmployees = this->getmanagedEmploees(id);
        break;
    case NONE:
    default:
        break;
    }
    for (auto mE : managedEmployees)
    {
        salary += worker->percentForEmployees * this->getWorkerSalary(mE, date);
    }
    return salary;
}

std::shared_ptr<WorkerSalaryParams> SalaryService::getWorkerSalaryParams(int& id)
{
    QSqlQuery employee = DbService::getInstance()->findAndLeftJoin(
                "worker w",
                "w.id = " + QString::number(id),
                "salary_rule sr",
                "w.type_id = sr.worker_type_id",
                "w.id, w.date_of_employment, w.type_id, sr.base_salary,"
                "sr.year_increase, sr.year_increase_percent_border,"
                "sr.employee_percent, sr.employee_level_bonus"
            );


    employee.first();

    WorkerSalaryParams workerSalaryParams(
                    id,
                    employee.value(1).toInt(),
                    employee.value(2).toInt(),
                    employee.value(3).toDouble(),
                    employee.value(4).toDouble(),
                    employee.value(5).toDouble(),
                    employee.value(6).toDouble(),
                    employee.value(7).toInt()
                );

    return std::make_shared<WorkerSalaryParams>(workerSalaryParams);
}

std::vector<int> SalaryService::getmanagedEmploees(int& id)
{
    QSqlQuery managedEmployees = DbService::getInstance()->findAndLeftJoin(
                "worker w",
                "w.id = " + QString::number(id) + " AND r.employee_id NOT NULL",
                "relation r",
                "r.manager_id = w.id",
                "w.id, w.type_id,r.employee_id"
            );

    std::vector<int> employeeIds;

    while(managedEmployees.next())
    {
        employeeIds.push_back(managedEmployees.value(2).toInt());
    }
    return employeeIds;
}

std::vector<int> SalaryService::getAllManagedEmployees(int& id)
{
    std::vector<int> employeeIds = this->getmanagedEmploees(id);
    for (auto e : employeeIds)
    {
       std::vector<int> tmp = this->getAllManagedEmployees(e);
       employeeIds.insert( employeeIds.end(), tmp.begin(), tmp.end());
    }
    return employeeIds;
}

double SalaryService::countEmployeeSalary(
    int baseSalary,
    double percentPerYear,
    int years,
    double yearIncreasePercentBorder)
{
    double yearsOfWorkPercent =
            this->getYearsOfWorkPercent(percentPerYear, years, yearIncreasePercentBorder);
    double total =
            (this->WHOLE_SALARY_PART + yearsOfWorkPercent) * baseSalary;
    return total;
}

double SalaryService::countManagerSalary(double ownSalary, double percentForEmployees)
{

}

double SalaryService::getYearsOfWorkPercent(double percentPerYear, int years, double yearIncreasePercentBorder)
{
    double percentForYears = percentPerYear * years;
    if (percentForYears < yearIncreasePercentBorder)
    {
        return percentForYears;
    }
    return yearIncreasePercentBorder;
}

double SalaryService::countSalaryExpences(int date)
{
    QSqlQuery workers = DbService::getInstance()->execute("SELECT w.id FROM worker w");
    double total;
    while(workers.next())
    {
        total += this->getWorkerSalary(workers.value(0).toInt(), date);
    }
    return total;
}
