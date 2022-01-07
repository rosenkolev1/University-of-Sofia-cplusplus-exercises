// Kontrolno_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

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
	bool hasBeenFoundBonus = false;

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
			secondArr[y + 1] = secondArr[y];
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
			else if (startChecking == false)
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

			if (firstArrChar != secondArrChar)
			{
				startChecking = false;
				startPos = -1;
			}

		}
	}

	//BONUS
	for (int i = 0; i < size2; i++)
	{
		//Rotate the second array once
		char lastChar = secondArr[size2 - 1];
		for (int y = size2 - 2; y >= 0; y--)
		{
			secondArr[y + 1] = secondArr[y];
		}
		secondArr[0] = lastChar;

		startPos = -1;
		startChecking = false;

		int counter = 0;
		int indexesFoundChars[1024] = {};

		//Search for the second array in the first one
		for (int y = 0; y < size1; y++)
		{
			char firstArrChar = firstArr[y];
			char secondArrChar = secondArr[counter];

			if (firstArrChar == secondArrChar)
			{
				indexesFoundChars[counter] = y;
				counter++;
				//Success
				if (counter >= size2)
				{
					hasBeenFoundBonus = true;
					cout << "Rotation ";
					for (int z = 0; z < size2; z++)
					{
						cout << secondArr[z];
					}
					cout << " found after deleting characters: ";
					for (int d = 0; d < indexesFoundChars[0]; d++)
					{
						cout << d << " ";
					}
					for (int z = 0; z < size2-1; z++)
					{
						int startIndexForDeletion = indexesFoundChars[z];
						int endIndexForDeletion = indexesFoundChars[z+1];

						for (int d = startIndexForDeletion + 1; d < endIndexForDeletion; d++)
						{
							cout << d << " ";
						}
					}
					for (int d = indexesFoundChars[counter - 1] + 1; d < size1; d++)
					{
						cout << d << " ";
					}

				}
			}

		}
	}

	if (hasBeenFoundBonus == false && hasBeenFound == false)
	{
		cout << "No rotation found!";
	}
}

int main()
{
	exerciseThree();
}


