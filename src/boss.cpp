#include "boss.h"


Boss::Boss(int id, string name, int deptID)
{
    this->m_ID = id;
    this->m_Name = name;
    this->m_DeptID = deptID;
}

void Boss::showInfo()
{
    cout << "ID: " << this->m_ID
         << "\tName: " << this->m_Name
         << "\tCategory: " << this->getDeptName()
         << "\tJobContent: Leadership" << endl;
}

string Boss::getDeptName()
{
    return string("Boss");
}