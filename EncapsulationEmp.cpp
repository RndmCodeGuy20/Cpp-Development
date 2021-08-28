#include <iostream>
using namespace std;

class Employee {
private:
	string Name;
	string Company;
	int Age;

public:
	void setName(string name) {
		Name = name;
	}

	string getName() {
		return Name;
	}

	void setAge(int age) {
		Age = age;
	}

	int getAge() {
		return Age;
	}
};

int main() {
	Employee emp;
	emp.setName("Shantanu");
	emp.setAge(23);

	cout << "Name of employee is : " << emp.getName() << endl;
	cout << "Age of employee is : " << emp.getAge() << endl;
}