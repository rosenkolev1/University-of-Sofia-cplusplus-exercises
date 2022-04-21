// Zada4a 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int returnIntFromCharacter(char characterForNumber, char letters[], int numbers[], int lettersCount)
{
    int indexOfLetter = -1;
    for (int i = 0; i < lettersCount; i++)
    {
        if (characterForNumber == letters[i])
        {
            indexOfLetter = i;
        }
    }

    if (indexOfLetter == -1) return 0;

    return numbers[indexOfLetter];
}

int calculate(string equation, int n, char letters[], int numbers[])
{
    int stringLength = equation.length();

    int umnojenieSum = 1;
    bool hasStartedUmnojenie = false;
    int numbersForAdditionCount = 0;
    int numbersForAdditionCounter = 0;

    int totalSum = 0;

    for (int i = 0; i < stringLength; i++)
    {
        char currentChar = equation[i];
        if (currentChar == '+')
        {
            numbersForAdditionCount++;
        }
    }
    numbersForAdditionCount++;

    int* numbersForAddition = new int[numbersForAdditionCount];

    for (int i = 0; i < stringLength; i++)
    {
        bool equationHasEnded = false;

        char currentChar = equation[i];
        if (currentChar == '.' && hasStartedUmnojenie == false)
        {
            char leftNumberChar = equation[i - 1];
            char rightNumberChar = equation[i + 1];

            int leftNumber = returnIntFromCharacter(leftNumberChar, letters, numbers, n);
            int rightNumber = returnIntFromCharacter(rightNumberChar, letters, numbers, n);

            umnojenieSum = leftNumber * rightNumber;
            i++;
            hasStartedUmnojenie = true;
        }
        else if (currentChar == '.' && hasStartedUmnojenie == true)
        {
            char rightNumberChar = equation[i + 1];
            int rightNumber = returnIntFromCharacter(rightNumberChar, letters, numbers, n);

            umnojenieSum *= rightNumber;
            i++;
        }

        if (hasStartedUmnojenie == true && currentChar != '.' && !isalpha(currentChar))
        { 
            hasStartedUmnojenie = false;
            numbersForAddition[numbersForAdditionCounter] = umnojenieSum;
            numbersForAdditionCounter++;
            umnojenieSum = 1;
        }
    }

    if (hasStartedUmnojenie)
    {
        hasStartedUmnojenie = false;
        numbersForAddition[numbersForAdditionCounter] = umnojenieSum;
        numbersForAdditionCounter++;
        umnojenieSum = 1;
    }

    //Check for the lone numbers to add
    for (int i = 0; i < stringLength - 1; i++)
    {
        char currentChar = equation[i];
        char nextChar = equation[i+1];
        if (currentChar == '+' && isalpha(nextChar))
        {
            if (i + 1 == stringLength - 1)
            {
                totalSum += returnIntFromCharacter(nextChar, letters, numbers, n);
            }
            else if(equation[i+2] == '+')
            {
                totalSum += returnIntFromCharacter(nextChar, letters, numbers, n);
            }
        }
    }

    //Sum the numbers
    for (int i = 0; i < numbersForAdditionCounter; i++)
    {
        totalSum += numbersForAddition[i];
    }

    return totalSum;
}

int main()
{
    string equation = "";
    int n = 0;

    cin >> equation;

    char letters[] = { 'b', 'c', 'a', 'd' };
    int numbers[] = { 5, 3, 2, 42 };

    cout << calculate(equation, 4, letters, numbers);
}

