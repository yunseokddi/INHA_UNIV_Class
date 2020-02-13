#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using std::cout;
using std::endl;
#include <new> // C++ standard new operator
#include <cstring> // strcpy and strlen prototypes
#include "employee.h" // Employee class definition
#include "employer.h"


Employer::Employer(Employee* input) {
	this->first = input;
} // end Employee constructor

Employer::~Employer() {
	delete this->first;
} // end


void Employer::Enqueue(Employee* input) {
	Employee* temp=first;
	for (int i = 0; i < input->getCount(); i++) {
		if (temp->getNext() != NULL) {
			temp = temp->getNext();
		}
		else {//temp->next == 0/NULL
			temp->setNext(input);
			return;
		}
	}
}

void Employer::printList() {
	Employee* temp = first;
	for (int i = 0; i < temp->getCount(); i++) {
		if (temp->getNext() != NULL) {
			cout << i + 1 << temp->getFirstName() << " "
				<< temp->getLastName() << " " << endl;
			temp = temp->getNext();
		}
		else {
			cout << i + 1 << temp->getFirstName() << " "
				<< temp->getLastName() << " " << endl;
			return;
		}
	}
}

void Employer::search(int a)
{
	int a = 0;
	cin >> a;
	switch (a)
	{
	case 1:
		Employer.printlist(1);
		break;
	case 2:
		Employer.printlist(2);
		break;
	case 3:
		Employer.printlist(3);
		break;
	case 4:
		Employer.printlist(4);
		break;
	case 5:
		Employer.printlist(5);
		break;
	}
}

void Employer::Dequeue()
{

}