#pragma once

#include "GameController.h"
#include <iostream>
#include "..\Game.GlobalConstants\GlobalConstants.h"
#include "..\Game.UI/GameUI.h"
#include "..\Game.IOS/FileSystem.h"
#include "..\Project.StringManipulation\MStringManip.h"
#include "..\Game.IOS\Seeder.h"

User* GameController::currentUser = nullptr;
bool GameController::returnToTitleScreen = false;

void GameController::deleteOwnAccountConfirmationScreenPrint()
{
    mstring textArray[3];
    size_t textArrayIndex = 0;

    //Add the text
    textArray[textArrayIndex++] = GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION;
    textArray[textArrayIndex++] = GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_NO;
    textArray[textArrayIndex++] = GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_YES;

    //Screen Print
    GameUI::printScreenWithText(textArray, 3, GlobalConstants::DELETE_CONFIRM_TITLE);
}

bool GameController::deleteOwnAccountConfirmation()
{
    deleteOwnAccountConfirmationScreenPrint();

    while (true)
    {
        mstring selection;
        std::cin >> selection;

        if (selection == GlobalConstants::COMMAND_RETURN)
        {
            //Return to last screen
            return true;
        }
        //Delete account and return user to welcome screen
        else if (selection == GlobalConstants::COMMAND_ACCOUNT_DELETE_CONFIRM)
        {
            //Delete the user's account
            FileSystem::deleteUser(currentUser->username);

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
    bool continueGame = currentUser->level > 1;
    size_t textArraySize = continueGame ? 6 : 5;

    bool isAdmin = currentUser->role == UserRoles::Admin;
    //Change the textArraySize and textArray based on the user being or not being an admin
    if (isAdmin) textArraySize += 5;

    mstring* textArray = new mstring [textArraySize];

    size_t textArrayIndex = 0;

    //Type out the fact that you are in admin profile
    if (isAdmin)
    {
        mstring loggedAsAdminText = "!!!LOGGED AS ADMIN!!!\n";
        textArray[textArrayIndex++] = loggedAsAdminText;
    }

    //Make text with current level
    /*char currentLevelText[100];
    strcpy(currentLevelText, GlobalConstants::MAINMENU_LEVEL_TEXT);
    const char* levelText = MStringManip::parseToString(currentUser->level);
    strcat(currentLevelText, levelText);
    strcat(currentLevelText, "\n");
    textArray[textArrayIndex++] = currentLevelText;*/

    mstring currentLevelText = GlobalConstants::MAINMENU_LEVEL_TEXT;
    mstring levelText = MStringManip::parseToString(currentUser->level);
    currentLevelText += levelText + "\n";
    textArray[textArrayIndex++] = currentLevelText;

    //Make text with current lives
    /*char currentLivesText[100];
    strcpy(currentLivesText, GlobalConstants::MAINMENU_LIVES_TEXT);
    const char* livesText = MStringManip::parseToString(currentUser->lives);
    strcat(currentLivesText, livesText);
    strcat(currentLivesText, "\n");
    textArray[textArrayIndex++] = currentLivesText;*/
    mstring currentLivesText = GlobalConstants::MAINMENU_LIVES_TEXT;
    mstring livesText = MStringManip::parseToString(currentUser->lives);
    currentLivesText += livesText + "\n";
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
    GameUI::printScreenWithText(textArray, textArrayIndex, GlobalConstants::MAINMENU_TITLE);

    //Delete dynamic memory
    delete[] textArray;
}

bool GameController::mainMenuLogged()
{
    mainMenuLoggedScreenPrint();
    bool isAdmin = currentUser->role == UserRoles::Admin;
    while (true)
    { 
        /*char* selection = new char[10000];
        char firstChar = (char)std::cin.peek();
        if (firstChar == '\0' || firstChar == '\n') std::cin.ignore();
        std::cin.getline(selection, 1000);
        std::cin.clear();*/
        mstring selection;
        std::cin >> selection;

        bool returnToScreen = false;
        bool continueGame = currentUser->level > 1;
        if (selection == GlobalConstants::COMMAND_RETURN)
        {
            //Return to last screen
            return true;
        }
        //User wants to delete their own account, so take them to the confirmation screen!
        else if (!isAdmin && selection == GlobalConstants::COMMAND_ACCOUNT_DELETE)
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
        else if (!continueGame && selection == GlobalConstants::COMMAND_GAME_START)
        {
            std::cout << "do something";
        }
        //User continues a game or restarts a started game
        else if (continueGame &&
            (selection == GlobalConstants::COMMAND_GAME_RESTART ||
                selection == GlobalConstants::COMMAND_GAME_CONTINUE))
        {
            std::cout << "do something";
        }
        //Get info about a user
        else if (isAdmin && MStringManip::stringStartsWith(selection, GlobalConstants::COMMAND_ADMIN_GETINFO))
        {
            std::cout << "get info about somebody";
        }
        //Exclude user from leaderboard
        else if (isAdmin && MStringManip::stringStartsWith(selection, GlobalConstants::COMMAND_ADMIN_EXCLUDE))
        {
            std::cout << "exclude somebody from leaderboards";
        }
        //Delete user
        else if (isAdmin && MStringManip::stringStartsWith(selection, GlobalConstants::COMMAND_ADMIN_DELETE))
        {
            std::cout << "delete somebody";
        }
        //Recover user
        else if (isAdmin && MStringManip::stringStartsWith(selection, GlobalConstants::COMMAND_ADMIN_RECOVER))
        {
            std::cout << "recover somebody's account";
        }
        //Add powerup to admin
        else if (isAdmin && MStringManip::stringStartsWith(selection, GlobalConstants::COMMAND_ADMIN_ADD))
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
    mstring textArray[2];
    size_t textArrayIndex = 0;

    //Add the text
    textArray[textArrayIndex++] = GlobalConstants::LOGIN;
    textArray[textArrayIndex++] = GlobalConstants::RETURN_TEXT;

    //Screen Print
    GameUI::printScreenWithText(textArray, textArrayIndex, GlobalConstants::LOGIN_TITLE);
}

bool GameController::loginUser()
{
    loginUserScreenPrint();

    while (true)
    {
        /*char selection[1000];
        char firstChar = (char)std::cin.peek();
        if (firstChar == '\0' || firstChar == '\n') std::cin.ignore();
        std::cin.getline(selection, 1000);
        std::cin.clear();*/

        mstring selection;
        std::cin >> selection;

        bool returnToScreen = false;
        bool textIsValid = true;

        size_t splitStringsCount = 0;
        mstring* splitInput = MStringManip::splitString(selection, GlobalConstants::COMMAND_DELIM, splitStringsCount);
        mstring username = splitStringsCount == 2 ? splitInput[0] : "";
        mstring password = splitStringsCount == 2 ? splitInput[1] : "";

        // Validate if text is inputted in the correct format
        textIsValid = FileSystem::usernameIsValid(username) && FileSystem::passwordIsValid(password);

        if (selection == GlobalConstants::COMMAND_RETURN)
        {
            //Clear memory for input from console
            MStringManip::deleteArrayOfStrings(splitInput, splitStringsCount);

            //Return to previous screen
            return true;
        }
        if (!textIsValid)
        {
            //Clear memory for input from console
            MStringManip::deleteArrayOfStrings(splitInput, splitStringsCount);

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
                MStringManip::deleteArrayOfStrings(splitInput, splitStringsCount);

                continue;
            }

            currentUser = FileSystem::getUser(username);

            //TODO: If this user is deleted, then print a message to them from the second table of the database
            if (currentUser->isDeleted)
            {
                GameUI::printLineNoBorders(GlobalConstants::USER_BANNED);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);

                //Clear memory for input from console
                MStringManip::deleteArrayOfStrings(splitInput, splitStringsCount);

                continue;
            }

            GameUI::printLineNoBorders("Game Starting...");

            //Go to main menu logged
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
    mstring textArray[2];
    size_t textArrayIndex = 0;

    //Add the text
    textArray[textArrayIndex++] = GlobalConstants::REGISTER;
    textArray[textArrayIndex++] = GlobalConstants::RETURN_TEXT;

    //Screen Print
    GameUI::printScreenWithText(textArray, textArrayIndex, GlobalConstants::REGISTER_TITLE);
}

bool GameController::registerUser()
{
    //Screen Print
    registerUserScreenPrint();

    while (true)
    {
        /*char selection[1000];
        char firstChar = (char)std::cin.peek();
        if (firstChar == '\0' || firstChar == '\n') std::cin.ignore();
        std::cin.getline(selection, 1000);
        std::cin.clear();*/
        mstring selection;
        std::cin >> selection;

        bool textIsValid = true;

        size_t splitStringsCount = 0;
        mstring* splitInput = MStringManip::splitString(selection, GlobalConstants::COMMAND_DELIM, splitStringsCount);
        mstring username = splitStringsCount == 2 ? splitInput[0] : "";
        mstring password = splitStringsCount == 2 ? splitInput[1] : "";

        // Validate if text is inputted in the correct format
        textIsValid = FileSystem::usernameIsValid(username) && FileSystem::passwordIsValid(password);

        if (selection == GlobalConstants::COMMAND_RETURN)
        {
            //Clear memory for input from console
            MStringManip::deleteArrayOfStrings(splitInput, splitStringsCount);

            //Return to previous screen
            return true;
        }
        if (!textIsValid)
        {
            //Clear memory for input from console
            MStringManip::deleteArrayOfStrings(splitInput, splitStringsCount);

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
                   MStringManip::deleteArrayOfStrings(splitInput, splitStringsCount);

                   continue;
             }
            
             //Register the user, print the successful registration text and then send the user back to the login or register screen
             FileSystem::registerUser(username, password);
            
             GameUI::printLineNoBorders(GlobalConstants::REGISTER_SUCCESS);

             //Clear memory for input from console
             MStringManip::deleteArrayOfStrings(splitInput, splitStringsCount);
            
             //Return to previous screen
             return true;           
        }
    }
}

void GameController::loginOrRegisterScreenPrint()
{
    mstring textArray[2];
    size_t textArrayIndex = 0;

    //Add the text
    textArray[textArrayIndex++] = GlobalConstants::LOGIN_OR_REGISTER;
    textArray[textArrayIndex++] = GlobalConstants::RETURN_TEXT;

    //Screen Print
    GameUI::printScreenWithText(textArray, textArrayIndex, GlobalConstants::LOGINORREGISTER_TITLE);
}

bool GameController::loginOrRegister()
{
    //Screen Print
    loginOrRegisterScreenPrint();

    while (true)
    {
        mstring selection;
        std::cin >> selection;

        bool returnToScreen = false;

        if (selection != GlobalConstants::COMMAND_LOGIN_START &&
                selection != GlobalConstants::COMMAND_REGISTER_START &&
                selection != GlobalConstants::COMMAND_RETURN
            )
        {
            // Print on a single line without screen borders
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
        else if (selection == GlobalConstants::COMMAND_LOGIN_START)
        {
            returnToScreen = loginUser();
        }
        else if (selection == GlobalConstants::COMMAND_REGISTER_START)
        {
            //Start the register procedure
            returnToScreen = registerUser();
        }
        else if (selection == GlobalConstants::COMMAND_RETURN)
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
    mstring textArray[4];
    size_t textArrayIndex = 0;

    //Add the text
    textArray[textArrayIndex++] = GlobalConstants::WELCOME_STARTSCREEN_TEXT;
    textArray[textArrayIndex++] = GlobalConstants::BUTTON_START;
    textArray[textArrayIndex++] = GlobalConstants::BUTTON_END;

    //Screen Print
    GameUI::printScreenWithText(textArray, textArrayIndex, GlobalConstants::STARTSCREEN_TITLE);
}

void GameController::startUp()
{
    //Seed database
    Seeder::seedDatabase(false);
    //Seeder::seedDatabase(true);

    //Screen print
    startUpScreenPrint();

    // Start the game/selection loop
    while (true)
    {
        mstring selection;
        std::cin >> selection;

        bool returnToScreen = false;

        if (selection == GlobalConstants::COMMAND_MAINMENU_END)
        {
            //End the game
            GameUI::printScreenWithText(GlobalConstants::GAME_END);
            break;
        }
        else if (selection == GlobalConstants::COMMAND_MAINMENU_START)
        {
            //Start the actual game by trying to log in first
            returnToScreen = loginOrRegister();
        }
        //If user writes invalid data
        else
        {
            // Print on a single line without screen borders
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }

        if (returnToTitleScreen) returnToTitleScreen = false;

        if (returnToScreen)
        {
            startUpScreenPrint();
        }
    }
}
