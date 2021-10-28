// Zada4a5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
    int a, b;

    cin >> a >> b;

    while (a != b)
    {
        if (a < 0) a *= -1;
        if (b < 0) b *= -1;

        //Edge cases
        if (a == 0 && b != 0)
        {
            cout << b;
            return 0;
        }
        else if(a != 0 && b == 0)
        {
            cout << a;
            return 0;
        }

        if (a > b)
        {       
            a -= b;
        }
        else
        {
            b -= a;
        }
    }

    cout << a;
}

