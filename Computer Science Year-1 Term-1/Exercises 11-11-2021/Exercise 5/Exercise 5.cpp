// Exercise 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

bool checkIfNumberIsPrime(int number)
{
	for (int i = 2; i <= number/2; i++)
	{
		if (number % i == 0) return false;
	}

	return (number != 0 ? true : false);
}

void printAllPrimeNumbersInRange(int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (checkIfNumberIsPrime(i)) cout << i << " | ";
	}
}

int main()
{
	int n;
	cin >> n;
	
	printAllPrimeNumbersInRange(n);
}