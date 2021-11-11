// Exercise 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int reverseNumber(int a)
{
    int reversedNumber = 0;
    int c = 0;

    while (a != 0)
    {
        reversedNumber = reversedNumber * 10 + (a % 10);
        a /= 10;
        c++;
    }

    return reversedNumber;
}

bool checkIfNumberIsSymmetrical(int a) 
{
    int reversedNumber = reverseNumber(a);

    return reversedNumber == a;
}

int main()
{
    int a;
    cin >> a;

    cout << (checkIfNumberIsSymmetrical(a) ? "The number is symmetrical" : "The number is not symmetrical");
}

