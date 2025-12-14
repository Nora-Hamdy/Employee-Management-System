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

};