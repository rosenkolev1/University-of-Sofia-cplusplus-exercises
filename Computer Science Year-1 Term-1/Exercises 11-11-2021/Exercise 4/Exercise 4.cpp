// Exercise 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

double powerOf(int number, int power)
{
    int product = 1;
	for (int i = 1; i <= abs(power); i++)
	{
		product *= number;
	}

	if (power < 0 && product != 0) return 1 / (double)product;

	return product;
}

int main()
{
	int n, m;
	cin >> n >> m;

	cout << powerOf(n, m);
}