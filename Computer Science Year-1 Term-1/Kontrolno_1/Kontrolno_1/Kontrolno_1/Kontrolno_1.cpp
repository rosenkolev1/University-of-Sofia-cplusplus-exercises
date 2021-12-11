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

	cin >> n >> k;
	int kCopy = k;

	while (n != 0)
	{
		int digitOfN = n % 10;
		int digitOfK = kCopy % 10;

		if (kCopy == 0 && isSearching)
		{
			endPos = c--;
			break;
		}

		if (digitOfN == digitOfK && isSearching == false)
		{
			isSearching = true;
			startPos = c;
		}
		else if (digitOfN != digitOfK)
		{
			isSearching = false;
			kCopy = k;
		}

		if (digitOfN == digitOfK)
		{
			kCopy /= 10;
		}


		n /= 10;
		c++;
	}

	if (isSearching == true && n != 0 && startPos >= 2)
	{
		cout << "True";
	}
	else cout << "False";
}

//Exercise 2
bool adjacentNumber(int n)
{
	int digitsCount = 0;
	int digits[100];

	if (n >= -9 && n <= 9) return true;

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

	int min = a-1;
	int max = b+1;

	bool adjacentNumberFound = false;

	for (int i = a; i <= b; i++)
	{
		if(adjacentNumber(i))
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

//Exercise 3
void rotationFoundOutput(int endPos, int startPos, int sizeOfSecondArr, char secondArr[1024], int sizeOfFirstArr)
{
	cout << "Rotation ";
	for (int z = 0; z < sizeOfSecondArr; z++)
	{
		cout << secondArr[z];
	}
	cout << " found after deleting " << startPos << " characters from the start and " << sizeOfFirstArr - endPos - 1 << " characters from the end.";
}

void exerciseThree()
{
	int size1, size2;
	cin >> size1 >> size2;
	char firstArr[1024];
	char secondArr[1024];

	int startPos = -1;
	bool startChecking = false;
	bool hasBeenFound = false;

	for (int i = 0; i < size1; i++)
	{
		char c;
		cin >> c;
		firstArr[i] = c;
	}

	for (int i = 0; i < size2; i++)
	{
		char c;
		cin >> c;
		secondArr[i] = c;
	}

	for (int i = 0; i < size2; i++)
	{
		//Rotate the second array once
		char lastChar = secondArr[size2 - 1];
		for (int y = size2 - 2; y >= 0; y--)
		{
			secondArr[y+1] = secondArr[y];
		}
		secondArr[0] = lastChar;

		startPos = -1;
		startChecking = false;

		//Search for the second array in the first one
		for (int y = 0; y < size1; y++)
		{
			char firstArrChar = firstArr[y];
			char secondArrChar = NULL;

			if (startChecking == true && y - startPos < size2)
			{
				secondArrChar = secondArr[y - startPos];
			}
			else if(startChecking == false)
			{
				secondArrChar = secondArr[0];
			}

			if (firstArrChar == secondArrChar && startChecking == true && y - startPos == size2 - 1)
			{
				rotationFoundOutput(y, startPos, size2, secondArr, size1);
				return;
			}

			if (firstArrChar == secondArrChar && startChecking == false)
			{
				startPos = y;
				startChecking = true;

				// If the length of the second array is 1
				if (size2 == 1)
				{
					rotationFoundOutput(y, startPos, size2, secondArr, size1);
					return;
				}
			}

			if(firstArrChar != secondArrChar)
			{
				startChecking = false;
				startPos = -1;
			}

		}
	}

	if (hasBeenFound == false)
	{
		cout << "No rotation found!";
	}
}

int main()
{
	//exerciseOne();
	//exerciseTwo();
	//exerciseThree();
}


