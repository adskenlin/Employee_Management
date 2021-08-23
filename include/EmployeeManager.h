// avoid include multiple times
#pragma once
#include <iostream>
using namespace std;
#include "people.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>
#define FILENAME "EmployeeFile.txt"


class EmployeeManager
{
public:

    //construction
    EmployeeManager();

    //menu
    void ShowMenu();

    //quit
    void ExitSystem();

    //number of employees
    int m_peopleNum;

    //pointer of employee array
    People ** m_peopleArray;

    //Add Employee
    void AddPeople();

    //save in file
    void save();

    //check file
    bool m_FileIsEmpty;

    //get number of employees in file
    int get_peopleNum();

    //init array
    void init_peopleArray();

    //show all infomation
    void ShowPeople();

    //check if id exists, if yes, return index, else return -1
    int isExist(int id);

    //delete people
    void DelPeople();

    //deconstruction
    ~EmployeeManager();
};