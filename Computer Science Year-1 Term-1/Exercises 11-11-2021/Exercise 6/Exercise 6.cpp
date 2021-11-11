// Exercise 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

bool checkIfNumberHasEqualNeighbouringDigits(int number)
{
	while (number != 0)
	{
		int lastDigit = number % 10;
		number /= 10;
		int secondToLastDigit = number % 10;

		if (lastDigit == secondToLastDigit) return true;
	}

	return false;
}

void printAllNumbers(int k, int l)
{
	for (int i = k; i <= l; i++)
	{
		if (checkIfNumberHasEqualNeighbouringDigits(i)) cout << i << " | ";
	}
}

int main()
{
	int k, l;
	cin >> k >> l;

	printAllNumbers(k, l);
}