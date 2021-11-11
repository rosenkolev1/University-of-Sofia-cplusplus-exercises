// Exercise 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

bool checkIfAverageOfDigitsIsMoreThan(int number, int average)
{
	number = abs(number);

	int sumOfDigits = 0;
	double countOfDigits = 0;
	double  averageOfDigits = 0;

	while (number != 0)
	{
		int lastDigit = number % 10;
		sumOfDigits += lastDigit;

		number /= 10;
		countOfDigits++;
	}

	averageOfDigits = countOfDigits != 0 ? sumOfDigits / countOfDigits : 0;

	return averageOfDigits >= average;
}

void printAllNumbers(int m, int n, int k)
{
	for (int i = m; i <= n; i++)
	{
		if (checkIfAverageOfDigitsIsMoreThan(i, k)) cout << i << " | ";
	}
}

int main()
{
	int m, n, k;
	cin >> m >> n >> k;

	printAllNumbers(m, n, k);
}