#include <iostream>
#include <iomanip>
#include <vector>
#include "Employee.h"
#include "SalariedEmployee.h"
#include "CommisionEmployee.h"
#include "BasePlusCommissionEmployee.h"
using namespace std;

void virtualViaPointer(const Employee * const);
void virtualViaRefence(const Employee &);

int main()
{
	cout << fixed << setprecision(2);
	SalariedEmployee salariedEmployee("John", "Smith", "111-11-1111", 800);
	CommissionEmployee::CommissionEmployee("Sue", "jones", "333-33-3333", 10000, 06);
	BasePlusCommissionEmployee::BasePlusCommissionEmployee("Bob", "Lewis", "444-44-4444", 5000, 04, 300);

	cout << "Employees processed individually using static binding:\n\n";

	salariedEmployee.print();
	cout << "\nearned $" << salariedEmployee.earnings() << "\n\n";
	CommissionEmployee.print();
	cout << "\nearned $" << CommissionEmployee.earnings() << "\n\n";
	BasePlusCommissionEmployee.print();
	cout << "\nearned $" << BasePlusCommissionEmployee.earnings()
		<< "\n\n";

	vector <Employee *> employees(3);

	employees[0] = &salariedEmployee;
	employees[1] = &CommissionEmployee;
	employees[2] = &BasePlusCommissionEmployee;

	cout << "Employees processed polymorphically via dynamic binding:\n\n";

	cout << "Virtual function calls made off base-class pointers:\n\n";

	for (const Employee *employeePtr : employees)
		virtualViaPointer(employeePtr);

	cout << "Virtual function calls made off base-class references:\n\n";

	for (const Employee *employeePtr : employees)
		virtualViaRefence(*employeePtr);

	void virtualViaPointer(const Employee * const baseClassPtr)
	{
		baseClassPtr->print();
		cout << "\nearned $" << baseClassPtr->earnings() "\n\n";

	}

	void virtualViaRefence(const Employee &baseClassRef)
	{
		baseClassRef.print();
		cout << "\nearned $" << baseClassRef.earnings() << "\n\n";
	}

}