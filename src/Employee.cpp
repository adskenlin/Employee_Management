#include "employee.h"

Employee::Employee(int id, string name, int deptID)
{
    this->m_ID = id;
    this->m_Name = name;
    this->m_DeptID = deptID;
}

void Employee::showInfo()
{
    cout << "ID: " << this->m_ID
         << "\tName: " << this->m_Name
         << "\tCategory: " << this->getDeptName()
         << "\tJobContent: Normal work" << endl;
}

string Employee::getDeptName()
{
    return string("Staff");
}