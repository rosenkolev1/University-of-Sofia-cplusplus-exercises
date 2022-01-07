// Kontrolno_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

//Exercise 2
bool adjacentNumber(int n)
{
	int digitsCount = 0;
	int digits[100];

	if (n < 0) n = abs(n);

	if (n <= 9) return true;

	while (n != 0)
	{
		digits[digitsCount] = n % 10;
		digitsCount++;
		n /= 10;
	}

	for (int i = 0; i < digitsCount - 1; i++)
	{
		if (digits[i] == digits[i + 1]) return false;
	}

	return true;
}

void exerciseTwo()
{
	int a, b;
	cin >> a >> b;

	if (a > b)
	{
		cout << "Can't do that good sir!";
		return;
	}

	int min = a - 1;
	int max = b + 1;

	bool adjacentNumberFound = false;

	for (int i = a; i <= b; i++)
	{
		if (adjacentNumber(i))
		{
			if (adjacentNumberFound == false)
			{
				adjacentNumberFound = true;
				min = i;
				max = i;
			}
			else
			{
				if (min > i) min = i;
				if (max < i) max = i;
			}
		}
	}

	if (adjacentNumberFound) cout << "The equation: " << max << " - " << min << " = " << max - min;
	else cout << "No adjacent numbers!";
}

int main()
{
	exerciseTwo();
}


