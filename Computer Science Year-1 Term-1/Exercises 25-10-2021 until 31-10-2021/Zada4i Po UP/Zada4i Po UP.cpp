// Zada4i Po UP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

	int digitsCount = 1;

	int numberCopy = n;
	while (true)
	{
		numberCopy /= 10;
		if (numberCopy == 0) break;

		digitsCount++;
	}

	for (int i = 1; i <= digitsCount/2; i++)
	{
		int firstDigit = (n / (int)pow(10, digitsCount - i));
		if (firstDigit > 9) firstDigit %= 10;

		int lastDigit = (n / (int)(pow(10, i - 1))) % 10;

		if (firstDigit != lastDigit)
		{
			cout << "GUZ"; 
			return 100;
		}
	}

	cout << "number is symmetrical";
}
