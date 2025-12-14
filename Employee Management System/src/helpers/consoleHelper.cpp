#include "include/helpers/consoleHelper.h"

void printSeparator()
{
	cout << " ====================================================================================================================" << endl;
	cout << "\n\n";
}

void printTitle(const string& title)
{
	const int width = 117;
	size_t pad = (width - title.length()) / 2;
	cout << string(width, '-') << endl;
	cout << string(pad, ' ') << title << endl;
	cout << string(width, '-') << endl;
	cout << "\n\n";
}

void printSuccess(const string& msg)
{
	cout << "\033[32m" << "[Success] " << msg << "\033[0m" << "\n\n";
}

void printError(const string& msg)
{
	cout << "\033[31m" << "[Error] " << msg << "\033[0m" << "\n\n";
}

void printInfo(const string& msg)
{
	cout << "\033[34m" << "[Info] " << msg << "\033[0m" << "\n\n";
}