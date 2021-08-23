#pragma once
#include <iostream>
#include <string>
#include "people.h"

using namespace std;

class Manager :public People
{
public:

    Manager(int id, string name, int deptID);
    // information
    virtual void showInfo();

    virtual string getDeptName();
};