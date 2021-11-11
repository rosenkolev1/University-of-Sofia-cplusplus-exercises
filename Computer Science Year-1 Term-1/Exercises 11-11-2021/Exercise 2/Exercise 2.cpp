// Exercise 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int returnLargestNumber(int a, int b, int c)
{
    return (a >= b ? (a >= c ? a : c) : (b >= c ? b : c));
}

int main()
{
    int a, b, c;
    cin >> a >> b >> c;

    cout << "The largest number is: " << returnLargestNumber(a, b, c);
}