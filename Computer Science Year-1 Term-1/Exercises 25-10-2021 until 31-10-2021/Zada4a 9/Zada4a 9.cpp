// Zada4a5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
	int number;
	int sum = 0;
	do
	{
		cin >> number;
		sum += number;
	} while (number != 0);

	cout << "The sum of the numbers: " << sum;
}

