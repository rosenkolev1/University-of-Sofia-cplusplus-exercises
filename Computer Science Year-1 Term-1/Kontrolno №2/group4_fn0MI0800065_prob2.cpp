// Zada4a 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

bool hasRepeatingDigits(int number)
{
    int numberCopy = number;
    int numberCount = 0;
    while (numberCopy != 0)
    {
        numberCopy /= 10;
        numberCount++;
    }

    if (number == 0) numberCount = 1;

    int digitsArr[100];

    for (int i = 0; i < numberCount; i++)
    {
        int digit = number % 10;
        number /= 10;
        digitsArr[i] = digit;
    }

    for (int i = 0; i < numberCount; i++)
    {
        const int currentDigit = digitsArr[i];
        for (int y = 0; y < numberCount; y++)
        {
            int comparedDigit = digitsArr[y];

            if (currentDigit == comparedDigit && i != y) return true;
        }
    }

    return false;
}

int* collect(int matrix[][30], int n, int &repeatingDigitsNumbersCount)
{
    int* newArray = new int[1];
    int currentNewArraySize = 0;

    for (int row = n - 1; row >= 0; row--)
    {
        int col = 0;
        int oldRowValue = row;
        while (col < n && row < n)
        {
            int currentNumber = matrix[row][col];
            bool numberHasRepeatingDigits = hasRepeatingDigits(currentNumber);

            if (numberHasRepeatingDigits)
            {
                currentNewArraySize++;
                int* copyArray = new int[currentNewArraySize - 1];
                for (int i = 0; i < currentNewArraySize - 1; i++)
                {
                    copyArray[i] = newArray[i];
                }

                delete[] newArray;
                newArray = new int[currentNewArraySize];

                for (int i = 0; i < currentNewArraySize - 1; i++)
                {        
                    newArray[i] = copyArray[i];
                }
                newArray[currentNewArraySize - 1] = currentNumber;

                delete[] copyArray;
            }

            row++;
            col++;
        }

        row = oldRowValue;
    }

    for (int col = 1; col < n; col++)
    {
        int row = 0;
        int oldCol = col;

        while (row < n && col < n)
        {
            int currentNumber = matrix[row][col];
            bool numberHasRepeatingDigits = hasRepeatingDigits(currentNumber);

            if (numberHasRepeatingDigits)
            {
                currentNewArraySize++;
                int* copyArray = new int[currentNewArraySize - 1];
                for (int i = 0; i < currentNewArraySize - 1; i++)
                {
                    copyArray[i] = newArray[i];
                }

                delete[] newArray;
                newArray = new int[currentNewArraySize];

                for (int i = 0; i < currentNewArraySize - 1; i++)
                {
                    newArray[i] = copyArray[i];
                }
                newArray[currentNewArraySize - 1] = currentNumber;

                delete[] copyArray;
            }

            row++;
            col++;
        }

        col = oldCol;
    }

    repeatingDigitsNumbersCount = currentNewArraySize;

    return newArray;
}

void printMatrix(int matrix[900], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << matrix[i] << " ";
    }
}

void printMatrix(int matrix[][30], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int y = 0; y < n; y++)
        {
            cout << matrix[i][y] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int matrix[30][30];

    int n = 0;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int y = 0; y < n; y++)
        {
            cin >> matrix[i][y];
        }
    }

    printMatrix(matrix, n);

    int repeatingDigitsNumbersCount = 0;

    cout << endl;

    int* newArray = collect(matrix, n, repeatingDigitsNumbersCount);

    printMatrix(newArray, repeatingDigitsNumbersCount);
}
