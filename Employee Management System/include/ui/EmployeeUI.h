#pragma once
#include "include/core/interfaces/IEmployeeService.h"
#include<memory>

class EmployeeUI
{
public:
	explicit
	EmployeeUI(shared_ptr<IEmployeeService> employeeService);

private:
	shared_ptr<IEmployeeService> _service;

};