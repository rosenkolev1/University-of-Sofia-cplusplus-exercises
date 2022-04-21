// Kontrolno №2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstring>

using namespace std;

void SplitByDelimiter(char text[100], int textLength, char delimiter, string outputArr[2])
{
    outputArr[0] = "";
    outputArr[1] = "";

    int wordIndex = 0;
    int wordLettersCount = 0;

    for (int i = 0; i < textLength; i++)
    {
        char textChar = text[i];
        if (textChar != delimiter)
        {
            outputArr[wordIndex] += textChar;
            wordLettersCount++;
        }
        if (textChar == delimiter)
        {
            wordIndex++;
            wordLettersCount = 0;
        }
    }
}

char* minWord(string &inputString)
{
    string minString = "";
    bool minStringHasBeenSet = false;
    string currentWord = "";
    int indexOfMinString = -1;

    for (int i = 0; i < inputString.length(); i++)
    {
        char currentChar = inputString[i];
        if (isalpha(currentChar) || isalnum(currentChar))
        {
            currentWord += currentChar;
        }
        else
        {
            if (minStringHasBeenSet == false)
            {
                minString = currentWord;
                minStringHasBeenSet = true;
                currentWord = "";
                indexOfMinString = i;
            }
            else
            {
                if (minString > currentWord)
                {
                    minString = currentWord;
                    indexOfMinString = i;
                }
                currentWord = "";
            }
        }
    }

    /*char* minStringChars = new char[minString.length()];
    int charLength = minString.length();
    for (int i = 0; i < minString.length(); i++)
    {
        minStringChars[i] = minString[i];
    }*/



    return &inputString[indexOfMinString];
}

int main()
{
    string inputString = "";

    cin >> inputString;

    char* pointerToMinWord = minWord(inputString);

    cout << "The min word is: ";
    for (int i = 0; i < 10; i++)
    {
        cout << pointerToMinWord[i];
    }

    /*cout << "The min word is: " << *pointerToMinWord;*/
}
