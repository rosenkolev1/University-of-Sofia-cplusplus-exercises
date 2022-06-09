#pragma once

#include "GameController.h"
#include <iostream>
#include "..\Game.GlobalConstants\GlobalConstants.h"
#include "..\Game.UI/GameUI.h"
#include "..\Game.IOS/FileSystem.h"
#include "..\Project.StringManipulation\MStringManip.h"
#include "..\Game.IOS\Seeder.h"

//TODO: Change all the params of the functions to & so no needless copying is being made

User* GameController::currentUser = nullptr;
bool GameController::returnToTitleScreen = false;

void GameController::adminIncludeAccountConfirmationScreenPrint(mstring username)
{
    mstring textArray[3];
    size_t textArrayIndex = 0;

    //Add the text
    textArray[textArrayIndex++] = MStringManip::replaceFirst(GlobalConstants::ADMIN_INCLUDEINLEADERBOARD_CONFIRMATION,
        GlobalConstants::USERNAME_PLACEHOLDER, username);
    textArray[textArrayIndex++] = GlobalConstants::ADMIN_INCLUDEINLEADERBOARD_CONFIRMATION_NO;
    textArray[textArrayIndex++] = GlobalConstants::ADMIN_INCLUDEINLEADERBOARD_CONFIRMATION_YES;

    //Screen Print
    GameUI::printScreenWithText(textArray, textArrayIndex, GlobalConstants::INCLUDEINLEADERBOARD_CONFIRM_TITLE);
}

