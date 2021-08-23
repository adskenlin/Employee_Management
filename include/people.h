#pragma once
#include <iostream>
#include <string>

using namespace std;

class People
{
public:
    // information
    virtual void showInfo() = 0;

    virtual string getDeptName() = 0;

    // personal ID
    int m_ID;
    // name
    string m_Name;
    // Department ID
    int m_DeptID;

};