#pragma once

#include "include/core/interfaces/IEmployeeRepository.h"
#include "include/core/models/Employee.h"

class EmployeeRepository : public IEmployeeRepository {
private:
	string filename;

public:
	explicit
	EmployeeRepository(const string& file);

	OperationResult<vector<unique_ptr<Employee>>> load() override;
	OperationResult<void> save(const vector<unique_ptr<Employee>>& employees) override;
};