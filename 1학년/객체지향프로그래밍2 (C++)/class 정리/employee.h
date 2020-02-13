#pragma once
#ifndef EMPLOYEE2_H
#define EMPLOYEE2_H

class Employee {
public:
	Employee(const char *, const char *); // constructor
	~Employee(); // destructor
	const char *getFirstName() const; // return first name
	const char *getLastName() const; // return last name
	static int getCount(); // return # objects instantiated
	void setNext(Employee* input);
	Employee* getNext();

private:
	char *firstName;
	char *lastName;

	Employee* next;
	static int count;
}; // end

#endif