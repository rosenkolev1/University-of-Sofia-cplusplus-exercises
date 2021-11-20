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
    _setmode(_fileno(stdout), _O_U16TEXT);

    string a = "";
    wcout << L"Привет!!!!!" << endl;

    cin >> a;

    return 0;
}

