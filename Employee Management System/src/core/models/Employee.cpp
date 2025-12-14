#include "include/core/models/Employee.h"
#include<sstream>
#include<iomanip>

Employee::Employee() :name(""), socialNumber(""), jobTitle(""),
baseSalary(0), dob(Date()), hireDate(Date())
{
}

Employee::Employee(const string& empName, const string& empSocialNumber, const string& empJobTitle,
	const double salary, const Date& birthDate, const Date& joinDate)
	: name(empName), socialNumber(empSocialNumber), jobTitle(empJobTitle),
	baseSalary(salary), dob(birthDate), hireDate(joinDate)
{
}

void Employee::updateName(const string& newName) { name = newName; }
void Employee::updateSocialNumber(const string& newSocialNumber) { socialNumber = newSocialNumber; }
void Employee::updateJobTitle(const string& newJobTitle) { jobTitle = newJobTitle; }
void Employee::updateSalary(const double newSalary) { baseSalary = newSalary; }
void Employee::updateDob(const Date& newDob) { dob = newDob; }
void Employee::updateHireDate(const Date& newHireDate) { hireDate = newHireDate; }

int Employee::getAge() const { return dob.elapsedYears(); }
int Employee::getYearsWorked() const { return hireDate.elapsedYears(); }

double Employee::computeNetSalary(const double taxRate, const double insuranceRate) const
{
	double insuranceAmount, taxAmount;
	insuranceAmount = this->baseSalary * insuranceRate;
	taxAmount = this->baseSalary * taxRate;
	return this->baseSalary - (insuranceAmount + taxAmount);
}

string Employee::toString() const
{
	ostringstream oss;
	oss << "| " << setw(21) << setiosflags(ios::left) << this->name << "  | "
		<< "| " << setw(13) << setiosflags(ios::left) << this->socialNumber << "  | "
		<< "| " << setw(19) << setiosflags(ios::left) << this->jobTitle << "  | "
		<< "| " << setw(13) << setiosflags(ios::left) << this->computeNetSalary(TAX_RATE, INSURANCE_RATE) << "  | "
		<< "| " << setw(4) << setiosflags(ios::left) << this->getAge() << "  | "
		<< "| " << setw(13) << setiosflags(ios::left) << this->getYearsWorked() << "  | ";
	return oss.str();
}