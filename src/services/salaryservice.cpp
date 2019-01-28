#include "salaryservice.h"
#include "dbservice.h"
#include "../helpers/datetimehelper.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>


SalaryService::SalaryService()
{

}

double SalaryService::getWorkersSalary(int id, int date)
{
    auto dBService = DbService::getInstance();

    QSqlQuery result =
            dBService->findAndLeftJoin(
                "worker w",
                "w.id = " + QString::number(id),
                "salary_rule sr",
                "w.type_id = sr.worker_type_id",
                "w.id, w.date_of_employment, sr.base_salary,"
                "sr.year_increase, sr.year_increase_percent_border,"
                "sr.employee_percent, sr.employee_level_bonus"
            );

//    while (result.first()) {
//        qDebug("id = %d, text = %s.", result.value(1).toInt(),
//               qPrintable(result.value(2).toString()));
//    }
    result.first();
    int dateOfEmployment = result.value(1).toInt();
    double baseSalary = result.value(2).toDouble();
    double percentPerYear = result.value(3).toDouble();
    double yearIncreasePercentBorder = result.value(4).toDouble();
    double percentForEmployees = result.value(5).toDouble();
    double employeeLevelBonus = result.value(6).toDouble();

    if (date < dateOfEmployment) {
        return 0;
    }
    int years = getYears(date - dateOfEmployment);

    double salary = this->countSalary(
                baseSalary,
                percentPerYear,
                years,
                yearIncreasePercentBorder,
                percentForEmployees);
    return salary;
//    auto a = result;
// return a;
}

/**
 * @brief Counts salary for a worker
 * Base salary + percent per year
 * (not  higher then percentage)
 * + percentage of low leveled managed employees.
 * @param baseSalary
 * @param percentPerYer
 * @param percentForEmployees
 * @param years
 * @return
 */
double SalaryService::countSalary(
    int baseSalary,
    double percentPerYear,
    int years,
    double yearIncreasePercentBorder,
    double percentForEmployees)
{
    double yearsOfWorkPercent =
            this->getYearsOfWorkPercent(percentPerYear, years, yearIncreasePercentBorder);

    double total =
            (this->WHOLE_SALARY_PART + yearsOfWorkPercent + percentForEmployees) * baseSalary;
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

double SalaryService::countSalaryExpences()
{

}
