#include "include/core/models/Date.h"
#include<sstream>
#include<iomanip>

Date::Date()
{
	dateValue.tm_mday = -1;
	dateValue.tm_mon = -1;
	dateValue.tm_year = -1;
}

Date::Date(const int day, const int month, const int year)
{
	dateValue.tm_mday = day;
	dateValue.tm_mon = month - 1;
	dateValue.tm_year = year - 1900;
}

int Date::elapsedYears() const
{
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);

	int currentYear = localTime.tm_year;
	int currentMonth = localTime.tm_mon;
	int currentDay = localTime.tm_mday;

	int years = currentYear - dateValue.tm_year;
	if (currentMonth < dateValue.tm_mon ||
		(currentMonth == dateValue.tm_mon && currentDay < dateValue.tm_mday))
		return --years;

	return years;
}

Date Date::parseDate(const string& dateStr)
{
	istringstream ss(dateStr);
	if (!dateStr.empty())
	{
		int day, month, year;
		char daySeparator, monthSeparator;
		ss >> day >> daySeparator >> month >> monthSeparator >> year;
		Date parsedDate(day, month, year);
		return parsedDate;
	}

	return Date();
}

bool Date::isEmpty() const
{
	return dateValue.tm_mday == -1 && dateValue.tm_mon == -1 && dateValue.tm_year == -1;
}

bool Date::operator==(const Date& other) const
{
	return dateValue.tm_mday == other.dateValue.tm_mday
		&& dateValue.tm_mon == other.dateValue.tm_mon
		&& dateValue.tm_year == other.dateValue.tm_year;
}

bool Date::operator!=(const Date& other) const
{
	return !(*this == other);
}

string Date::toString() const
{
	ostringstream oss;
	oss << setfill('0') << setw(2) << dateValue.tm_mday << "/"
		<< setw(2) << dateValue.tm_mon + 1
		<< "/" << dateValue.tm_year + 1900;
	return oss.str();
}