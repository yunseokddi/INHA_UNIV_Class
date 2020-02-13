#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using std::cout;
using std::endl;
#include <new> // C++ standard new operator
#include <cstring> // strcpy and strlen prototypes
#include "employee.h" // Employee class definition

int Employee::count = 0;

int Employee::getCount() {
	return count;

}
Employee::Employee(const char *first, const char *last) {
	firstName = new char[strlen(first) + 1];
	strcpy(firstName, first);
	lastName = new char[strlen(last) + 1];
	strcpy(lastName, last);
	++count;
	next = NULL;
	cout << "Employee constructor for " << firstName << ' ' << lastName << " called." << endl;

} // end Employee constructor

  // destructor deallocates dynamically allocated memory


Employee::~Employee() {
	cout << "~Employee() called for " << firstName << ' ' << lastName << endl;
	delete[] firstName; // recapture memory	
	delete[] lastName; // recapture memory
	--count; // decrement static count of employees

} // end destructor ~Employee



const char *Employee::getFirstName() const {

	return firstName;
} // end function getFirstName

const char *Employee::getLastName() const {

	return lastName;
} //

void Employee::setNext(Employee* input) {
	this->next = input;
}
Employee* Employee::getNext() {
	return this->next;
}