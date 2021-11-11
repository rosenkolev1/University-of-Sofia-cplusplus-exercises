// Exercise 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int sumOfIntegers(int a, int b)
{
	return (a + b) * (b - a + 1) / 2;
}

int main()
{
	int a, b;
	cin >> a >> b;

	cout << "The sum is: " << sumOfIntegers(a, b);
}