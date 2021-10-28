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
			if (y == 0 || y == n - 1)
			{
				if ((i == 0 || i == n - 1)) cout << "+ ";
				else if (i > 0 && i < n - 1) cout << "| ";
			}		
			else
			{
				cout << "- ";
			}
			
		}
		cout << endl;
	}
}

