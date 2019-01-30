#ifndef SALARYSERVICE_H
#define SALARYSERVICE_H


#include <QSqlDatabase>
#include <QSqlQuery>
#include <memory>
#include <vector>
#include <ctime>


struct WorkerSalaryParams{

    int id;
    int dateOfEmployment;
    int workerType;
    double baseSalary;
    double percentPerYear;
    double yearIncreasePercentBorder;
    double percentForEmployees;
    int employeeLevelBonus;

    WorkerSalaryParams(
            int id,
            int dateOfEmployment,
            int workerType,
            double baseSalary,
            double percentPerYear,
            double yearIncreasePercentBorder,
            double percentForEmployees,
            int employeeLevelBonus
        )
    {
        this->id = id;
        this->dateOfEmployment = dateOfEmployment;
        this->workerType = workerType;
        this->baseSalary = baseSalary;
        this->percentPerYear = percentPerYear;
        this->yearIncreasePercentBorder = yearIncreasePercentBorder;
        this->percentForEmployees = percentForEmployees;
        this->employeeLevelBonus = employeeLevelBonus;
    }
};

class SalaryService
{
public:
    const int WHOLE_SALARY_PART = 1;

    enum WORKERS {NONE, FIRST, ALL};

    SalaryService();

    double getWorkerSalary(int id, int date = std::time(0));
    std::shared_ptr<WorkerSalaryParams> getWorkerSalaryParams(int& id);
    std::vector<int> getmanagedEmploees(int& id);
    std::vector<int> getAllManagedEmployees(int& id);
    double countSalaryExpences();
    double getYearsOfWorkPercent(double percentPerYear, int years, double yearIncreasePercentBorder);
    double countSalaryExpences(int date);
private:
    /**
     * @brief Counts salary for a worker
     * Base salary + percent per year
     * (not  higher then percentage)
     * @param baseSalary
     * @param percentPerYear
     * @param years
     * @param yearIncreasePercentBorder
     * @param percentForEmployees
     * @return
     */
    double countEmployeeSalary(
            int baseSalary,
            double percentPerYear,
            int years,
            double yearIncreasePercentBorder);


    double countManagerSalary(double ownSalary, double percentForEmployees);

};

#endif // SALARYSERVICE_H
