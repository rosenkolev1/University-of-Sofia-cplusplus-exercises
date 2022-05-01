#pragma once

#include "GameController.h"
#include <iostream>
#include "..\Game.GlobalConstants\GlobalConstants.h"
#include "..\Game.UI/GameUI.h"
#include "..\Game.IOS/FileSystem.h"
#include "..\Game.IOS\ConsoleSystem.h"

User* GameController::currentUser = nullptr;

//TODO: change this screen depending on the role of the user
void GameController::mainMenuLoggedScreenPrint()
{
    size_t maxSize = 88;
    char** textArray = new char* [5];
    bool continueGame = currentUser->level > 1;
    size_t textArraySize = continueGame ? 4 : 5;

    for (size_t i = 0; i < textArraySize; i++)
    {
        textArray[i] = new char[maxSize];
    }

    //Make text with current level
    char* currentLevelText = new char[100]
    {
        "Current Level: "
    };
    const char* levelText = ConsoleSystem::parseToString(currentUser->level);
    strcat(currentLevelText, levelText);
    strcat(currentLevelText, "\n");
    strcpy(textArray[0], currentLevelText);

    //Make text with current lives
    char currentLivesText[100] = "Lives: ";
    const char* livesText = ConsoleSystem::parseToString(currentUser->lives);
    strcat(currentLivesText, livesText);
    strcat(currentLivesText, "\n");
    strcpy(textArray[1], currentLivesText);

    if (continueGame)
    {
        textArray[2] = (char*)GlobalConstants::MAINMENU_LOGGED_CONTINUEGAME;
        textArray[3] = (char*)GlobalConstants::MAINMENU_LOGGED_RESTARTGAME;        
    }
    else
    {
        textArray[2] = (char*)GlobalConstants::MAINMENU_LOGGED_STARTGAME;
        textArray[3] = (char*)GlobalConstants::MAINMENU_LOGGED_RETURN_TEXT;
    }
    textArray[textArraySize - 1] = (char*)GlobalConstants::MAINMENU_LOGGED_RETURN_TEXT;
    //Screen Print
    GameUI::printScreenWithText((const char**)textArray, textArraySize, maxSize);

    //Delete dynamically allocated memory
    delete[] livesText;
    delete[] levelText;
}

bool GameController::mainMenuLogged()
{
    mainMenuLoggedScreenPrint();

    while (true)
    { 
        char* selection = new char[10000];
        std::cin >> selection;
        bool returnToScreen = false;
        bool continueGame = currentUser->level > 1;
        //If the command is invalid while a game hasnt already been started
        if (strcmp(selection, GlobalConstants::COMMAND_RETURN) == 0)
        {
            //Return to last screen
            return true;
        }
        //Users starts a new game
        else if (!continueGame && strcmp(selection, GlobalConstants::COMMAND_GAME_START) == 0)
        {
            std::cout << "do something";
        }
        //User continues a game or restarts a started game
        else if (continueGame &&
            (strcmp(selection, GlobalConstants::COMMAND_GAME_RESTART) == 0 ||
                strcmp(selection, GlobalConstants::COMMAND_GAME_CONTINUE) == 0))
        {
            std::cout << "do something";
        }
        //If the command is invalid
        else 
        {
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }

        if (returnToScreen)
        {
            //Return to this screen
            mainMenuLoggedScreenPrint();
            continue;
        }
    }

    return false;
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
            bool userExists = FileSystem::userIsRegisteredWithPassword(username, password);
            currentUser = FileSystem::getUser(username);

            //TODO: If this user is deleted, then print a message to them from the second table of the database
            if (currentUser->isDeleted)
            {
                GameUI::printLineNoBorders(GlobalConstants::USER_BANNED);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);

                //Clear memory for input from console
                ConsoleSystem::deleteArrayOfStrings(splitInput, splitStringsCount);

                continue;
            }

            if (!userExists)
            {
                GameUI::printLineNoBorders(GlobalConstants::LOGIN_USERNAME_TAKEN);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);

                //Clear memory for input from console
                ConsoleSystem::deleteArrayOfStrings(splitInput, splitStringsCount);

                continue;
            }

            GameUI::printLineNoBorders("Game Starting...");
            returnToScreen = mainMenuLogged();
        }

        if (returnToScreen)
        {
            //Return to this screen
            loginUserScreenPrint();
            continue;
        }
    }
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
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
        else if (strcmp(selection, GlobalConstants::COMMAND_LOGIN_START) == 0)
        {
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
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
        else if (strcmp(selection, GlobalConstants::COMMAND_MAINMENU_END) == 0)
        {
            //End the game
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
