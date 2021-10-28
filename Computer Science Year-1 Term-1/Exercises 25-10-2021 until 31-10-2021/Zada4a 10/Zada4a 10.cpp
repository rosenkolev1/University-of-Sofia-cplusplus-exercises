// Zada4a5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;

	if (n == 0) cout << n;

	if (n < 0) n *= -1;

	while(n != 0)
	{
		int lastDigit = n % 10;
		n /= 10;

		cout << lastDigit << endl;
	}
}

