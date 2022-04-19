// Game.App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameUI.h"
#include "..\Game.IOS\FileSystem.cpp"

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

        //TODO: CHECK IF USERNAME AND PASSWORD ARE VALID
        //TODO: MAKE ANOTHER MODULE OF THE PROGRAM THAT WORKS WITH FILES

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

        textValidity = strlen(username) > 0 && strlen(password) > 0;

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
            //Register the user, print the successful registration text and then send the user back to the login or register screen
            FileSystem::registerUser(username, password);

            GameUI::printScreenWithText(GlobalConstants::REGISTER_SUCCESS);
            
            //Return to previous screen
            return true;
        }

        //if (selection == nullptr ||
        //    (strcmp(selection, GlobalConstants::COMMAND_LOGIN_START) != 0 && strcmp(selection, GlobalConstants::COMMAND_REGISTER_START) != 0)
        //    )
        //{
        //    // Print on a single line without screen borders
        //    //TODO: IMPLEMENT ERROR LOOP GAME FUNCTION HERE
        //    GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
        //    continue;
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

int main()
{
    startUp();
}
