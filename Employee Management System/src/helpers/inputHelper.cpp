#include "include/helpers/inputHelper.h"

string toLowerCase(const string& s)
{
	string out = s;
	for (char& c : out)
		c = tolower(static_cast<unsigned char>(c));

	return out;
}

string promptString(const string& message)
{
	while (true)
	{
		cout << message;
		string value;
		getline(cin, value);
		if (!value.empty())
			return value;

		printError("Input cannot be empty. Please enter a value.");
	}
}

char promptYesNo(const string& message)
{
	while (true)
	{
		char choice = toupper(prompt<char>(message));
		if (choice == 'Y' || choice == 'N')
			return choice;
		printError("Invalid input. Please enter Y or N.");
	}
}