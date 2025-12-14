#pragma once

#include "include/core/models/Employee.h"
#include "include/core/common/OperationResult.h"
#include <vector>
#include <memory>

class IEmployeeRepository
{
public:
	virtual ~IEmployeeRepository() = default;
	virtual OperationResult<vector<unique_ptr<Employee>>> load() = 0;
	virtual OperationResult<void> save(const vector<unique_ptr<Employee>>& employees) = 0;
};