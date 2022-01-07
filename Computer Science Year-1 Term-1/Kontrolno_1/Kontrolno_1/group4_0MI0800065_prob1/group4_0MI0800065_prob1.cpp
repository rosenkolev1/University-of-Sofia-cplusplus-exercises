// Kontrolno_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

void exerciseOne()
{
	int n, k;
	int startPos = 0, endPos = 0;
	int c = 1;
	bool isSearching = false;
	int appendingInt = 0;
	int appendingIntDigitsCount = 0;

	cin >> n >> k;
	int kCopy = k;
	int nCopy = n;

	n = abs(n);

	while (n != 0)
	{
		int digitOfN = n % 10;
		int digitOfK = kCopy % 10;

		if (kCopy == 0 && isSearching)
		{
			endPos = c--;
			break;
		}

		if (digitOfN == digitOfK && isSearching == false && c > 1)
		{
			isSearching = true;
			startPos = c;
		}
		else if (digitOfN != digitOfK && isSearching == true)
		{
			isSearching = false;
			kCopy = k;
			continue;
		}

		if (digitOfN == digitOfK)
		{
			kCopy /= 10;
		}

		n /= 10;
		c++;
	}

	for (int i = 1; i < startPos; i++)
	{
		int digitOfN = nCopy % 10;
		appendingInt += pow(10, i - 1) * digitOfN;
		nCopy /= 10;
	}	

	if (isSearching == true && n != 0 && startPos >= 2 && appendingInt >= pow(10, startPos - 2))
	{
		cout << "True";
	}
	else cout << "False";
}

int main()
{
	exerciseOne();
}


