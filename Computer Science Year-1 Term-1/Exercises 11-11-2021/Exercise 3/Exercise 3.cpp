// Exercise 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int sign(int a)
{
    if (a == 0) return 0;
    else if (a < 0) return -1;
    else if (a > 0) return 1;
}

int main()
{
    int x, y;
    cin >> x >> y;
    cout << (sign(x) + sign(y)) * sign(x + y);
}