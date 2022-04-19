// Game.App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma once;
#include "GameController.h"

void GameController::registerUserScreenPrint()
{
    const char** textArray = new const char* [2];
    textArray[0] = GlobalConstants::REGISTER;
    textArray[1] = GlobalConstants::RETURN_TEXT;
    //Screen Print
    GameUI::printScreenWithText(textArray, 2, 144);
}

bool GameController::registerUser()
{
    //Screen Print
    registerUserScreenPrint();

    while (true)
    {
        char selection[100];
        std::cin >> selection;

        bool textValidity = true;

        //Check validity of name and password
        char username[GlobalConstants::USERNAME_LENGTH_MAX] = "";
        char password[GlobalConstants::PASSWORD_LENGTH_MAX] = "";

        int arrayCounter = 0;
        bool switchToPassword = false;
        for (size_t i = 0; i < strlen(selection); i++)
        {
            if (!switchToPassword && selection[i] != '|')
            {
                username[arrayCounter] = selection[i];
                arrayCounter++;
            }
            else if (!switchToPassword && selection[i] == '|')
            {
                //Set terminator for username and switch to password
                username[arrayCounter] = '\0';
                arrayCounter = 0;
                switchToPassword = true;
            }
            else if (switchToPassword && selection[i] != '|')
            {
                password[arrayCounter] = selection[i];
                arrayCounter++;
            }
            else if(switchToPassword && selection[i] == '|')
            {
                textValidity = false;
            }
        }
        //Set terminator for password
        password[arrayCounter] = '\0';

        //TODO: Add actual checks for username and password length and an already existing user and invalid symbols in the text, 
        // such as the delimiters used for the different rows and columns of the database!

        //Guz::ne6toSi("asd");
        //Guz guz;
        //guz.ne6toSi("asdsadasdadasd");
        textValidity = FileSystem::usernameIsValid(username) && FileSystem::passwordIsValid(password);

        if (strcmp(selection, GlobalConstants::COMMAND_RETURN) == 0)
        {
            //Return to previous screen
            return true;
        }
        if (selection == nullptr || !textValidity)
        {
            // Print on a single line without screen borders
            //TODO: IMPLEMENT ERROR LOOP GAME FUNCTION HERE
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
        else if (textValidity)
        {
            //Check if the user hasn't been registered already
            bool userIsRegistered = FileSystem::userIsRegistered(username);
            if (userIsRegistered)
            {
                GameUI::printLineNoBorders(GlobalConstants::REGISTER_USERNAME_TAKEN);
                continue;
            }

            //Register the user, print the successful registration text and then send the user back to the login or register screen
            FileSystem::registerUser(username, password);

            GameUI::printScreenWithText(GlobalConstants::REGISTER_SUCCESS);
            
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
            //TODO: IMPLEMENT ERROR LOOP GAME FUNCTION HERE
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
        else if (strcmp(selection, GlobalConstants::COMMAND_LOGIN_START) == 0)
        {
            //TODO: Start the login procedure

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
            returnToScreen  = loginOrRegister();
            
        }

        if (returnToScreen)
        {
            startUpScreenPrint();
        }
    }
}
