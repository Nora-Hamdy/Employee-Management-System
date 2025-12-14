#pragma once

#include<ctime>
#include<string>
using namespace std;

struct  Date
{
private:
	tm dateValue;

public:
	Date();
	Date(const int day, const int month, const int year);

	const tm getTm() const { return dateValue; }
	const int getDay() const { return dateValue.tm_mday; }
	const int getMonth() const { return dateValue.tm_mon + 1; }
	const int getYear() const { return dateValue.tm_year + 1900; }

	int elapsedYears() const;

	/**
	* @brief Parse a date string in "DD/MM/YYYY" format into a Date object.
	* @param dateStr The string representing the date.
	* @return Date The Date object corresponding to the input string.
	*/
	static Date parseDate(const string& dateStr);
	bool isEmpty() const;
	bool operator==(const Date& other) const;
	bool operator!=(const Date& other) const;
	string toString() const;
};