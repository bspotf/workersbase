#ifndef SEARCHHELPER_H
#define SEARCHHELPER_H

#include <QString>

class SearchHelper
{
public:
    static QString getSearchCondition(
            QString id,
            QString name,
            QString lastname,
            QString surname)
    {
        QString condition;
        if (id != "")
        {
            condition += "w.id = " + id + " ";
        }
        if (name != "")
        {
            if (condition != ""){
                condition += "AND ";
            }
            condition += "w.name LIKE \'" + name + "%\' ";
        }
        if (lastname != "")
        {
            if (condition != ""){
                condition += "AND ";
            }
            condition += "w.patronimic LIKE \'" + lastname + "%\' ";
        }
        if (surname != "")
        {
            if (condition != ""){
                condition += "AND ";
            }
            condition += "w.surname LIKE \'" + surname + "%\' ";
        }
        return condition;
    }

    static QString getManagedWorkersCondition(int &managerId)
    {
        auto employees = WorkerHelper::getmanagedEmploees(managerId);
        QString condition = "w.id in (";
        for (int i = 1, sz = employees.size(); i <= employees.size(); i++)
        {
            condition += QString::number(employees[i-1]);
            if (i !=sz){
                condition += ",";
            }
        }
        condition += ")";
        return condition;
    }
};
#endif // SEARCHHELPER_H
