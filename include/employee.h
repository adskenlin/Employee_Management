#pragma once
#include <iostream>
#include <string>
#include "people.h"

using namespace std;

class Employee : public People
{
public:

    Employee(int id, string name, int deptID);
    // information
    virtual void showInfo();

    virtual string getDeptName();

};