// Game.App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameUI.h"

//bool isCommandValid()
//{
//    selection == nullptr ||
//        (strcmp(selection, GlobalConstants::COMMAND_MAINMENU_START) != 0 && strcmp(selection, GlobalConstants::COMMAND_MAINMENU_END) != 0)
//
//}

char gameState[] = "Main menu default selection";

void registerUserScreenPrint()
{
    const char** textArray = new const char* [2];
    textArray[0] = GlobalConstants::REGISTER;
    textArray[1] = GlobalConstants::RETURN_TEXT;
    //Screen Print
    GameUI::printScreenWithText(textArray, 2, 144);
}

bool registerUser()
{
    //Screen Print
    registerUserScreenPrint();

    while (true)
    {
        char selection[100];
        std::cin >> selection;



        //if (selection == nullptr ||
        //    (strcmp(selection, GlobalConstants::COMMAND_LOGIN_START) != 0 && strcmp(selection, GlobalConstants::COMMAND_REGISTER_START) != 0)
        //    )
        //{
        //    // Print on a single line without screen borders
        //    //TODO: IMPLEMENT ERROR LOOP GAME FUNCTION HERE
        //    GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
        //    continue;
        //}
        //else if (strcmp(selection, GlobalConstants::COMMAND_RETURN) == 0)
        //{
        //    //return to previous screen somehow
        //    return true;
        //}
    }
}

void loginOrRegisterScreenPrint()
{
    const char** textArray = new const char* [2];
    textArray[0] = GlobalConstants::LOGIN_OR_REGISTER;
    textArray[1] = GlobalConstants::RETURN_TEXT;
    //Screen Print
    GameUI::printScreenWithText(textArray, 2, 55);
}

bool loginOrRegister()
{
    //Screen Print
    loginOrRegisterScreenPrint();

    while (true)
    {
        char selection[100];
        std::cin >> selection;

        if (selection == nullptr ||
            (strcmp(selection, GlobalConstants::COMMAND_LOGIN_START) != 0 && 
             strcmp(selection, GlobalConstants::COMMAND_REGISTER_START) != 0 && 
             strcmp(selection, GlobalConstants::COMMAND_RETURN) != 0) 
            )
        {
            // Print on a single line without screen borders
            //TODO: IMPLEMENT ERROR LOOP GAME FUNCTION HERE
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
        else if (strcmp(selection, GlobalConstants::COMMAND_LOGIN_START) == 0)
        {
            //Start the login procedure
        }
        else if (strcmp(selection, GlobalConstants::COMMAND_REGISTER_START) == 0)
        {
            //Start the register procedure
            bool returnToScreen = registerUser();
            if (returnToScreen)
            {
                loginOrRegisterScreenPrint();
            }
        }
        else if (strcmp(selection, GlobalConstants::COMMAND_RETURN) == 0)
        {
            //return to previous screen
            return true;
        }
    }
}

void startUpScreenPrint()
{
    //Screen print
    const char** textArray = new const char* [3];
    textArray[0] = GlobalConstants::WELCOME_STARTSCREEN_TEXT;
    textArray[1] = GlobalConstants::BUTTON_START;
    textArray[2] = GlobalConstants::BUTTON_END;
    GameUI::printScreenWithText(textArray, 3, 117);
}

void startUp()
{
    //Screen print
    startUpScreenPrint();

    // Start the game/selection loop
    while (true)
    {
        char selection[100];
        //std::cin.clear();
        //std::cin.getline(selection, 100);
        std::cin >> selection;
        //If user writes nonsense data
        if (selection == nullptr ||
            (strcmp(selection, GlobalConstants::COMMAND_MAINMENU_START) != 0 && strcmp(selection, GlobalConstants::COMMAND_MAINMENU_END) != 0)
            )
        {
            // Print on a single line without screen borders
            //TODO: IMPLEMENT ERROR LOOP GAME FUNCTION HERE
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
        else if (strcmp(selection, GlobalConstants::COMMAND_MAINMENU_END) == 0)
        {
            //End the game
            //TODO: IMPLEMENT ENDING GAME FUNCTION HERE
            GameUI::printScreenWithText(GlobalConstants::GAME_END);
            break;
        }
        else if (strcmp(selection, GlobalConstants::COMMAND_MAINMENU_START) == 0)
        {
            //Start the actual game by trying to log in first
            bool restartCycle = loginOrRegister();
            if (restartCycle)
            {
                startUpScreenPrint();
                continue;
            }
        }
    }
}

int main()
{
    startUp();
}
