// Exercise 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

void returnDate(int day, int month, int year, int daysPassed)
{
	for (int i = 0; i < daysPassed; i++)
	{
		bool visokosnaGodina = year % 4 == 0;
		int maxDaysInCurrentMonth = 0;

		//If it is February
		if (month == 2) maxDaysInCurrentMonth = 28 + visokosnaGodina;
		//If it is April or June
		else if (month % 2 == 0 && month <= 6) maxDaysInCurrentMonth = 30;
		//If it is September or November
		else if (month % 2 == 1 && month >= 9) maxDaysInCurrentMonth = 30;
		//If it is January, March, May, July, August October, December
		else maxDaysInCurrentMonth = 31;

		day++;

		//If the next day is the first day of another month
		if (day > maxDaysInCurrentMonth)
		{
			month++;
			day -= maxDaysInCurrentMonth;
		}

		//If the current date is 31st of December
		if (month > 12)
		{
			year++;
			month = 1;
		}
	}

	cout << "The next date is : " << day << "." << month << "." << year;
}

int main()
{
	int day, month, year;
	cout << "Enter the starting date(day, month, year): "; cin >> day >> month >> year;

	int daysPassed;
	cout << "Enter the number of days passed: "; cin >> daysPassed;

	returnDate(day, month, year, daysPassed);
}