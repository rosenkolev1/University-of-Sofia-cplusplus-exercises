// Zada4a5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;

	int digitsCount = 1;

	if (n < 0) n *= -1;

	int numberCopy = n;

	while (true)
	{
		numberCopy /= 10;
		if (numberCopy == 0) break;

		digitsCount++;
	}

	for (int i = 1; i <= digitsCount; i++)
	{
		int currentDigit = (n / (int)pow(10, i-1)) % 10;

		int secondCopyOfNumber = n;

		for (int y = 1; y <= digitsCount; y++)
		{
			int digitToCompareWith = secondCopyOfNumber % 10;

			if (digitToCompareWith == currentDigit && i != y)
			{
				cout << "The numbers contains two of the same digits";
				return 0;
			}

			secondCopyOfNumber /= 10;
		}
	}

	cout << "The numbers doesn't contain two of the same digits";
}

