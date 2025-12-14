#pragma once
#include "include/core/interfaces/IEmployeeService.h"
#include<memory>

class EmployeeUI
{
public:
	explicit
	EmployeeUI(shared_ptr<IEmployeeService> employeeService);

	void run();

private:
	shared_ptr<IEmployeeService> _service;

	void showMainMenu() const;
	void handleUserChoice(int choice);

	void addEmployeeUI();
	void updateEmployeeUI();
	void deleteEmployeeUI();
	void findEmployeeUI();
	void showAllEmployeesUI();
	void showEmployeeNetSalaryUI();
	void showAverageNetSalaryUI();
	void saveData() const;

	void printEmployeeTableHeader() const;
	
};