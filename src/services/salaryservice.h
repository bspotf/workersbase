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
private:
    double countSalary(int baseSalary,
                       double percentPerYer,
                       double percentForEmployees,
                       int years);
};

#endif // SALARYSERVICE_H
