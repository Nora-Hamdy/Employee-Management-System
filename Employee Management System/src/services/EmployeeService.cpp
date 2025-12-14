#include "include/services/EmployeeService.h"

EmployeeService::EmployeeService(unique_ptr<IEmployeeRepository> repo) : employeeRepository(move(repo)), isModified(false)
{}