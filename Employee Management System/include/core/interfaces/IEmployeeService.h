#pragma once

#include "include/core/models/Employee.h"
#include "include/core/common/OperationResult.h"
#include <functional>
#include<vector>
#include<memory>
using namespace std;

class IEmployeeService
{
public:
	virtual ~IEmployeeService() = default;

	virtual OperationResult<void> initialize() = 0;
	virtual OperationResult<vector<Employee>> getAllEmployees() const = 0;
	virtual OperationResult<Employee*> findEmployee(const function<bool(const Employee&)>& criteria) const = 0;
	virtual OperationResult<Employee> addEmployee(unique_ptr<Employee> newEmployee) = 0;
	virtual OperationResult<Employee> updateEmployee(const string& socialNumber, const Employee& updatedEmployee) = 0;
	virtual OperationResult<void> deleteEmployee(const string& socialNumber) = 0;
	virtual OperationResult<double> getEmployeeNetSalary(const string& socialNumber) const = 0;
	virtual OperationResult<double> computeAverageNetSalary() = 0;
	virtual OperationResult<void> saveIfNeeded() = 0;
};
