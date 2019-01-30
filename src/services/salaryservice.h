#ifndef SALARYSERVICE_H
#define SALARYSERVICE_H

#define WHOLE_SALARY_PART 1

#include "../helpers/workerhelper.h"

#include <QSqlDatabase>
#include <QSqlQuery>

#include <vector>
#include <ctime>

class SalaryService
{
public:

    enum WORKERS {NONE, FIRST, ALL};

    SalaryService();

    /**
     * Returns worker salary including all his employees percentage
     * Hope there is no need to calculate salary after 2038 year
     *
     * @brief getWorkerSalary
     * @param id
     * @param date
     * @return double
     */
    double getWorkerSalary(int id, int64_t date = std::time(0));

    /**
     * Returns addition for years of work
     * not higher than yearIncreasePercentBorder
     *
     * @brief getYearsOfWorkPercent
     * @param percentPerYear
     * @param years
     * @param yearIncreasePercentBorder
     * @return double
     */
    double getYearsOfWorkPercent(double percentPerYear, int years, double yearIncreasePercentBorder);

    /**
     * Counts all salary expences on date
     *
     * @brief countSalaryExpences
     * @param date
     * @return double
     */
    double countSalaryExpences(int64_t date);

private:

    /**
     * Counts salary only for a worker
     * without his employees
     * Base salary + percent per year
     * (not  higher then percentage)
     *
     * @brief countEmployeeSalary
     * @param baseSalary
     * @param percentPerYear
     * @param years
     * @param yearIncreasePercentBorder
     * @param percentForEmployees
     * @return double
     */
    double countEmployeeSalary(
            int baseSalary,
            double percentPerYear,
            int years,
            double yearIncreasePercentBorder);
};

#endif // SALARYSERVICE_H
