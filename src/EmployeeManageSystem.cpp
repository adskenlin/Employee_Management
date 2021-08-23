#include <iostream>
#include "EmployeeManager.h"
using namespace std;

int main()
{
    //test
    // People * emp = new Employee(1, "Paul", 0);
    // emp->showInfo();
    // delete emp;

    // People * manager = new Manager(2, "Rahm", 1);
    // manager->showInfo();
    // delete manager;

    // People * boss = new Boss(3, "Bill", 2);
    // boss->showInfo();
    // delete boss;
    // create object
    EmployeeManager EM;

    int choice = 0;

    while (true)
    {
        EM.ShowMenu();
        cout << "Please Enter the option number: " << endl;
        cin >> choice;

        switch(choice)
        {
            case 0:
                EM.ExitSystem();
            case 1:
                EM.AddPeople();
                break;
            case 2:
                EM.ShowPeople();
                break;
            case 3:
                EM.DelPeople();
                break;
            case 4:
                EM.EditPeople();
                break;
            case 5:
                EM.FindPeople();
                break;
            case 6:
                EM.SortPeople();
                break;
            case 7:
                EM.Clean();
                break;
            default:
                system("cls");
            
        }

    }
    system("pause");
    return 0;
}