// Zada4a5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;

	int sumOfDigits = 0;

	if (n < 0) n *= -1;

	while (n != 0)
	{
		int lastDigit = n % 10;
		n /= 10;

		sumOfDigits += lastDigit;
	}

	string sumOfDigitsIsDivisibleByThirteen = sumOfDigits % 13 == 0 ? ("The sum of the digits is divisible by 13") : "The sum of the digits is not divisible by 13";

	cout << sumOfDigitsIsDivisibleByThirteen;
}

