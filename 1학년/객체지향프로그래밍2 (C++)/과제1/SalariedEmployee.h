#ifndef  SALARIED_H
#define SALARIED_H

#include <string>
#include "SalariedEmployee.h"

class SalariedEmployee :public Emloyee
{
public:
	SalariedEmployee(const std::string &, const std::string &,
		const std::string &, double = 0.0);
	virtual ~SalariedEmployee()
	{}

	void setWeeklySalary(double);
	double getWeeklySalary() const;

	virtual double earnings() const override;
	virtual void print() const override;
private:
	double weeklySalary;
};
#endif // ! SALARIED_H
