#include "include/repository/EmployeeRepository.h"
#include "include/core/common/OperationStatus.h"
#include<fstream>

EmployeeRepository::EmployeeRepository(const string& file) : filename(file)
{}

OperationResult<vector<unique_ptr<Employee>>> EmployeeRepository::load()
{
	vector<unique_ptr<Employee>> employees;

	ifstream employeeFile;    
	employeeFile.open(filename);
	if (!employeeFile.is_open())
	{
		return OperationResult<vector<unique_ptr<Employee>>>::Failure("File not found");
	}
	
	int employeeCount;
	employeeFile >> employeeCount;
	

	for (int i = 0; i < employeeCount; i++)              
	{
		string employeeName, employeeSocialNumber, employeeJobTitle;
		double employeeSalary;
		Date employeeBirthOfDate, employeeHireDate;
		string birthOfDateStr, hireDateStr;

		employeeFile.ignore();                     
		getline(employeeFile, employeeName);     
		employeeFile >> employeeSocialNumber;    
		employeeFile.ignore();                     
		getline(employeeFile, employeeJobTitle);        
		employeeFile >> employeeSalary >> birthOfDateStr >> hireDateStr;
		
		employeeBirthOfDate = Date::parseDate(birthOfDateStr);
		employeeHireDate = Date::parseDate(hireDateStr);

		employees.push_back( make_unique<Employee>(employeeName, employeeSocialNumber, employeeJobTitle, 
			employeeSalary, employeeBirthOfDate, employeeHireDate));

	}
	employeeFile.close();      

	return OperationResult<vector<unique_ptr<Employee>>>::Success(move(employees));
}

OperationResult<void> EmployeeRepository::save(const vector<unique_ptr<Employee>>& employees)
{
	ofstream employeeFile;                 
	employeeFile.open(filename);     

	if (!employeeFile.is_open())
	{
		return OperationResult<void>::Failure("Error: Unable to open " + filename + " file for saving!");
	}
	size_t employeeCount = employees.size();
	employeeFile << employeeCount << endl;

	for (int i = 0; i < employeeCount; i++)      
	{
		Date employeeBirthOfDate = employees[i]->getDateOfBirth();
		Date employeeHireDate = employees[i]->getHireDate();

		employeeFile << employees[i]->getName() << endl
			<< employees[i]->getSocialNumber() << endl
			<< employees[i]->getJobTitle() << endl
			<< employees[i]->getBaseSalary() << endl
			<< employeeBirthOfDate.getDay() << "-"
			<< employeeBirthOfDate.getMonth() << "-"
			<< employeeBirthOfDate.getYear() << endl
			<< employeeHireDate.getDay() << "-"
			<< employeeHireDate.getMonth() << "-"
			<< employeeHireDate.getYear() << endl;
	}
	employeeFile.close();
	return OperationResult<void>::Success();
}

