#pragma once

#include "Date.h"

class Employee
{
private:
	string name;
	string socialNumber;
	string jobTitle;
	double baseSalary;
	Date dob;
	Date hireDate;
public:

	Employee();
	Employee(const string& empName, const string& empSocialNumber, const string& empJobTitle, const double salary,
		const Date& birthDate, const Date& joinDate);

	const string& getName() const { return name; }
	const string& getSocialNumber() const { return socialNumber; }
	const string& getJobTitle() const { return jobTitle; }
	const double getBaseSalary() const { return baseSalary; }
	const Date& getDateOfBirth() const { return dob; }
	const Date& getHireDate() const { return hireDate; }

	void updateName(const string& newName);
	void updateSocialNumber(const string& newSocialNumber);
	void updateJobTitle(const string& newJobTitle);
	void updateSalary(const double newSalary);
	void updateDob(const Date& newDob);
	void updateHireDate(const Date& newHireDate);

	int getAge() const;
	int getYearsWorked() const;

	double computeNetSalary(const double taxRate, const double insuranceRate) const;

	string toString() const;
};