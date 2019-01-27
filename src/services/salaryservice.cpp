#include "salaryservice.h"
#include "dbservice.h"
#include "../helpers/datetimehelper.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <ctime>

SalaryService::SalaryService()
{

}

double SalaryService::getWorkersSalary(int id, int date)
{
    auto dBService = DbService::getInstance();

    QSqlQuery result =
            dBService->findAndLeftJoin(
                " worker w",
                " w.id = " + QString::number(id),
                " salary_rule sr",
                " w.type_id = sr.worker_type_id ",
                " w.id, w.date_of_employment, sr.year_increase,"
                " sr.increase_border_percent, sr.employee_percent,"
                " sr.employee_level_bonus"
            );

    std::time_t dateToGetSlary = std::time(0);
    int time = getYears(dateToGetSlary);///(60*60*24*365);

    while (result.next()) {
        qDebug("id = %d, text = %s.", result.value(0).toInt(),
               qPrintable(result.value(1).toString()));
    }
    auto a = result;
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
    double percentPerYer,
    double percentForEmployees,
    int years)
{
    double total =
            (this->WHOLE_SALARY_PART + percentPerYer*years + percentForEmployees) * baseSalary;
    return total;
}

double SalaryService::countSalaryExpences()
{
}
