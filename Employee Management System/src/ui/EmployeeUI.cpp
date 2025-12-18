#include "include/ui/EmployeeUI.h"
#include "include/helpers/consoleHelper.h"
#include "include/helpers/inputHelper.h"
#include<iostream>
#include<iomanip>
using namespace std;

EmployeeUI::EmployeeUI(shared_ptr<IEmployeeService> employeeService) : _service(move(employeeService)) 
{}

void EmployeeUI::run()
{
	printTitle("|     Welcom to the Employee Management System     |");
	char continueFlag;
	do
	{
		showMainMenu();
		int choice = prompt<int>("Enter your choice: ");
		cout << endl;
		handleUserChoice(choice);
		continueFlag = promptYesNo("Back to Main Menu? (Y/N): ");
		printSeparator();
	} while (continueFlag == 'Y');
	
	saveData();
	printInfo("Exiting Employee Management System...");
}

void EmployeeUI::showMainMenu() const
{
	cout << "Enter 1 to Show All Employees\n" << endl
		 << "Enter 2 to Add New Employee\n" << endl
		 << "Enter 3 to Modify Employee Information\n" << endl
		 << "Enter 4 to Delete Employee\n" << endl
		 << "Enter 5 to Search for Employee\n" << endl
		 << "Enter 6 to Calculate Net Salary\n" << endl
		 << "Enter 7 to Calculate Average Salary\n" << endl
		 << "Enter 0 to Exit\n" << endl;
}

void EmployeeUI::handleUserChoice(int choice)
{
	switch (choice)
	{
		case 1: showAllEmployeesUI(); break;
		case 2: addEmployeeUI(); break;
		case 3: updateEmployeeUI(); break;
		case 4: deleteEmployeeUI(); break;
		case 5: findEmployeeUI(); break;
		case 6: showEmployeeNetSalaryUI(); break;
		case 7: showAverageNetSalaryUI(); break;
		case 0: saveData();
				printInfo("Exiting Employee Management System...");
				exit(0);
		default:
			printError("Invalid Choice.");
			break;
	}
}

void EmployeeUI::addEmployeeUI()
{
	printTitle("Add Employee");
	char choice;

	do {
		string name = promptString("Enter Name: ");
		cout << endl;
		string socialNumber = promptString("Enter Social Number: ");
		cout << endl;
		string jobTitle = promptString("Enter Job Title: ");
		cout << endl;
		double baseSalary = prompt<double>("Enter Salary($): ");
		cout << endl;
		string dobStr = promptString("Enter Birth Date (DD/MM/YYYY): ");
		Date dob = Date::parseDate(dobStr);
		cout << endl;
		string hireDateStr = promptString("Enter Hire Date:  (DD/MM/YYYY): ");
		Date hireDate = Date::parseDate(hireDateStr);
		cout << endl;

		Employee e(name, socialNumber, jobTitle, baseSalary, dob, hireDate);
		auto result = _service->addEmployee(make_unique<Employee>(e));
		
		if (result.status == OperationStatus::Success)
			printSuccess(result.message);
		else
			printError(result.message);

		choice = promptYesNo("Add another employee? (Y/N): ");
		printSeparator();

	} while (choice == 'Y');
}

void EmployeeUI::updateEmployeeUI()
{
	printTitle("Update Employee");

	string socialNumber = promptString("Enter Social Number: ");
	
	Employee updatedEmployee;
	bool updated = false;
	bool continueUpdatingCurrent =true;
	char updateAnotherEmployee;

	while(continueUpdatingCurrent)
	{
		cout<< "Update Employee Information" << endl
			<< "----------------------------" << endl
			<< "1. Update Name" << endl
			<< "2. Update Social Number" << endl
			<< "3. Update Job Title" << endl
			<< "4. Update Salary" << endl 
			<< "5. Update Birth Date" << endl 
			<< "6. Update Hire Date" << endl
			<< "7. Save and Exit" << endl
			<< "8. Cancel" << endl;

		int userChoice = prompt<int>("Select an option: ");
		switch (userChoice)                           
		{
			case 1: updatedEmployee.updateName(promptString("Enter new name: ")); break;
			case 2: updatedEmployee.updateSocialNumber(promptString("Enter new social number: ")); break;
			case 3: updatedEmployee.updateJobTitle(promptString("Enter new job title: ")); break;
			case 4: updatedEmployee.updateSalary(prompt<double>("Enter new salary: ")); break;
			case 5: updatedEmployee.updateDob(Date::parseDate(promptString("Enter new birth date (dd/mm/yyyy): ")));  break;
			case 6: updatedEmployee.updateHireDate(Date::parseDate(promptString("Enter new hire date (dd/mm/yyyy): ")));  break;
			case 7: updated = true; continueUpdatingCurrent = false;  break;
			case 8: printInfo("\t\t\t\tUpdate canceled"); continueUpdatingCurrent = false;  break;
		}
		printSeparator();
	} 

	if (updated)
	{
		auto result = _service->updateEmployee(socialNumber, updatedEmployee);
		if (result.status == OperationStatus::Success)
			printSuccess(result.message);
		else if(result.status == OperationStatus::NoChanges)
			printInfo(result.message);
		else
			printError(result.message);
	}
	updateAnotherEmployee = promptYesNo("Do you want to modify another employee? (Y/N): ");
	cout << endl;
	if (updateAnotherEmployee == 'Y')
		updateEmployeeUI();
}

