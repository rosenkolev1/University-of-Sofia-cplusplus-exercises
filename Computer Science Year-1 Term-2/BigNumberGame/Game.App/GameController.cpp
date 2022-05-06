#pragma once

#include "GameController.h"
#include <iostream>
#include "..\Game.GlobalConstants\GlobalConstants.h"
#include "..\Game.UI/GameUI.h"
#include "..\Game.IOS/FileSystem.h"
#include "..\Project.StringManipulation\StringManip.h"
#include "..\Game.IOS\Seeder.h"

User* GameController::currentUser = nullptr;
bool GameController::returnToTitleScreen = false;

void GameController::deleteOwnAccountConfirmationScreenPrint()
{
    size_t maxSize = 73;
    const char** textArray = new const char* [3];
    textArray[0] = GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION;
    textArray[1] = GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_NO;
    textArray[2] = GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_YES;

    GameUI::printScreenWithText((const char**)textArray, 3, maxSize, GlobalConstants::DELETE_CONFIRM_TITLE);

    //Delete dynamic memory
    delete[] textArray;
}

bool GameController::deleteOwnAccountConfirmation()
{
    deleteOwnAccountConfirmationScreenPrint();

    while (true)
    {
        char* selection = new char[10000];
        std::cin >> selection;

        if (strcmp(selection, GlobalConstants::COMMAND_RETURN) == 0)
        {
            //Return to last screen
            return true;
        }
        //Delete account and return user to welcome screen
        else if (strcmp(selection, GlobalConstants::COMMAND_ACCOUNT_DELETE_CONFIRM) == 0)
        {
            //Delete the user's account
            FileSystem::deleteUser(currentUser->username, nullptr);

            //Set the current user to nullptr because it was deleted
            currentUser = nullptr;
            //If the user has deleted their own account, then send them a message to inform them of the account deletion
            GameUI::printLineNoBorders(GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_SUCCESS);

            //Return to title screen
            returnToTitleScreen = true;
            return true;
        }
        //Invalid command
        else 
        {
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
    }
}

void GameController::mainMenuLoggedScreenPrint()
{
    size_t maxSize = 88;
    bool continueGame = currentUser->level > 1;
    size_t textArraySize = continueGame ? 6 : 5;

    bool isAdmin = currentUser->role == UserRoles::Admin;
    //Change the textArraySize and textArray based on the user being or not being an admin
    if (isAdmin) textArraySize += 5;

    const char** textArray = new const char* [textArraySize];

    size_t textArrayIndex = 0;

    //Type out the fact that you are in admin profile
    if (isAdmin)
    {
        char loggedAsAdminText[100] =
        {
            "!!!LOGGED AS ADMIN!!!\n"
        };
        textArray[textArrayIndex++] = loggedAsAdminText;
    }

    //Make text with current level
    char currentLevelText[100];
    strcpy(currentLevelText, GlobalConstants::MAINMENU_LEVEL_TEXT);
    const char* levelText = StringManip::parseToString(currentUser->level);
    strcat(currentLevelText, levelText);
    strcat(currentLevelText, "\n");
    textArray[textArrayIndex++] = currentLevelText;

    //Make text with current lives
    char currentLivesText[100];
    strcpy(currentLivesText, GlobalConstants::MAINMENU_LIVES_TEXT);
    const char* livesText = StringManip::parseToString(currentUser->lives);
    strcat(currentLivesText, livesText);
    strcat(currentLivesText, "\n");
    textArray[textArrayIndex++] = currentLivesText;

    //Type out the appropriate things depending on the state of the game of the user
    if (continueGame)
    {
        textArray[textArrayIndex++] = GlobalConstants::MAINMENU_LOGGED_CONTINUEGAME;
        textArray[textArrayIndex++] = GlobalConstants::MAINMENU_LOGGED_RESTARTGAME;
    }
    else
    {
        textArray[textArrayIndex++] = GlobalConstants::MAINMENU_LOGGED_STARTGAME;
    }
    if(!isAdmin) textArray[textArrayIndex++] = GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT;//strcpy(textArray[textArrayIndex++], GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT);
    else
    {
        textArray[textArrayIndex++] = GlobalConstants::ADMIN_GETINFO;
        textArray[textArrayIndex++] = GlobalConstants::ADMIN_EXCLUDEFROMLEADERBOARD;
        textArray[textArrayIndex++] = GlobalConstants::ADMIN_DELETEACCOUNT;
        textArray[textArrayIndex++] = GlobalConstants::ADMIN_RECOVER;
        textArray[textArrayIndex++] = GlobalConstants::ADMIN_ADDHELPER;
    }

    textArray[textArrayIndex++] = GlobalConstants::MAINMENU_LOGGED_RETURN_TEXT;

    //If these are not equal, then there is an error in the program
    if (textArrayIndex != textArraySize)
    {
        throw "The text array size and the expected size do not match";
    }

    //Screen Print
    GameUI::printScreenWithText(textArray, textArrayIndex, maxSize, GlobalConstants::MAINMENU_TITLE);

    //Delete dynamic memory
    delete[] livesText;
    delete[] levelText;
    delete[] textArray;
}

bool GameController::mainMenuLogged()
{
    mainMenuLoggedScreenPrint();
    bool isAdmin = currentUser->role == UserRoles::Admin;
    while (true)
    { 
        char* selection = new char[10000];
        char firstChar = (char)std::cin.peek();
        if (firstChar == '\0' || firstChar == '\n') std::cin.ignore();
        std::cin.getline(selection, 1000);
        std::cin.clear();

        bool returnToScreen = false;
        bool continueGame = currentUser->level > 1;
        if (strcmp(selection, GlobalConstants::COMMAND_RETURN) == 0)
        {
            //Unlog the current user
            //currentUser = nullptr;
            //Return to last screen
            return true;
        }
        //User wants to delete their own account, so take them to the confirmation screen!
        else if (!isAdmin && strcmp(selection, GlobalConstants::COMMAND_ACCOUNT_DELETE) == 0)
        {
            //If the user deletes their own account, then we send them all the way back to the title screen
            returnToScreen = deleteOwnAccountConfirmation();          
            if (returnToTitleScreen)
            {
                currentUser = nullptr;
                return true;
            }
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
        //Get info about a user
        else if (isAdmin && StringManip::stringStartsWith(selection, GlobalConstants::COMMAND_ADMIN_GETINFO))
        {
            std::cout << "get info about somebody";
        }
        //Exclude user from leaderboard
        else if (isAdmin && StringManip::stringStartsWith(selection, GlobalConstants::COMMAND_ADMIN_EXCLUDE))
        {
            std::cout << "exclude somebody from leaderboards";
        }
        //Delete user
        else if (isAdmin && StringManip::stringStartsWith(selection, GlobalConstants::COMMAND_ADMIN_DELETE))
        {
            std::cout << "delete somebody";
        }
        //Recover user
        else if (isAdmin && StringManip::stringStartsWith(selection, GlobalConstants::COMMAND_ADMIN_RECOVER))
        {
            std::cout << "recover somebody's account";
        }
        //Add powerup to admin
        else if (isAdmin && StringManip::stringStartsWith(selection, GlobalConstants::COMMAND_ADMIN_ADD))
        {
            std::cout << "add a helper";
        }
        //If the command is invalid while a game hasnt already been started
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
    size_t textArrayIndex = 0;
    textArray[textArrayIndex++] = GlobalConstants::LOGIN;
    textArray[textArrayIndex++] = GlobalConstants::RETURN_TEXT;
    //Screen Print
    GameUI::printScreenWithText((const char**)textArray, textArrayIndex, 60, GlobalConstants::LOGIN_TITLE);

    //Delete dynamic memory
    delete[] textArray;
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
        char** splitInput = StringManip::splitString(selection, GlobalConstants::COMMAND_DELIM, splitStringsCount);
        char* username = splitStringsCount == 2 ? splitInput[0] : nullptr;
        char* password = splitStringsCount == 2 ? splitInput[1] : nullptr;

        // Validate if text is inputted in the correct format
        textIsValid = FileSystem::usernameIsValid(username) && FileSystem::passwordIsValid(password);

        if (strcmp(selection, GlobalConstants::COMMAND_RETURN) == 0)
        {
            //Clear memory for input from console
            StringManip::deleteArrayOfStrings(splitInput, splitStringsCount);

            //Return to previous screen
            return true;
        }
        if (selection == nullptr || !textIsValid)
        {
            //Clear memory for input from console
            StringManip::deleteArrayOfStrings(splitInput, splitStringsCount);

            // Print on a single line without screen borders
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
        else if (textIsValid)
        {
            bool userExists = FileSystem::userIsRegisteredWithPassword(username, password);

            if (!userExists)
            {
                GameUI::printLineNoBorders(GlobalConstants::LOGIN_USERNAME_TAKEN);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);

                //Clear memory for input from console
                StringManip::deleteArrayOfStrings(splitInput, splitStringsCount);

                continue;
            }

            currentUser = FileSystem::getUser(username);
            //TODO: If this user is deleted, then print a message to them from the second table of the database
            if (currentUser->isDeleted)
            {
                GameUI::printLineNoBorders(GlobalConstants::USER_BANNED);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);

                //Clear memory for input from console
                StringManip::deleteArrayOfStrings(splitInput, splitStringsCount);

                continue;
            }

            GameUI::printLineNoBorders("Game Starting...");
            returnToScreen = mainMenuLogged();
        }

        //If the user deletes their own account, then we send them all the way back to the title screen
        if (returnToTitleScreen) return true;

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
    size_t textArrayIndex = 0;
    textArray[textArrayIndex++] = GlobalConstants::REGISTER;
    textArray[textArrayIndex++] = GlobalConstants::RETURN_TEXT;
    //Screen Print
    GameUI::printScreenWithText(textArray, textArrayIndex, 300, GlobalConstants::REGISTER_TITLE);

    //Delete dynamic memory
    delete[] textArray;
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
        char** splitInput = StringManip::splitString(selection, GlobalConstants::COMMAND_DELIM, splitStringsCount);
        char* username = splitStringsCount == 2 ? splitInput[0] : nullptr;
        char* password = splitStringsCount == 2 ? splitInput[1] : nullptr;

        // Validate if text is inputted in the correct format
        textIsValid = FileSystem::usernameIsValid(username) && FileSystem::passwordIsValid(password);

        if (strcmp(selection, GlobalConstants::COMMAND_RETURN) == 0)
        {
            //Clear memory for input from console
            StringManip::deleteArrayOfStrings(splitInput, splitStringsCount);

            //Return to previous screen
            return true;
        }
        if (selection == nullptr || !textIsValid)
        {
            //Clear memory for input from console
            StringManip::deleteArrayOfStrings(splitInput, splitStringsCount);

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
                   StringManip::deleteArrayOfStrings(splitInput, splitStringsCount);

                   continue;
             }
            
             //Register the user, print the successful registration text and then send the user back to the login or register screen
             FileSystem::registerUser(username, password);
            
             GameUI::printLineNoBorders(GlobalConstants::REGISTER_SUCCESS);

             //Clear memory for input from console
             StringManip::deleteArrayOfStrings(splitInput, splitStringsCount);
            
             //Return to previous screen
             return true;           
        }
    }
}

