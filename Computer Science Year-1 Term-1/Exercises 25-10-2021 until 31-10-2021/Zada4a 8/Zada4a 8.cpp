// Zada4a5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
    int n;
    cout << "Enter the number to convert: ";
    cin >> n;

    int binaryNumber = 0;

    for (int i = 0; n > 0; i++)
    {
        binaryNumber += n % 2 * pow(10, i);
        n = n / 2;
    }
    cout << "Binary of the given number= " << binaryNumber;
}

