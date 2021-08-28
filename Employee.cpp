#include <iostream>
using namespace std;

class Employee
{
public:
    string Name;
    string Compamy;
    int Age;

    Employee(string Name, string Company, int Age)
    {
        this->Name = Name;
        this->Compamy = Company;
        this->Age = Age;
    }

    void intro()
    {
        cout << "Name : " << Name << endl;
        cout << "Company : " << Compamy << endl;
        cout << "Age : " << Age << endl;
    }
};

int main()
{
    Employee emp = Employee("Shantanu", "Google", 19);
    emp.intro();

    return 0;
}