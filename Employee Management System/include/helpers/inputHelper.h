#pragma once
#include "consoleHelper.h"
#include<string>
#include <sstream>
#include<iostream>
using namespace std;

string toLowerCase(const string& s);

template<typename T>
T prompt(const string& message)
{
	T value;
	while (true)
	{
		cout << message;
		string input;
		getline(cin, input);
		istringstream iss(input);
		if (iss >> value)
		{
			char extra;
			if (!(iss >> extra))
				return value;
		}
		printError("Invalid input. Please enter a valid value.");
		printSeparator();
	}
}

string promptString(const string& message);

char promptYesNo(const string& message);