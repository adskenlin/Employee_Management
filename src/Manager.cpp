#include "manager.h"

Manager::Manager(int id, string name, int deptID)
{
    this->m_ID = id;
    this->m_Name = name;
    this->m_DeptID = deptID;
}

void Manager::showInfo()
{
    cout << "ID: " << this->m_ID
         << "\tName: " << this->m_Name
         << "\tCategory: " << this->getDeptName()
         << "\tJobContent: Project Management" << endl;
}

string Manager::getDeptName()
{
    return string("Manager");
}