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

            bool id_exist = true;
            cout << "please enter the id of " << i+1 << " new employee: ";
            do
            {
                cin >> id;
                int index = this->isExist(id);
                if (index == -1)
                {
                    id_exist = false;
                }else{
                    cout << "ID already exists!" << endl;
                    cout << "Enter a new ID: " << endl;
                }
            }while (id_exist);

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

void EmployeeManager::EditPeople()
{
    if (this->m_FileIsEmpty)
    {
        cout << "Empty file or no record!" << endl;
    }else{
        cout << "Please enter the id of employee: " << endl;
        int id;
        cin >> id;

        int index = this->isExist(id);

        if (index != -1)
        {
            delete this->m_peopleArray[index];
            int newID = 0;
            string newName = "";
            int dSelect = 0;

            cout << "found employee with ID" << id << endl;
            cout << "Please enter new ID: ";
            cin >> newID;
            cout << "Please enter new name: ";
            cin >> newName;
            cout << "Please enter new category: " << endl;
            cout << "1. Employee" << endl;
            cout << "2. Manager" << endl;
            cout << "3. Boss" << endl;
            cin >> dSelect;

            People * people = NULL;
            switch (dSelect)
            {
                case 1:
                    people = new Employee(newID, newName, 1);
                    break;
                case 2:
                    people = new Manager(newID, newName, 2);
                    break;
                case 3:
                    people = new Boss(newID, newName, 3);
                    break;
                default:
                    break;
                    
            }
            this->m_peopleArray[index] = people;

            cout << "You have changed " << newName << "'s inforamtion!" << endl;

            this->save();

        }else{
            cout << "Could not find this employee in database!" << endl;
        }

    }
    system("pause");
    system("cls");
}

void EmployeeManager::FindPeople()
{
    if (this->m_FileIsEmpty)
    {
        cout << "Empty file or no record!" << endl;
    }else{
        cout << "Find the employee with: " << endl;
        cout << "1. ID " << endl;
        cout << "2. Name " << endl;

        int select = 0;
        cin >> select;

        if (select == 1)
        {
            int id;
            cout << "Please enter ID: " << endl;
            cin >> id;

            int index = this->isExist(id);
            if (index != -1)
            {
                cout << "Found as follows: " << endl;
                this->m_peopleArray[index]->showInfo();
            }else{
                cout << "Could not find this employee in database!" << endl;
            }
        }else if (select == 2)
        {
            string name;
            cout << "Please enter Name: " << endl;
            cin >> name;

            bool flag = false;
            for (int i=0; i < m_peopleNum; i++)
            {
                if (m_peopleArray[i]->m_Name == name)
                {
                    cout << "Found as follows: " << endl;
                    flag = true;
                    this->m_peopleArray[i]->showInfo();
                }
            }

            if (flag == false)
            {
               cout << "Could not find this employee in database!" << endl; 
            }
        }else{
            cout << "Invalid option!" << endl;
        }
    }
    system("pause");
    system("cls");
}

void EmployeeManager::SortPeople()
{
    if (this->m_FileIsEmpty)
    {
        cout << "Empty file or no record!" << endl;
        system("pasue");
        system("cls");
    }
    else
    {
        cout << "Please enter your sort option: " << endl;
        cout << "1. Ascending w.r.t. IDs" << endl;
        cout << "2. Descending w.r.t. IDs" << endl;

        int select = 0;
        cin >> select;
        for (int i=0; i < this->m_peopleNum; i++)
        {
            int minOrMax = i;
            for (int j = i+1; j< this->m_peopleNum;j++)
            {
                if (select==1)
                {
                    if (this->m_peopleArray[minOrMax]->m_ID > this->m_peopleArray[j]->m_ID)
                    {
                        minOrMax = j;
                    }
                }
                else
                {
                    if (this->m_peopleArray[minOrMax]->m_ID < this->m_peopleArray[j]->m_ID)
                    {
                        minOrMax = j;
                    }
                }
            }
            if (i != minOrMax)
            {
                People * temp = this->m_peopleArray[i];
                this->m_peopleArray[i] = this->m_peopleArray[minOrMax];
                this->m_peopleArray[minOrMax] = temp;
            }
        }
        cout << "Sorted: " << endl;
        this->save();
        this->ShowPeople();
    }
}

void EmployeeManager::Clean()
{
    cout << "Are you sure to clean all data?" << endl;
    cout << "1. Sure" << endl;
    cout << "2. Cancel" << endl;

    int select = 0;
    cin >> select;

    if (select == 1){
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();

        if (this->m_peopleArray != NULL)
        {
            for (int i = 0; i < this->m_peopleNum; i++)
            {
                if (this->m_peopleArray[i] != NULL)
                {
                    delete this->m_peopleArray[i];                  
                }
            }
            this->m_peopleNum = 0;
            delete [] this->m_peopleArray;
            this->m_peopleArray = NULL;
            this->m_FileIsEmpty = true;

        }
        cout << "Clean Done!" << endl;

    }
    system("pause");
    system("cls");
}

EmployeeManager::~EmployeeManager()
{
    if (this->m_peopleArray != NULL)
    {
        for (int i = 0; i < this->m_peopleNum; i++)
        {
            if (this->m_peopleArray[i] != NULL)
            {
                delete this->m_peopleArray[i];
            }
        }
        delete [] this->m_peopleArray;
        this->m_peopleArray = NULL;
    }

}