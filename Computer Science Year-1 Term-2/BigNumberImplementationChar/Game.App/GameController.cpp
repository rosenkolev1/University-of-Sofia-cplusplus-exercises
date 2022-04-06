// Game.App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameUI.h"

void startUp()
{
    GameUI::printScreenWithText("Welcome to the BigNumber game!!!!", 33);
    char* someTestText = new char[10000];
    for (int i = 0; i < 105; i++)
    {
        someTestText[i] = 'A';
    }
    //GameUI::printScreenWithText(someTestText, 10000);
    GameUI::printScreenWithText(someTestText, 105);
    int a;
    std::cin >> a;
}

int main()
{
    startUp();
}
