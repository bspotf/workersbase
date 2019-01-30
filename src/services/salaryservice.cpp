#include "salaryservice.h"
#include "../helpers/datetimehelper.h"

SalaryService::SalaryService()
{

}

double SalaryService::getWorkerSalary(int id, int date)
{
    auto worker = WorkerHelper::getWorkerSalaryParams(id);

    double salary = this->countEmployeeSalary(
                worker->baseSalary,
                worker->percentPerYear,
                getYears(date - worker->dateOfEmployment),
                worker->yearIncreasePercentBorder);

    std::vector<int> managedEmployees;

    switch (worker->employeeLevelBonus) {
    case ALL: {
        managedEmployees = WorkerHelper::getAllManagedEmployees(id);
        break;
    }
    case FIRST:
        managedEmployees = WorkerHelper::getmanagedEmploees(id);
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

double SalaryService::countEmployeeSalary(
    int baseSalary,
    double percentPerYear,
    int years,
    double yearIncreasePercentBorder)
{
    double yearsOfWorkPercent = this->getYearsOfWorkPercent(
                percentPerYear,
                years,
                yearIncreasePercentBorder);
    double total = (this->WHOLE_SALARY_PART + yearsOfWorkPercent) * baseSalary;
    return total;
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