void EmployeeUI::deleteEmployeeUI()
{
	printTitle("Delete Employee");

	string socialNumber = promptString("Enter Social Number: ");
	
	auto result = _service->deleteEmployee(socialNumber);
	if (result.status == OperationStatus::Success)
		printSuccess(result.message);
	else
		printError(result.message);
	
	char continueDeleting = promptYesNo("Do you want to delete another employee? (Y/N): ");
	cout << endl;
	if (continueDeleting == 'Y')
		deleteEmployeeUI();
}

void EmployeeUI::findEmployeeUI()
{
	printTitle("Find Employee");
	cout << "Search By: \n"
		<< "1. Name" << endl
		<< "2. Social Number" << endl;

	int userChoice = prompt<int>("Please enter your choice: ");
	cout << endl;
	OperationResult<Employee*> result;
	if (userChoice == 1)
	{   
		string name = promptString("Enter Name: ");
		result = _service->findEmployee([name](const Employee& e) { return toLowerCase(e.getName()) == toLowerCase(name); });
	}
	else if (userChoice == 2)
	{
		string socialNumber = promptString("Enter Social Number: ");
		result = _service->findEmployee([socialNumber](const Employee& e) { return e.getSocialNumber() == socialNumber; });
	}
	else
		result = OperationResult<Employee*>::Failure("Invalid Choice.");

	cout << endl;

	if (result.status == OperationStatus::Success)
	{
		printEmployeeTableHeader();
		cout << result.data.value()->toString() << endl;
		printSeparator();
	}
	else
		printError(result.message);

	char continueSearch = promptYesNo("Continue searching for another employee? (Y/N): ");
	cout << endl;
	if (continueSearch == 'Y')
		findEmployeeUI();
}

void EmployeeUI::showAllEmployeesUI()
{
	printTitle("Show All Employees");
	
	auto result = _service->getAllEmployees();
	if (result.status == OperationStatus::Failure)
	{
		printError(result.message);
		printSeparator();
		return;
	}
	
	printEmployeeTableHeader();
	
	for (auto employee : result.data.value())
		cout << employee.toString()<<endl;

	printSeparator();
}

void EmployeeUI::showEmployeeNetSalaryUI()
{
	printTitle("Employee Net Salary");
	string socialNumber = promptString("Enter Social Number: ");
	printTitle("NET SALARY REPORT");

	auto result = _service->getEmployeeNetSalary(socialNumber);
	if (result.status == OperationStatus::Success)
	{
		cout << "Employee Social Number : " << socialNumber << endl;
		cout << "Net Salary : $" << result.data.value() << "\n\n";
	}
	else
		printError(result.message);

	char continueSalaryReport = promptYesNo("Do you want to calculate net salary for another employee? (Y/N): ");
	cout << endl;
	if (continueSalaryReport == 'Y')
		showEmployeeNetSalaryUI();
}

void EmployeeUI::showAverageNetSalaryUI()
{
	printTitle("Average Net Salary");
	auto result = _service->computeAverageNetSalary();
	if (result.status == OperationStatus::Success)
		printSuccess("Average Net Salary of All Employees: $" + to_string(result.data.value()));
	else
		printError(result.message);
	printSeparator();
}

void EmployeeUI::saveData() const
{
	auto result = _service->saveIfNeeded();
	if (result.status == OperationStatus::Success)
		printSuccess(result.message);
	else if (result.status == OperationStatus::NoChanges)
		printInfo(result.message);
	else
		printError(result.message);
}

void EmployeeUI::printEmployeeTableHeader() const
{
	cout << "|" << setw(19) << setiosflags(ios::left) << "Name" << " | ";
	cout << "| " << setw(13) << setiosflags(ios::left) << "Social Number" << " | ";
	cout << "| " << setw(31) << setiosflags(ios::left) << "Job Title" << " | ";
	cout << "| " << setw(13) << setiosflags(ios::left) << "Net Salary($)" << " | ";
	cout << "| " << setw(4) << setiosflags(ios::left) << "Age" << " | ";
	cout << "| " << setw(12) << setiosflags(ios::left) << "Years Worked" << "| " << endl;
	printSeparator();
}