#include "UnauthenticatedController.h"
#include ".\Project.StringManipulation\MStringManip.h"
#include ".\Game.GlobalConstants\GlobalConstants.h"
#include ".\Game.UI\GameUI.h"
#include ".\Game.IOS\FileSystem.h"
#include ".\Game.IOS\Seeder.h"
#include "AuthenticatedController.h"
//#include ".\Game.IOS\User.h"

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

            Controller::currentUser = FileSystem::getUser(username);

            if (Controller::currentUser->isDeleted)
            {
                //Get message from deletionMessages table
                DeletionMessage message = FileSystem::getDeletionMessage(Controller::currentUser->username);
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
        else if (selection == GlobalConstants::COMMAND_MAINMENU_LEADERBOARD)
        {
            //Get all the users
            size_t usersCount = 0;
            User* users = FileSystem::getAllUsers(usersCount);

            //Filter out the users which are excluded from the leaderboards
            size_t includedUsersCount = 0;
            User* includedUsers = new User[usersCount];
            for (size_t i = 0; i < usersCount; i++)
            {
                if (users[i].includeHighscore) includedUsers[includedUsersCount++] = users[i];
            }

            //Shorten the array
            User* copyOfIncludedUsers = new User[includedUsersCount];
            for (size_t i = 0; i < includedUsersCount; i++)
            {
                copyOfIncludedUsers[i] = includedUsers[i];
            }

            //Dealloc dynamic memory
            delete[] users;
            delete[] includedUsers;

            includedUsers = copyOfIncludedUsers;

            //Sort the array of included users
            User* sortedUsers = new User[includedUsersCount];
            size_t sortedUsersIndex = 0;

            while (sortedUsersIndex < includedUsersCount)
            {
                User largestUser = includedUsers[0];
                size_t largestUserIndex = 0;
                for (size_t i = 1; i < includedUsersCount - sortedUsersIndex; i++)
                {
                    if (includedUsers[i].highscore > largestUser.highscore)
                    {
                        largestUser = includedUsers[i];
                        largestUserIndex = i;
                    }
                }
                //Swap the current largest user to last place
                User copyOfLastUser = includedUsers[includedUsersCount - sortedUsersIndex - 1];
                includedUsers[includedUsersCount - sortedUsersIndex - 1] = largestUser;
                includedUsers[largestUserIndex] = copyOfLastUser;

                sortedUsers[sortedUsersIndex++] = largestUser;
            }

            //Dealloc dynamic memory
            delete[] includedUsers;
            
            mstring leaderboardInfo;

            for (size_t i = 0; i < sortedUsersIndex; i++)
            {
                mstring userInfo = MStringManip::replaceAll(GlobalConstants::LEADERBOARD_USER_TEXT, GlobalConstants::USERNAME_PLACEHOLDER, sortedUsers[i].username);
                userInfo = MStringManip::parseToString(i) + MStringManip::replaceAll(userInfo, GlobalConstants::HIGHSCORE_PLACEHOLDER, MStringManip::parseToString(sortedUsers[i].highscore));
                leaderboardInfo += userInfo + "\n";
            }

            GameUI::printLineNoBorders(GlobalConstants::LEADERBOARD_TEXT);
            GameUI::printLineNoBorders(leaderboardInfo);
            
            //Dealloc dynamic memory
            delete[] sortedUsers;

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