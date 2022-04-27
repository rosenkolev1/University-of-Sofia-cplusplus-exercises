#pragma once

#include "GameController.h"
#include <iostream>
#include "..\Game.GlobalConstants\GlobalConstants.h"
#include "..\Game.UI/GameUI.h"
#include "..\Game.IOS/FileSystem.h"
#include "..\Game.IOS\ConsoleSystem.h"



void GameController::playingLevelScreenPrint()
{

}

bool GameController::playingLevel()
{
    playingLevelScreenPrint();

    while (true)
    {
        char* selection = new char[10000];


        bool returnToScreen = false;
        
        if (returnToScreen)
        {
            //Return to last screen
            return true;
        }
    }

    return false;
}

void GameController::registerUserScreenPrint()
{
    const char** textArray = new const char* [2];
    textArray[0] = GlobalConstants::REGISTER;
    textArray[1] = GlobalConstants::RETURN_TEXT;
    //Screen Print
    GameUI::printScreenWithText(textArray, 2, 300); 
}

bool GameController::registerUser()
{
    //Screen Print
    registerUserScreenPrint();

    while (true)
    {
        char selection[1000];
        char firstChar = (char)std::cin.peek();
        if (firstChar == '\0' || firstChar == '\n') std::cin.ignore();
        std::cin.getline(selection, 1000);
        std::cin.clear();

        bool textIsValid = true;

        size_t splitStringsCount = 0;
        char** splitInput = ConsoleSystem::splitString(selection, GlobalConstants::COMMAND_DELIM, splitStringsCount);
        char* username = splitStringsCount == 2 ? splitInput[0] : nullptr;
        char* password = splitStringsCount == 2 ? splitInput[1] : nullptr;

        // Validate if text is inputted in the correct format
        textIsValid = FileSystem::usernameIsValid(username) && FileSystem::passwordIsValid(password);

        if (strcmp(selection, GlobalConstants::COMMAND_RETURN) == 0)
        {
            //Clear memory for input from console
            ConsoleSystem::deleteArrayOfStrings(splitInput, splitStringsCount);

            //Return to previous screen
            return true;
        }
        if (selection == nullptr || !textIsValid)
        {
            //Clear memory for input from console
            ConsoleSystem::deleteArrayOfStrings(splitInput, splitStringsCount);

            // Print on a single line without screen borders
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
        else if (textIsValid)
        {
            //Check if the user hasn't been registered already
            bool userIsRegistered = FileSystem::userIsRegistered(username);
            if (userIsRegistered)
            {
                   GameUI::printLineNoBorders(GlobalConstants::REGISTER_USERNAME_TAKEN);
                   GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);

                   //Clear memory for input from console
                   ConsoleSystem::deleteArrayOfStrings(splitInput, splitStringsCount);

                   continue;
             }
            
             //Register the user, print the successful registration text and then send the user back to the login or register screen
             FileSystem::registerUser(username, password);
            
             GameUI::printLineNoBorders(GlobalConstants::REGISTER_SUCCESS);

             //Clear memory for input from console
             ConsoleSystem::deleteArrayOfStrings(splitInput, splitStringsCount);
            
             //Return to previous screen
             return true;           
        }

    }
}

void GameController::loginUserScreenPrint()
{
    const char** textArray = new const char* [2];
    textArray[0] = GlobalConstants::LOGIN;
    textArray[1] = GlobalConstants::RETURN_TEXT;
    //Screen Print
    GameUI::printScreenWithText(textArray, 2, 60);
}

bool GameController::loginUser()
{
    loginUserScreenPrint();

    while (true)
    {
        char selection[1000];
        char firstChar = (char)std::cin.peek();
        if (firstChar == '\0' || firstChar == '\n') std::cin.ignore();
        std::cin.getline(selection, 1000);
        std::cin.clear();

        bool returnToScreen = false;
        bool textIsValid = true;

        size_t splitStringsCount = 0;
        char** splitInput = ConsoleSystem::splitString(selection, GlobalConstants::COMMAND_DELIM, splitStringsCount);
        char* username = splitStringsCount == 2 ? splitInput[0] : nullptr;
        char* password = splitStringsCount == 2 ? splitInput[1] : nullptr;

        // Validate if text is inputted in the correct format
        textIsValid = FileSystem::usernameIsValid(username) && FileSystem::passwordIsValid(password);

        if (strcmp(selection, GlobalConstants::COMMAND_RETURN) == 0)
        {
            //Clear memory for input from console
            ConsoleSystem::deleteArrayOfStrings(splitInput, splitStringsCount);

            //Return to previous screen
            return true;
        }
        if (selection == nullptr || !textIsValid)
        {
            //Clear memory for input from console
            ConsoleSystem::deleteArrayOfStrings(splitInput, splitStringsCount);

            // Print on a single line without screen borders
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
        else if (textIsValid)
        {
            bool userExists = FileSystem::userIsRegistered(username);

            if (!userExists)
            {
                GameUI::printLineNoBorders(GlobalConstants::LOGIN_USERNAME_TAKEN);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);

                //Clear memory for input from console
                ConsoleSystem::deleteArrayOfStrings(splitInput, splitStringsCount);

                continue;
            }

            GameUI::printLineNoBorders("Game Starting...");
            returnToScreen = playingLevel();
        }

        if (returnToScreen)
        {
            //Return to the last screen
            return true;
        }
    }
}

void GameController::loginOrRegisterScreenPrint()
{
    const char** textArray = new const char* [2];
    textArray[0] = GlobalConstants::LOGIN_OR_REGISTER;
    textArray[1] = GlobalConstants::RETURN_TEXT;
    //Screen Print
    GameUI::printScreenWithText(textArray, 2, 55);
}

bool GameController::loginOrRegister()
{
    //Screen Print
    loginOrRegisterScreenPrint();

    while (true)
    {
        char selection[100];
        std::cin >> selection;

        bool returnToScreen = false;

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
            //TODO: Start the login procedure
            returnToScreen = loginUser();
        }
        else if (strcmp(selection, GlobalConstants::COMMAND_REGISTER_START) == 0)
        {
            //Start the register procedure
            returnToScreen = registerUser();
        }
        else if (strcmp(selection, GlobalConstants::COMMAND_RETURN) == 0)
        {
            //Return to previous screen
            return true;
        }

        if (returnToScreen)
        {
            loginOrRegisterScreenPrint();
        }
    }
}

void GameController::startUpScreenPrint()
{
    //Screen print
    const char** textArray = new const char* [3];
    textArray[0] = GlobalConstants::WELCOME_STARTSCREEN_TEXT;
    textArray[1] = GlobalConstants::BUTTON_START;
    textArray[2] = GlobalConstants::BUTTON_END;
    GameUI::printScreenWithText(textArray, 3, 117);
}

void GameController::startUp()
{
    //Screen print
    startUpScreenPrint();

    // Start the game/selection loop
    while (true)
    {
        char selection[100];
        std::cin >> selection;

        bool returnToScreen = false;

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
            returnToScreen = loginOrRegister();

        }

        if (returnToScreen)
        {
            startUpScreenPrint();
        }
    }
}