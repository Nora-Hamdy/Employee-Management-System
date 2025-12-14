#pragma once
#include "include/core/interfaces/IEmployeeRepository.h"
#include "include/core/interfaces/IEmployeeService.h"

class EmployeeService : public IEmployeeService {
private:
	vector<unique_ptr<Employee>> employees;
	unique_ptr<IEmployeeRepository> employeeRepository;
	bool isModified;

public:
	explicit
	EmployeeService(unique_ptr<IEmployeeRepository> repo);

	OperationResult<void> initialize() override;
	OperationResult<vector<Employee>> getAllEmployees() const override;
	OperationResult<Employee*> findEmployee(const function<bool(const Employee&)>& criteria) const override;
	OperationResult<Employee> addEmployee(unique_ptr<Employee> newEmployee) override;
	OperationResult<Employee> updateEmployee(const string& socialNumber, const Employee& updatedEmployee) override;
	OperationResult<void> deleteEmployee(const string& socialNumber) override;
	OperationResult<double> getEmployeeNetSalary(const string& socialNumber) const override;
	OperationResult<double> computeAverageNetSalary() override;
	OperationResult<void> saveIfNeeded() override;

};