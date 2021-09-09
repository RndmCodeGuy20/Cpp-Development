#include <iostream>
using namespace std;

class Employee
{
public:
	string Name;
	string Designation;

	void Employee() {

	}

private:
	int Age;
};

class Developer : Employee {
public:
	int numOfLangs;
	int Experience;

private:
	int Salary;
};


int main() {

	Developer dev;



	return 0;
}