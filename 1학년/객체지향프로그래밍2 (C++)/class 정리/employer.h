#pragma once

#pragma once
#ifndef EMPLOYER2_H
#define EMPLOYER2_H
#include "employee.h"
class Employer {

public:
	Employer(Employee* input); // constructor
	~Employer(); // destructor

	//static int getCount(); // return # objects instantiated
	
	void printList();				//display all list
	void Enqueue(Employee* input);	//insert

	void search(int num);			//find num
	Employee* Dequeue();			//delete

private:
	Employee* first;
}; // end

#endif