void GameController::loginOrRegisterScreenPrint()
{
    const char** textArray = new const char* [2];
    size_t textArrayIndex = 0;
    textArray[textArrayIndex++] = GlobalConstants::LOGIN_OR_REGISTER;
    textArray[textArrayIndex++] = GlobalConstants::RETURN_TEXT;
    //Screen Print
    GameUI::printScreenWithText(textArray, textArrayIndex, 55, GlobalConstants::LOGINORREGISTER_TITLE);

    //Delete dynamic memory
    delete[] textArray;
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

        //If the user deletes their own account, then we send them all the way back to the title screen
        if (returnToTitleScreen) return true;

        if (returnToScreen)
        {
            loginOrRegisterScreenPrint();
        }
    }
}

void GameController::startUpScreenPrint()
{
    const char** textArray = new const char* [4];
    size_t textArrayIndex = 0;

    //Add the text
    textArray[textArrayIndex++] = GlobalConstants::WELCOME_STARTSCREEN_TEXT;
    textArray[textArrayIndex++] = GlobalConstants::BUTTON_START;
    textArray[textArrayIndex++] = GlobalConstants::BUTTON_END;
    GameUI::printScreenWithText(textArray, textArrayIndex, 117, GlobalConstants::STARTSCREEN_TITLE);

    //Delete dynamic memory
    delete[] textArray;
}

void GameController::startUp()
{
    //Seed database
    //Seeder::seedDatabase(false);
    //Seeder::seedDatabase(true);

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

        if (returnToTitleScreen) returnToTitleScreen = false;

        if (returnToScreen)
        {
            startUpScreenPrint();
        }
    }
}
