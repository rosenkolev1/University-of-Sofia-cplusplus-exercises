// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

using namespace std;

int main()
{
    bool bit1, bit2, bit3, bit4, bit5, bit6, bit7, bit8, bit9 = 0; //0000 1111 1111

    //First number
    cin >> bit1;
    cin >> bit2;
    cin >> bit3;
    cin >> bit4;

    //Second number
    cin >> bit5;
    cin >> bit6;
    cin >> bit7;
    cin >> bit8;

    //Add the first bit
    if (bit4 & bit8)
    {
        bit8 = 0;
        bit7 = !bit7;
        if (!bit7)
        {
            bit6 = !bit6;
            if (!bit6)
            {
                bit5 = !bit5;
                if (!bit5)
                {
                    bit9 = !bit9;
                }
            }
        }     
    }
    else
    {
        bit8 = bit4 | bit8;
    }

    //Add the second bit
    if (bit7 & bit3)
    {
        bit7 = 0;
        bit6 = !bit6;
        if (!bit6)
        {
            bit5 = !bit5;
            if (!bit5)
            {
                bit9 = !bit9;
            }
        }
    }
    else
    {
        bit7 = bit3 | bit7;
    }

    //Add the third bit
    if (bit6 & bit2)
    {
        bit6 = 0;
        bit5 = !bit5;
        if (!bit5)
        { 
            bit9 = !bit9;
        }
    }
    else
    {
        bit6 = bit6 | bit2;
    }

    //Add the fourth bit
    if (bit5 & bit1)
    {
        bit5 = 0;
        bit9 = !bit9;
    }
    else
    {
        bit5 = bit5 | bit1;
    }

    cout << "Here is the binary number: " << bit9 << bit5 << bit6 << bit7 << bit8;
}

