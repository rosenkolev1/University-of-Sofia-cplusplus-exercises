// Zada4a5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
    int a, b;

    cin >> a >> b;

    int kratno = a > b ? a : b;

    if (a == 0 || b == 0) cout << "programata se s4upi kopele";

    while (kratno % a != 0 || kratno % b != 0)
    {
        kratno++;
    }

    cout << kratno;
}

