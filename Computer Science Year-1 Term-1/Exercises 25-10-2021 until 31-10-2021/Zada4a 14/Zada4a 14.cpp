// Zada4a5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		for (int y = 0; y < n; y++)
		{
			cout << "* ";
		}
		cout << endl;
	}
}

