#include "UnauthenticatedController.h"
#include ".\Project.StringManipulation\MStringManip.h"
#include ".\Game.GlobalConstants\GlobalConstants.h"
#include ".\Game.UI\GameUI.h"
#include ".\Game.IOS\UserTable.h"
#include "..\Game.IOS\DeletionMessageTable.h"
#include ".\Game.IOS\Seeder.h"
#include "AuthenticatedController.h"

void UnauthenticatedController::loginUserScreenPrint()
{
    mstring textArray[2];
    size_t textArrayIndex = 0;

    //Add the text
    textArray[textArrayIndex++] = GlobalConstants::LOGIN;
    textArray[textArrayIndex++] = GlobalConstants::RETURN_TEXT;

    //Screen Print
    GameUI::printScreenWithText(textArray, textArrayIndex, GlobalConstants::LOGIN_TITLE);
}

bool UnauthenticatedController::loginUser()
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
        textIsValid = UserTable::usernameIsValid(username) && UserTable::passwordIsValid(password);

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
            bool userExists = UserTable::userIsRegisteredWithPassword(username, password);

            if (!userExists)
            {
                GameUI::printLineNoBorders(GlobalConstants::LOGIN_USERNAME_DOESNOTEXIST);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);

                //Clear memory for input from console
                delete[] splitInput;

                continue;
            }

            Controller::currentUser = UserTable::getUser(username);

            if (Controller::currentUser->isDeleted)
            {
                //Get message from deletionMessages table
                DeletionMessage message = DeletionMessageTable::getDeletionMessage(Controller::currentUser->username);
                GameUI::printLineNoBorders(message.message);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);

                //Clear memory for input from console
                delete[] splitInput;

                continue;
            }

            GameUI::printLineNoBorders("Game Starting...");

            //Go to main menu logged
            returnToScreen = AuthenticatedController::mainMenuLogged();
        }

        //If the user deletes their own account, then we send them all the way back to the title screen
        if (Controller::returnToTitleScreen) return true;

        if (returnToScreen)
        {
            //Return to this screen
            loginUserScreenPrint();
            continue;
        }
    }
}

void UnauthenticatedController::registerUserScreenPrint()
{
    mstring textArray[2];
    size_t textArrayIndex = 0;

    //Add the text
    textArray[textArrayIndex++] = GlobalConstants::REGISTER;
    textArray[textArrayIndex++] = GlobalConstants::RETURN_TEXT;

    //Screen Print
    GameUI::printScreenWithText(textArray, textArrayIndex, GlobalConstants::REGISTER_TITLE);
}

bool UnauthenticatedController::registerUser()
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
        textIsValid = UserTable::usernameIsValid(username) && UserTable::passwordIsValid(password);

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
            bool userIsRegistered = UserTable::userIsRegistered(username);
            if (userIsRegistered)
            {
                GameUI::printLineNoBorders(GlobalConstants::REGISTER_USERNAME_TAKEN);
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);

                //Clear memory for input from console
                delete[] splitInput;

                continue;
            }

            //Register the user, print the successful registration text and then send the user back to the login or register screen
            UserTable::registerUser(username, password);

            GameUI::printLineNoBorders(GlobalConstants::REGISTER_SUCCESS);

            //Clear memory for input from console
            delete[] splitInput;

            //Return to previous screen
            return true;
        }
    }
}

void UnauthenticatedController::loginOrRegisterScreenPrint()
{
    mstring textArray[2];
    size_t textArrayIndex = 0;

    //Add the text
    textArray[textArrayIndex++] = GlobalConstants::LOGIN_OR_REGISTER;
    textArray[textArrayIndex++] = GlobalConstants::RETURN_TEXT;

    //Screen Print
    GameUI::printScreenWithText(textArray, textArrayIndex, GlobalConstants::LOGINORREGISTER_TITLE);
}

bool UnauthenticatedController::loginOrRegister()
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
        if (Controller::returnToTitleScreen) return true;

        if (returnToScreen)
        {
            loginOrRegisterScreenPrint();
        }
    }
}

void UnauthenticatedController::startUpScreenPrint()
{
    mstring textArray[4];
    size_t textArrayIndex = 0;

    //Add the text
    textArray[textArrayIndex++] = GlobalConstants::WELCOME_STARTSCREEN_TEXT;
    textArray[textArrayIndex++] = GlobalConstants::BUTTON_START;
    textArray[textArrayIndex++] = GlobalConstants::BUTTON_LEADERBOARD;
    textArray[textArrayIndex++] = GlobalConstants::BUTTON_END;

    //Screen Print
    GameUI::printScreenWithText(textArray, textArrayIndex, GlobalConstants::STARTSCREEN_TITLE);
}

void UnauthenticatedController::startUp()
{
    //Seed database
    //Seeder::seedDatabase(false);
    Seeder::seedDatabase(true);

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
        else if (selection == GlobalConstants::COMMAND_LEADERBOARD)
        {
            size_t countOfRows = 0;
            mstring* leaderboardRowsInfo = Controller::getLeaderboardRows(true, false, true, countOfRows, GlobalConstants::COMMAND_DELIM);

            GameUI::printLineNoBorders(GlobalConstants::LEADERBOARD_TEXT);

            mstring tableString = GameUI::getTable(GlobalConstants::LEADERBOARD_COLS, GlobalConstants::LEADERBOARD_COLS_COUNT, leaderboardRowsInfo, countOfRows, GlobalConstants::COMMAND_DELIM);
            GameUI::printLineNoBorders(tableString);

            //Dealloc dynamic memory
            delete[] leaderboardRowsInfo;

            startUpScreenPrint();
            continue;
        }
        //If user writes invalid data
        else
        {
            // Print on a single line without screen borders
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }

        if (Controller::returnToTitleScreen) Controller::returnToTitleScreen = false;

        if (returnToScreen)
        {
            startUpScreenPrint();
        }
    }
}