bool GameController::adminIncludeAccountConfirmation(mstring username)
{
    adminIncludeAccountConfirmationScreenPrint(username);

    while (true)
    {
        mstring selection;
        std::cin >> selection;

        if (selection == GlobalConstants::COMMAND_RETURN)
        {
            //Return to last screen
            return true;
        }
        //Include the user in the leaderboards
        else if (selection == GlobalConstants::COMMAND_ADMIN_INCLUDE_CONFIRM)
        {
            //Include the user in the leaderboards
            FileSystem::includeUser(username);

            //Send the admin a message to inform them of the account deletion
            GameUI::printLineNoBorders(MStringManip::replaceFirst(GlobalConstants::ADMIN_INCLUDEINLEADERBOARD_SUCCESS,
                GlobalConstants::USERNAME_PLACEHOLDER, username));

            //Return to title screen
            return true;
        }
        //If the command is invalid while a game hasnt already been started
        else
        {
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
    }
}

void GameController::adminExcludeAccountConfirmationScreenPrint(mstring username)
{
    mstring textArray[3];
    size_t textArrayIndex = 0;

    //Add the text
    textArray[textArrayIndex++] = MStringManip::replaceFirst(GlobalConstants::ADMIN_EXCLUDEFROMLEADERBOARD_CONFIRMATION,
        GlobalConstants::USERNAME_PLACEHOLDER, username);
    textArray[textArrayIndex++] = GlobalConstants::ADMIN_EXCLUDEFROMLEADERBOARD_CONFIRMATION_NO;
    textArray[textArrayIndex++] = GlobalConstants::ADMIN_EXCLUDEFROMLEADERBOARD_CONFIRMATION_YES;

    //Screen Print
    GameUI::printScreenWithText(textArray, textArrayIndex, GlobalConstants::EXCLUDEFROMLEADERBOARD_CONFIRM_TITLE);
}

bool GameController::adminExcludeAccountConfirmation(mstring username)
{
    adminExcludeAccountConfirmationScreenPrint(username);

    while (true)
    {
        mstring selection;
        std::cin >> selection;

        if (selection == GlobalConstants::COMMAND_RETURN)
        {
            //Return to last screen
            return true;
        }
        //Exclude the user from the leaderboards
        else if (selection == GlobalConstants::COMMAND_ADMIN_EXCLUDE_CONFIRM)
        {
            //Exclude the user from the leaderboards
            FileSystem::excludeUser(username);

            //Send the admin a message to inform them of the account deletion
            GameUI::printLineNoBorders(MStringManip::replaceFirst(GlobalConstants::ADMIN_EXCLUDEFROMLEADERBOARD_SUCCESS,
                GlobalConstants::USERNAME_PLACEHOLDER, username));

            //Return to title screen
            return true;
        }
        //If the command is invalid while a game hasnt already been started
        else
        {
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
    }
}

void GameController::adminRecoverAccountConfirmationScreenPrint(DeletionMessage deletionMessage)
{
    mstring textArray[5];
    size_t textArrayIndex = 0;

    //Add the text
    textArray[textArrayIndex++] = MStringManip::replaceFirst(GlobalConstants::ADMIN_RECOVER_CONFIRMATION,
        GlobalConstants::USERNAME_PLACEHOLDER, deletionMessage.username);
    textArray[textArrayIndex++] = GlobalConstants::ADMIN_RECOVER_BANREASON;
    textArray[textArrayIndex++] = deletionMessage.message + "\n";
    textArray[textArrayIndex++] = GlobalConstants::ADMIN_RECOVER_CONFIRMATION_NO;
    textArray[textArrayIndex++] = GlobalConstants::ADMIN_RECOVER_CONFIRMATION_YES;

    //Screen Print
    GameUI::printScreenWithText(textArray, 5, GlobalConstants::RECOVER_CONFIRM_TITLE);
}

bool GameController::adminRecoverAccountConfirmation(DeletionMessage deletionMessage)
{
    adminRecoverAccountConfirmationScreenPrint(deletionMessage);

    while (true)
    {
        mstring selection;
        std::cin >> selection;

        if (selection == GlobalConstants::COMMAND_RETURN)
        {
            //Return to last screen
            return true;
        }
        else if (selection == GlobalConstants::COMMAND_ACCOUNT_RECOVER_CONFIRM)
        {       
            //Delete the old deletion message and unban the user
            FileSystem::restoreUser(deletionMessage.username);    

            //Send the admin a message to inform them of the account deletion
            GameUI::printLineNoBorders(MStringManip::replaceFirst(GlobalConstants::ADMIN_RECOVER_SUCCESS,
                GlobalConstants::USERNAME_PLACEHOLDER, deletionMessage.username));

            //Return to title screen
            return true;
        }
        //If the command is invalid while a game hasnt already been started
        else
        {
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
    }
}

void GameController::adminDeleteAccountConfirmationScreenPrint(DeletionMessage deletionMessage)
{
    mstring textArray[3];
    size_t textArrayIndex = 0;

    //Add the text
    textArray[textArrayIndex++] = MStringManip::replaceFirst(GlobalConstants::ADMIN_DELETEACCOUNT_CONFIRMATION, 
        GlobalConstants::USERNAME_PLACEHOLDER, deletionMessage.username);
    textArray[textArrayIndex++] = GlobalConstants::ADMIN_DELETEACCOUNT_CONFIRMATION_NO;
    textArray[textArrayIndex++] = GlobalConstants::ADMIN_DELETEACCOUNT_CONFIRMATION_YES;

    //Screen Print
    GameUI::printScreenWithText(textArray, 3, GlobalConstants::DELETE_CONFIRM_TITLE);
}

bool GameController::adminDeleteAccountConfirmation(DeletionMessage deletionMessage)
{
    adminDeleteAccountConfirmationScreenPrint(deletionMessage);

    while (true)
    {
        mstring selection;
        std::cin >> selection;

        if (selection == GlobalConstants::COMMAND_RETURN)
        {
            //Return to last screen
            return true;
        }
        else if (selection == GlobalConstants::COMMAND_ACCOUNT_DELETE_CONFIRM)
        {
            //Delete the user's account
            FileSystem::deleteUser(deletionMessage);

            //Send the admin a message to inform them of the account deletion
            GameUI::printLineNoBorders(MStringManip::replaceFirst(GlobalConstants::ADMIN_DELETEACCOUNT_SUCCESS,
                GlobalConstants::USERNAME_PLACEHOLDER, deletionMessage.username));

            //Return to title screen
            return true;
        }
        //If the command is invalid while a game hasnt already been started
        else
        {
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
    }
}

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
    if (isAdmin) textArraySize += 6;

    mstring* textArray = new mstring [textArraySize];

    size_t textArrayIndex = 0;

    //Type out the fact that you are in admin profile
    if (isAdmin)
    {
        mstring loggedAsAdminText = "!!!LOGGED AS ADMIN!!!\n";
        textArray[textArrayIndex++] = loggedAsAdminText;
    }

    //Make text with current level
    mstring currentLevelText = GlobalConstants::MAINMENU_LEVEL_TEXT;
    mstring levelText = MStringManip::parseToString(currentUser->level);
    currentLevelText += levelText + "\n";
    textArray[textArrayIndex++] = currentLevelText;

    //Make text with current lives
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
    if(!isAdmin) textArray[textArrayIndex++] = GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT;
    else
    {
        textArray[textArrayIndex++] = GlobalConstants::ADMIN_GETINFO;
        textArray[textArrayIndex++] = GlobalConstants::ADMIN_EXCLUDEFROMLEADERBOARD;
        textArray[textArrayIndex++] = GlobalConstants::ADMIN_INCLUDEINLEADERBOARD;
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
        mstring selection;
        std::cin >> selection;

        bool returnToScreen = false;
        bool continueGame = currentUser->level > 1;

        size_t partsCount = 0;
        mstring* splitSelection = MStringManip::splitString(selection, GlobalConstants::COMMAND_DELIM, partsCount);
        mstring command = splitSelection[0];

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
        else if (isAdmin && command == GlobalConstants::COMMAND_ADMIN_GETINFO)
        {
            std::cout << "get info about somebody";
        }
        //Exclude user from leaderboard
        else if (isAdmin && command == GlobalConstants::COMMAND_ADMIN_EXCLUDE)
        {
            //Check if the command is with valid syntax
            if (partsCount != 2)
            {
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }

            mstring username = splitSelection[1];

            //Dealloc dynamic memory
            delete[] splitSelection;

            User* targetUser = FileSystem::getUser(username);

            //Check if a user with this username exists
            if (targetUser == nullptr)
            {
                GameUI::printLineNoBorders(GlobalConstants::USER_DOES_NOT_EXIST);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }

            //Check if the user is not included currently
            if (!targetUser->includeHighscore)
            {
                GameUI::printLineNoBorders(MStringManip::replaceFirst(GlobalConstants::ADMIN_EXCLUDEFROMLEADERBOARD_ALREADYEXCLUDED,
                    GlobalConstants::USERNAME_PLACEHOLDER, username));
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }

            //Dealloc dynamic memory
            delete targetUser;

            returnToScreen = adminExcludeAccountConfirmation(username);
        }
        //Include user from leaderboard
        else if (isAdmin && command == GlobalConstants::COMMAND_ADMIN_INCLUDE)
        {
            //Check if the command is with valid syntax
            if (partsCount != 2)
            {
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }

            mstring username = splitSelection[1];

            //Dealloc dynamic memory
            delete[] splitSelection;

            User* targetUser = FileSystem::getUser(username);

            //Check if a user with this username exists
            if (targetUser == nullptr)
            {
                GameUI::printLineNoBorders(GlobalConstants::USER_DOES_NOT_EXIST);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }

            //Check if the user is included currently
            if (targetUser->includeHighscore)
            {
                GameUI::printLineNoBorders(MStringManip::replaceFirst(GlobalConstants::ADMIN_INCLUDEINLEADERBOARD_ALREADYINCLUDED,
                    GlobalConstants::USERNAME_PLACEHOLDER, username));
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }

            //Check if the user is an admin
            if (targetUser->role == UserRoles::Admin)
            {
                GameUI::printLineNoBorders(GlobalConstants::ADMIN_INCLUDEINLEADERBOARD_INCLUDEADMIN_NOTALLOWED);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }

            //Dealloc dynamic memory
            delete targetUser;

            returnToScreen = adminIncludeAccountConfirmation(username);
        }
        //Delete user
        else if (isAdmin && command == GlobalConstants::COMMAND_ADMIN_DELETE)
        {
            //Check if the command is with valid syntax
            if (partsCount != 3)
            {
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }

            //Get the username and message
            mstring message = splitSelection[1];
            mstring username = splitSelection[2];

            //Dealloc dynamic memory
            delete[] splitSelection;

            User* targetUser = FileSystem::getUser(username);

            //Check if a user with this username exists
            if (targetUser == nullptr)
            {
                GameUI::printLineNoBorders(GlobalConstants::USER_DOES_NOT_EXIST);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }

            //Check if the account is an admin account
            if (targetUser->role == UserRoles::Admin)
            {
                GameUI::printLineNoBorders(GlobalConstants::ADMIN_DELETEACCOUNT_DELETEADMIN_NOTALLOWED);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }

            //Check if the account is already deleted
            if (targetUser->isDeleted)
            {
                GameUI::printLineNoBorders(MStringManip::replaceFirst(GlobalConstants::ADMIN_DELETEACCOUNT_ALREADY_DELETED,
                    GlobalConstants::USERNAME_PLACEHOLDER, targetUser->username));
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }

            //Dealloc dynamic memory
            delete targetUser;

            //Create the new deletion message
            DeletionMessage deletionMessage = FileSystem::createDeletionMessage(message, username);

            returnToScreen = adminDeleteAccountConfirmation(deletionMessage);
        }
        //Recover user
        else if (isAdmin && command == GlobalConstants::COMMAND_ADMIN_RECOVER)
        {
            //Check if the command is with valid syntax
            if (partsCount != 2)
            {
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }

            //Get the username
            mstring username = splitSelection[1];

            //Dealloc dynamic memory
            delete[] splitSelection;

            User* targetUser = FileSystem::getUser(username);

            //Check if a user with this username exists at all, even amongst the banned accounts
            if (targetUser == nullptr)
            {
                GameUI::printLineNoBorders(GlobalConstants::USER_DOES_NOT_EXIST);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }

            //Check if the account is not banned
            if (!targetUser->isDeleted)
            {
                GameUI::printLineNoBorders(MStringManip::replaceFirst(GlobalConstants::ADMIN_RECOVER_NOTBANNED,
                    GlobalConstants::USERNAME_PLACEHOLDER, targetUser->username));
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }

            //Dealloc dynamic memory
            delete targetUser;

            //Get the deletion message for the user
            DeletionMessage deletionMessage = FileSystem::getDeletionMessage(username);

            returnToScreen = adminRecoverAccountConfirmation(deletionMessage);
        }
        //Add powerup to admin
        else if (isAdmin && command == GlobalConstants::COMMAND_ADMIN_ADD)
        {
            std::cout << "add a helper";
        }
        //If the input is invalid
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
            delete[] splitInput;

            //Return to previous screen
            return true;
        }
        if (!textIsValid)
        {
            //Clear memory for input from console
            delete[] splitInput;

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
                delete[] splitInput;

                continue;
            }

            currentUser = FileSystem::getUser(username);

            if (currentUser->isDeleted)
            {
                //Get message from deletionMessages table
                DeletionMessage message = FileSystem::getDeletionMessage(currentUser->username);
                GameUI::printLineNoBorders(message.message);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);

                //Clear memory for input from console
                delete[] splitInput;

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
            delete[] splitInput;

            //Return to previous screen
            return true;
        }
        if (!textIsValid)
        {
            //Clear memory for input from console
            delete[] splitInput;

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
                   delete[] splitInput;

                   continue;
             }
            
             //Register the user, print the successful registration text and then send the user back to the login or register screen
             FileSystem::registerUser(username, password);
            
             GameUI::printLineNoBorders(GlobalConstants::REGISTER_SUCCESS);

             //Clear memory for input from console
             delete[] splitInput;
            
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
