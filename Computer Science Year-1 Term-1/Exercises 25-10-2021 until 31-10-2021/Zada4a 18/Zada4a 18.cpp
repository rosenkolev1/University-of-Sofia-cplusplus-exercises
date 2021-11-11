// Zada4a5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
	int day, month;

	cout << "Enter the day: ";
	cin >> day;
	cout << "Enter the month: ";
	cin >> month;

	int totalNumberOfDaysSinceBeginningOfTheYear = 0;

	for (int i = 1; i <= month - 1; i++)
	{
		//If it is February
		if (i == 2) totalNumberOfDaysSinceBeginningOfTheYear += 28;
		//If it is April or June
		else if (i % 2 == 0 && i <= 6) totalNumberOfDaysSinceBeginningOfTheYear += 30;
		//If it is September or November
		else if (i % 2 == 1 && i >= 9) totalNumberOfDaysSinceBeginningOfTheYear += 30;
		//If it is January, March, May, July, August October, December
		else totalNumberOfDaysSinceBeginningOfTheYear += 31;
	}

	totalNumberOfDaysSinceBeginningOfTheYear += day;

	int weekDayNumberOffset = (totalNumberOfDaysSinceBeginningOfTheYear - 1) % 7;

	if (weekDayNumberOffset == 0) cout << "Friday";
	else if (weekDayNumberOffset == 1) cout << "Saturday";
	else if (weekDayNumberOffset == 2) cout << "Sunday";
	else if (weekDayNumberOffset == 3) cout << "Monday";
	else if (weekDayNumberOffset == 4) cout << "Tuesday";
	else if (weekDayNumberOffset == 5) cout << "Wednesday";
	else if (weekDayNumberOffset == 6) cout << "Thursday";
}


