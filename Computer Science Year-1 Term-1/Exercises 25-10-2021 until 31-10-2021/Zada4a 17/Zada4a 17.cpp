// Zada4a5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;

	for (int i = 0; i < n - 1; i++)
	{
		for (int y = 0; y < n - 1 - i; y++)
		{
			cout << " ";
		}

		for (int y = 0; y < i + 1; y++)
		{
			cout << "* ";
		}

		cout << endl;
	}

	for (int i = 0; i < n; i++)
	{
		cout << "* ";
	}
	cout << endl;

	for (int i = 0; i < n-1; i++)
	{
		for (int y = 0; y < i + 1; y++)
		{
			cout << " ";
		}

		for (int y = 0; y < n - 1 - i; y++)
		{
			cout << "* ";
		}

		cout << endl;
	}

	//----------------------------------------------------------

	/*for (int i = 1; i < n*2; i++)
	{
		for (int y = 0; y < n; y++)
		{
			cout << (y >= abs(n - i) ? "* " : " ");
		}
		cout << endl;
	}*/

	//----------------------------------------------------------

	/*for (int i = 0; i < n; i++)
	{
		for (int y = 0; y < n - 1 - i; y++)
		{
			cout << " ";
		}

		for (int y = 0; y < i + 1; y++)
		{
			cout << "* ";
		}

		cout << endl;
	}

	for (int i = 0; i < n - 1; i++)
	{
		for (int y = 0; y < 1 + i; y++)
		{
			cout << " ";
		}

		for (int y = 0; y < n - 1 - i; y++)
		{
			cout << "* ";
		}

		cout << endl;
	}*/
}

