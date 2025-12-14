#include "include/ui/EmployeeUI.h"
#include<iostream>
using namespace std;

EmployeeUI::EmployeeUI(shared_ptr<IEmployeeService> employeeService) : _service(move(employeeService)) 
{}