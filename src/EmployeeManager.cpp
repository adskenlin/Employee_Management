#include "EmployeeManager.h"

EmployeeManager::EmployeeManager()
{
    // if file not exists
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    if (!ifs.is_open())
    {
        cout << "File does not exist!" << endl;
        
        this->m_peopleNum = 0;
        this->m_peopleArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        cout << "File is empty!" << endl;
        this->m_peopleNum = 0;
        this->m_peopleArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    int num = this->get_peopleNum();
    if (num > 0){
        this->m_FileIsEmpty = false;
    }
    // cout << "There are " << num << " employees" << endl;
    this->m_peopleNum = num;
    // open space in memory
    this->m_peopleArray = new People*[this->m_peopleNum];
    // init
    this->init_peopleArray();

    // for (int i = 0; i < this->m_peopleNum; i++)
    // {
    //     cout << "ID: " << this->m_peopleArray[i]->m_ID
    //      << "\tName: " << this->m_peopleArray[i]->m_Name
    //      << "\tCategory: " << this->m_peopleArray[i]->m_DeptID
    //      << endl;
    // }

}

void EmployeeManager::ShowMenu()
{
    cout << "Welcome to Employee Management System!" << endl;
    cout << "**************************************" << endl;
    cout << "Please Choose Your Options:           " << endl;
    cout << "0. Quit                               " << endl;
    cout << "1. Add Employee Information           " << endl;
    cout << "2. Display Employee's Information     " << endl;
    cout << "3. Delete resigned Employee           " << endl;
    cout << "4. Edit Employee's Information        " << endl;
    cout << "5. Find Employee's Information        " << endl;
    cout << "6. Sort Information w.r.t. ID         " << endl;
    cout << "7. Clean All Information              " << endl;
    cout << "**************************************" << endl;
    cout << endl;
}

void EmployeeManager::ExitSystem()
{
    cout << "See You!" << endl;
    system("pause");
    exit(0);
}

void EmployeeManager::AddPeople()
{
    cout << "Please enter the number of employees you want to add: " << endl;
    int addNum = 0;
    cin >> addNum;

    if (addNum > 0)
    {
        // calculate the new number of employees
        int newSize = this->m_peopleNum + addNum;

        // open a space for storing the addresses of employees
        People ** newSpace = new People*[newSize];

        // copy the old array to new space
        if (this-> m_peopleArray != NULL)
        {
            for (int i = 0; i < this->m_peopleNum; i++)
            {
                newSpace[i] = this->m_peopleArray[i];
            }
        }

        for (int i=0; i < addNum; i++)
        {
            int id;
            string name;
            int dSelect;

            cout << "please enter the id of " << i+1 << " new employee: ";
            cin >> id;

            cout << "please enter the name of " << i+1 << " new employee: ";
            cin >> name;

            cout << "please enter the category of " << i+1 << " new employee: " << endl;
            cout << "1. Employee" << endl;
            cout << "2. Manager" << endl;
            cout << "3. Boss" << endl;
            cin >> dSelect;

            People * people = NULL;
            switch (dSelect)
            {
                case 1:
                    people = new Employee(id, name, 1);
                    break;
                case 2:
                    people = new Manager(id, name, 2);
                    break;
                case 3:
                    people = new Boss(id, name, 3);
                    break;
                default:
                    break;
                    
            }
            newSpace[this->m_peopleNum + i] = people;
        }

        // update attrs.
        delete [] this-> m_peopleArray;
        this -> m_peopleArray = newSpace;
        this -> m_peopleNum = newSize;
        this -> m_FileIsEmpty = false;

        // save in file
        this->save();

        cout << addNum << " People added!" << endl;

    }
    else
    {
        cout << "please enter a valid number!" << endl;
    }

    system("pause");
    system("cls");

}

void EmployeeManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    //
    for (int i=0; i < this->m_peopleNum; i++)
    {
        ofs << this->m_peopleArray[i]->m_ID << " "
            << this->m_peopleArray[i]->m_Name << " "
            << this->m_peopleArray[i]->m_DeptID << endl;
    }

    ofs.close();
}

int EmployeeManager::get_peopleNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int deptID;

    int num = 0;

    while (ifs >> id && ifs >> name && ifs >> deptID)
    {
        num++;
    }

    ifs.close();

    return num;
}

void EmployeeManager::init_peopleArray()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int deptID;

    int num = 0;

    while (ifs >> id && ifs >> name && ifs >> deptID)
    {
        People * people = NULL;

        if (deptID == 1)
        {
            people = new Employee(id, name, deptID);
        }else if (deptID == 2)
        {
            people = new Manager(id, name, deptID);
        }else
        {
            people = new Boss(id, name, deptID);
        }
        this->m_peopleArray[num] = people;
        num++;
    }
    ifs.close();
}

void EmployeeManager::ShowPeople()
{
    if (this->m_FileIsEmpty)
    {
        cout << "Empty file or no record!" << endl;
    }else{
        for (int i = 0; i < m_peopleNum; i++)
        {
            this->m_peopleArray[i]->showInfo();
        }
    }

    system("pause");
    system("cls");

}

int EmployeeManager::isExist(int id)
{
    int index = -1;

    for (int i = 0; i < this->m_peopleNum; i++)
    {
        if (this->m_peopleArray[i]->m_ID == id)
        {
            index = i;
            break;
        }
    }

    return index;

}

void EmployeeManager::DelPeople()
{
    if (this->m_FileIsEmpty)
    {
        cout << "Empty file or no record!" << endl;
    }
    else{
        cout << "Please enter the id of employee: " << endl;
        int id = 0;
        cin >> id;

        int index = this->isExist(id);

        if (index != -1)
        {
            for (int i = index; i < this->m_peopleNum-1; i++)
            {
                this->m_peopleArray[i] = this->m_peopleArray[i+1];
            }
            this->m_peopleNum--;
            this->save();

            cout << "Deleted!" << endl;

        }else{
            cout << "Could not find this employee in database!" << endl;
        }
    }

    system("pause");
    system("cls");

}

EmployeeManager::~EmployeeManager()
{
    if (this->m_peopleArray != NULL)
    {
        delete [] this->m_peopleArray;
        this->m_peopleArray = NULL;
    }

}