#include <iostream>
using std::cout;
using std::endl;
#include <new> 
#include "employee.h" // Employee class definition
#include "employer.h"

int main() {
	cout << "Number of employees before instantiation is " << Employee::getCount() << endl; // use class name
	Employee *e1Ptr = new Employee("Susan", "Baker");
	Employee *e2Ptr = new Employee("Robert", "Jones");
	Employee *e3Ptr = new Employee("Rob", "Jo6es");
	Employee *e4Ptr = new Employee("Rob2t", "Jo5es");
	Employee *e5Ptr = new Employee("Rob3", "Jo4s");
	Employer *manager = new Employer(e1Ptr);
	manager->Enqueue(e2Ptr);
	manager->Enqueue(e3Ptr);
	manager->Enqueue(e4Ptr);
	manager->Enqueue(e5Ptr);
	manager->printList();

	cout << "Number of employees after instantiation is " << e1Ptr->getCount();
	cout << "\n\nEmployee 1: " << e1Ptr->getFirstName() << " " << e1Ptr->getLastName() << "\nEmployee 2: " << e2Ptr->getFirstName() << " " << e2Ptr->getLastName() << "\n\n";

	cout << e1Ptr->getCount() << " " <<
		e2Ptr->getCount() << " ";
	delete e1Ptr; 
	e1Ptr = 0; 
	delete e2Ptr;
	e2Ptr = 0;
	cout << "Number of employees after deletion is " << Employee::getCount() << endl;

	system("PAUSE");
	return 0;
} // end
