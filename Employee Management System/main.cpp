#include "include/ui/EmployeeUI.h"
#include "include/helpers/ConfigManager.h"
#include "include/helpers/consoleHelper.h"
#include "include/repository/EmployeeRepository.h"
#include "include/services/EmployeeService.h"
#include<iostream>
#include<memory>
using namespace std;

int main()
{
	auto configManager = ConfigManager::instance();
	configManager.load();
	auto fileResult = configManager.get("employee_file");
	if (fileResult.status == OperationStatus::Success)
	{
		unique_ptr<IEmployeeRepository> employeeRepository = make_unique<EmployeeRepository>(fileResult.data.value());
		shared_ptr<IEmployeeService> employeeService = make_shared<EmployeeService>(move(employeeRepository));
		auto employeeServiceResult = employeeService->initialize();
		if (employeeServiceResult.status == OperationStatus::Success)
		{
			EmployeeUI EmployeeUI(move(employeeService));
			EmployeeUI.run();
		}
		else
			printError(employeeServiceResult.message);
	}
	else
		printError(fileResult.message);
	system("pause");
	return 0;
}