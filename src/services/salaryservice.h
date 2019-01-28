#ifndef SALARYSERVICE_H
#define SALARYSERVICE_H


#include <QSqlDatabase>
#include <QSqlQuery>

class SalaryService
{
public:
    const int WHOLE_SALARY_PART = 1;
    SalaryService();

    double getWorkersSalary(int id, int date);
    double countSalaryExpences();
    double getYearsOfWorkPercent(double percentPerYear, int years, double yearIncreasePercentBorder);
private:
    double countSalary(
            int baseSalary,
            double percentPerYear,
            int years,
            double yearIncreasePercentBorder,
            double percentForEmployees);
};

#endif // SALARYSERVICE_H
