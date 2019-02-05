#ifndef WORKERHELPER_H
#define WORKERHELPER_H

#include <QSqlDatabase>
#include <QSqlQuery>

#include <QSqlQuery>
#include <QVariant>

#include "../services/dbservice.h"
#include <memory>
#include <vector>

/**
 * Struct that inludes all params needed for salary count
 *
 * @brief The WorkerSalaryParams struct
 */
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
    ) {
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

struct Worker{
    int id;
    QString name;
    QString patronimic;
    QString surname;
    double baseSalary;
    QString type;
    QString address;
    QString telephone;
    int64_t dateOfEmployment;

    Worker(
       int id,
       QString name,
       QString patronimic,
       QString surname,
       double baseSalary,
       QString type,
       QString address = "",
       QString telephone = "",
       int64_t dateOfEmployment = NULL
    ) {
        this->id = id;
        this->name = name;
        this->patronimic = patronimic;
        this->surname = surname;
        this->baseSalary = baseSalary;
        this->type = type;
        this->address = address;
        this->telephone = telephone;
        this->dateOfEmployment = dateOfEmployment;
    }
};

class WorkerHelper
{
public:
    /**
     * @brief getmanagedEmploees
     * @param id
     * @return std::vector<int>
     */
    static std::vector<int> getmanagedEmploees(int& id)
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

    /**
     * @brief getAllManagedEmployees
     * @param id
     * @return std::vector<int>
     */
    static std::vector<int> getAllManagedEmployees(int& id)
    {
        std::vector<int> employeeIds = WorkerHelper::getmanagedEmploees(id);
        for (auto e : employeeIds)
        {
           std::vector<int> tmp = WorkerHelper::getAllManagedEmployees(e);
           employeeIds.insert( employeeIds.end(), tmp.begin(), tmp.end());
        }
        return employeeIds;
    }

    /**
     * @brief getWorkerSalaryParams
     * @param id
     * @return std::vector<int>
     */
    static std::shared_ptr<WorkerSalaryParams> getWorkerSalaryParams(int& id)
    {
        QSqlQuery employee = DbService::getInstance()->findAndLeftJoin(
                    "worker w",
                    "w.id = " + QString::number(id),
                    "salary_rule sr",
                    "w.type_id = sr.worker_type_id",
                    "w.id, w.date_of_employment, w.type_id, w.base_salary,"
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

    /**
     * @brief getWorkers
     * @param condition
     * @return
     */
    static QSqlQuery getWorkers(QString condition = "w.id NOT NULL")
    {
        condition = (condition != "") ? condition : "w.id NOT NULL";
        auto query = DbService::getInstance()->findAndLeftJoin(
                    "worker w",
                    condition,
                    "worker_type wt",
                    "wt.id = w.type_id",
                    "w.id, w.name, w.patronimic, w.surname, w.base_salary, wt.type as type"
                );
        return query;
    }

    /**
     * @brief createWorkersList
     * @param query
     * @return
     */
    static std::vector<Worker> createWorkersList(QSqlQuery& query){
        std::vector<Worker> workers;
        while(query.next())
        {
            Worker worker(
                        query.value(0).toInt(),
                        query.value(1).toString(),
                        query.value(2).toString(),
                        query.value(3).toString(),
                        query.value(4).toDouble(),
                        query.value(5).toString()
                        );
            workers.push_back(worker);
        }
        return workers;
    }

    /**
     * @brief createWorker
     * @param worker
     */
    static void createWorker(Worker &worker)
    {

        QString values = "\"" + worker.name + "\", \"" + worker.patronimic + "\", \""
                + worker.surname + "\", \"" + worker.address + "\", "
                + QString::number(getTypeIdFromName(worker.type)) + ", " + worker.telephone + ", "
                + QString::number(worker.dateOfEmployment) + ", "
                + QString::number(worker.baseSalary);
        //todo: изменить на вызов dbhelper
        DbService::getInstance()->execute("INSERT INTO worker "
            "(name,patronimic,surname,address,type_id,telephone,date_of_employment, base_salary)"
            " VALUES (" + values + ")");
    }

private:

    /**
     * @brief getTypeIdFromName
     * @param type
     * @return
     */
    static int getTypeIdFromName(QString &type)
    {
        if (type == "Employee") {
            return 1;
        }
        else if (type == "Manager") {
            return 2;
        }
        else if (type == "Sales") {
            return 3;
        }

        return NULL;
    }
};
#endif // WORKERHELPER_H
