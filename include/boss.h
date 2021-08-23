#pragma once
#include <iostream>
#include <string>
#include "people.h"

using namespace std;

class Boss :public People
{
public:

    Boss(int id, string name, int deptID);
    // information
    virtual void showInfo();

    virtual string getDeptName();
};