#include "include/services/EmployeeService.h"
#include "include/core/common/Constants.h"

EmployeeService::EmployeeService(unique_ptr<IEmployeeRepository> repo) : employeeRepository(move(repo)), isModified(false)
{}

OperationResult<void> EmployeeService::initialize()
{
	auto result = employeeRepository->load();

	if (result.status == OperationStatus::Failure && !result.data.has_value())
		return OperationResult<void>::Failure(result.message);
		
	employees = move(result.data.value());
	return OperationResult<void>::Success();
}

bool isNewSocialNumberUnique(const vector<unique_ptr<Employee>>& employees, const string& socialNumber, const string& exculdeSocialNumber = "")
{
	size_t employeeCount = employees.size();
	for (int i = 0; i < employeeCount; i++)
	{
		string employeeSocialNumber = employees[i]->getSocialNumber();
		if(employeeSocialNumber == socialNumber && employeeSocialNumber != exculdeSocialNumber)
			return false;
	}
	return true;
}

OperationResult<vector<Employee>> EmployeeService::getAllEmployees() const
{
	if (employees.empty())
		return OperationResult<vector<Employee>>::Failure("No employees found.");

	vector<Employee> result;
	result.reserve(employees.size());
	for (const auto& employee : employees)
		result.push_back(*employee);
	
	return OperationResult<vector<Employee>>::Success(result);
}

OperationResult<Employee*> EmployeeService::findEmployee(const function<bool(const Employee&)>& criteria) const
{
	size_t employeeCount = employees.size();
	for (int i = 0; i < employeeCount; i++)
	{
		if (criteria(*employees[i]))
			return OperationResult<Employee*>::Success(employees[i].get());
	}
	return  OperationResult<Employee*>::Failure("Employee not found");
}

OperationResult<Employee> EmployeeService::addEmployee(unique_ptr<Employee> newEmployee)
{
	if (!isNewSocialNumberUnique(employees, newEmployee->getSocialNumber()))
		return OperationResult<Employee>::Failure("An employee with this social number is already exist.");

	employees.push_back(move(newEmployee));
	isModified = true;
	return OperationResult<Employee>::Success(*employees.back(), "Employee added successfully");
}

OperationResult<Employee> EmployeeService::updateEmployee(const string& socialNumber, const Employee& updatedEmployee)
{
	auto result = findEmployee([socialNumber](const Employee& e) { return e.getSocialNumber() == socialNumber; });
	if(result.status == OperationStatus::Failure)
		return OperationResult<Employee>::Failure(result.message);

	Employee* employee = result.data.value();

	string newSocialNumber = updatedEmployee.getSocialNumber();
	if (!isNewSocialNumberUnique(employees, newSocialNumber, socialNumber))
		return OperationResult<Employee>::Failure("An employee with this social number is already exist.");

	string newEmployeeName = updatedEmployee.getName();
	string newEmployeeSocialNumber = updatedEmployee.getSocialNumber();
	string newEmployeeJobTitle = updatedEmployee.getJobTitle();
	double newEmployeeBaseSalary = updatedEmployee.getBaseSalary();
	Date newEmployeeDateOfBirth = updatedEmployee.getDateOfBirth();
	Date newEmployeeHireDate = updatedEmployee.getHireDate();

	isModified = false;

	if (!newEmployeeName.empty() && employee->getName() != newEmployeeName)
	{
		employee->updateName(newEmployeeName);
		isModified = true;
	}
	if (!newEmployeeSocialNumber.empty() && employee->getSocialNumber() != newEmployeeSocialNumber)
	{
		employee->updateSocialNumber(newEmployeeSocialNumber);
		isModified = true;
	}
	if (!newEmployeeJobTitle.empty() && employee->getJobTitle() != newEmployeeJobTitle)
	{
		employee->updateJobTitle(newEmployeeJobTitle);
		isModified = true;
	}
	if (newEmployeeBaseSalary != 0 && employee->getBaseSalary() != newEmployeeBaseSalary)
	{
		employee->updateSalary(newEmployeeBaseSalary);
		isModified = true;
	}
	if (!newEmployeeDateOfBirth.isEmpty() && employee->getDateOfBirth() != newEmployeeDateOfBirth)
	{
		employee->updateDob(newEmployeeDateOfBirth);
		isModified = true;
	}
	if (!newEmployeeHireDate.isEmpty() && employee->getHireDate() != newEmployeeHireDate)
	{
		employee->updateHireDate(newEmployeeHireDate);
		isModified = true;
	}
	if(!isModified)
		return OperationResult<Employee>::NoChanges("No changes detected");

	return OperationResult<Employee>::Success(*employee, "Employee updated successfully.");
}

OperationResult<void> EmployeeService::deleteEmployee(const string& socialNumber)
{
	auto result = findEmployee([socialNumber](const Employee& e) { return e.getSocialNumber() == socialNumber; });
	if (result.status == OperationStatus::Failure)
		return OperationResult<void>::Failure(result.message);

	Employee* employee = result.data.value();
	for (auto it = employees.begin(); it != employees.end(); it++)
	{
		if (it->get() == employee)
		{
			employees.erase(it);
			isModified = true;
			return OperationResult<void>::Success("Employee deleted successfully.");
		}
	}
	return OperationResult<void>::Failure("Unexpected error occurred while deleting employee.");
}

OperationResult<double> EmployeeService::getEmployeeNetSalary(const string& socialNumber) const
{
	auto result = findEmployee([socialNumber](const Employee& e) { return e.getSocialNumber() == socialNumber; });
	if (result.status == OperationStatus::Failure)
		return OperationResult<double>::Failure(result.message);
	
	Employee* employee = result.data.value();
	if (employee == nullptr)
		return OperationResult<double>::Failure("Employee not found.");

	return OperationResult<double>::Success(employee->computeNetSalary(TAX_RATE, INSURANCE_RATE));
}

OperationResult<double> EmployeeService::computeAverageNetSalary()
{
	size_t employeeCount = employees.size();
	if(employeeCount == 0)
		return OperationResult<double>::Failure("No employees found");

	double totalSalary = 0.0;
	for (int i = 0; i < employeeCount; i++)
	{
		totalSalary += employees[i]->computeNetSalary(TAX_RATE, INSURANCE_RATE);
	}

	return OperationResult<double>::Success(totalSalary / employeeCount);
}

OperationResult<void> EmployeeService::saveIfNeeded()
{
	if (isModified)
	{
		auto repoResult = employeeRepository->save(employees);
		
		if (repoResult.status == OperationStatus::Failure)
			return OperationResult<void>::Failure(repoResult.message);
		
		isModified = false;
		return OperationResult<void>::Success("Changes saved successfully.");
	}
	return OperationResult<void>::NoChanges("No changes to save.");
}