#include "AuthenticatedController.h"
#include ".\Project.StringManipulation\MStringManip.h"
#include ".\Game.GlobalConstants\GlobalConstants.h"
#include ".\Game.UI\GameUI.h"
#include ".\Game.IOS\FileSystem.h"
#include ".\BigNumber\BigNumberExpression.h"

void AuthenticatedController::gameOverScreenPrint()
{
    mstring textArray[3];
    size_t textArrayIndex = 0;

    //Add the text
    textArray[textArrayIndex++] = GlobalConstants::PLAYING_WRONG_GAMEOVER;
    textArray[textArrayIndex++] = GlobalConstants::PLAYING_GAMEOVER_RESTART;
    textArray[textArrayIndex++] = GlobalConstants::PLAYING_GAMEOVER_RETURN_TO_MAINMENU;

    //Screen Print
    GameUI::printScreenWithText(textArray, textArrayIndex, GlobalConstants::GAMEOVER_TITLE);
}

bool AuthenticatedController::gameOver()
{
    gameOverScreenPrint();

    while (true)
    {
        mstring selection;
        std::cin >> selection;

        bool returnToScreen = false;
        bool continueGame = Controller::currentUser->level > 1;

        if (selection == GlobalConstants::COMMAND_RETURN)
        {
            //Return to last screen
            return true;
        }
        //Start a new game
        else if (selection == GlobalConstants::COMMAND_GAME_START || selection == GlobalConstants::COMMAND_GAME_RESTART)
        {
            return false;
        }
        //If the input is invalid
        else
        {
            GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
            continue;
        }
    }

}

void AuthenticatedController::playingGameScreenPrint(const mstring& expression)
{
    mstring textArray[6];
    size_t textArrayIndex = 0;

    mstring currentLevelString = MStringManip::parseToString(Controller::currentUser->level);
    mstring currentLivesString = MStringManip::parseToString(Controller::currentUser->lives);
    mstring levelString = MStringManip::replaceAll(GlobalConstants::PLAYING_LEVEL_TEXT, GlobalConstants::LEVEL_PLACEHOLDER, currentLevelString);
    mstring livesString = MStringManip::replaceAll(GlobalConstants::PLAYING_LIVES_TEXT, GlobalConstants::LIVES_PLACEHOLDER, currentLivesString);

    //Add the text
    textArray[textArrayIndex++] = levelString;
    textArray[textArrayIndex++] = livesString;
    textArray[textArrayIndex++] = GlobalConstants::PLAYING_EXPRESSION_SOLVE;
    textArray[textArrayIndex++] = MStringManip::replaceAll(GlobalConstants::PLAYING_EXPRESSION, GlobalConstants::EXPRESSION_PLACEHOLDER, expression);
    textArray[textArrayIndex++] = GlobalConstants::PLAYING_SOLUTION_ENTER;
    textArray[textArrayIndex++] = GlobalConstants::PLAYING_RETURN_TEXT;

    //Screen Print
    GameUI::printScreenWithText(textArray, textArrayIndex, GlobalConstants::BIGNUMBER_GAME_TITLE);
}

bool AuthenticatedController::playingGame()
{
    bool generateNewExpression = false;

    while (true)
    {
        BigNumberExpression expression;
        BigNumber solution;
        //Check if there is an expression to be passed. If not, generate a new expression
        if (Controller::currentUser->lastExpressionIsNull() || generateNewExpression)
        {
            //TODO: TURN THE THING BELOW INTO IT"S OWN FUNCTION AND CLASS
            //Generate expression until it is solveable(i.e until there is no division by 0 in it)
            while (true)
            {
                try
                {
                    expression.generateExpression();
                    solution = expression.evaluateExpression();
                    break;
                }
                catch (mstring e)
                {
                    if (e != BigNumberExpression::EXPRESSION_DIVIDEBYZERO_EXCEPTION && e != BigNumberExpression::EXPRESSION_PERCENTBYZERO_EXCEPTION) throw e;
                }
            }

            Controller::currentUser->lastExpression = expression.getExpression();
            generateNewExpression = false;
        }
        else
        {
            expression.setExpression(Controller::currentUser->lastExpression);
            solution = expression.evaluateExpression();
        }

        playingGameScreenPrint(expression.getExpression());

        while (true)
        {
            mstring selection;
            std::cin >> selection;

            bool returnToScreen = false;

            //Split the selection by the commas and then check if the command is valid
            bool inputIsValidNumber = true;
            if (MStringManip::stringStartsWith(selection, ",") || MStringManip::stringEndsWith(selection, ",")) inputIsValidNumber = false;

            //Remove commas from the selection
            mstring selectionNumber = MStringManip::replaceAll(selection, ",", "");

            for (size_t i = 0; i < selectionNumber.getSize(); i++)
            {
                if (!isdigit(selectionNumber[i]) && i >= 1) inputIsValidNumber = false;
                else if (selectionNumber[0] != '-' && selectionNumber[0] != '+' && !isdigit(selectionNumber[0])) inputIsValidNumber = false;
            }
            if (selectionNumber.getSize() == 0) inputIsValidNumber = false;


            if (selection == GlobalConstants::COMMAND_RETURN)
            {
                //Return to last screen and save changes of game to the user
                FileSystem::updateUser(*(Controller::currentUser));

                return true;
            }
            //This is a cheat code for getting the solution to the expression
            else if (selection == GlobalConstants::COMMAND_PLAYING_CHEATCODE_GETSOLUTION)
            {
                //Print solution
                GameUI::printLineNoBorders(MStringManip::replaceAll(GlobalConstants::PLAYING_CHEATCODE_GETSOLUTION, GlobalConstants::SOLUTION_PLACEHOLDER, solution.getNumber()));
                continue;
            }
            else if (inputIsValidNumber)
            {
                //Check if the solution is correct
                BigNumber userAnswer(selectionNumber);

                if (userAnswer == solution)
                {
                    GameUI::printLineNoBorders(GlobalConstants::PLAYING_CORRECT);

                    //Update the user's current level
                    Controller::currentUser->level++;

                    //Have the game update the current user's last expression to the one that the current level will generate
                    generateNewExpression = true;

                    break;
                }
                else
                {
                    //If the answer is incorrect, let the user try again
                    Controller::currentUser->lives--;
                    if (Controller::currentUser->lives <= 0)
                    {
                        Controller::currentUser->setLastExpressionToNull();
                        Controller::currentUser->level = 0;
                        Controller::currentUser->lives = GlobalConstants::PLAYING_LIVES_DEFAULT;

                        //Update the user's profile so that they cannot save scum
                        FileSystem::updateUser(*Controller::currentUser);

                        bool returnToMainMenu = gameOver();
                        
                        //If the users chose to return to the main menu, then do so
                        if (returnToMainMenu) return true;
                        
                        //In this case, we generate the first level for the user.
                        Controller::currentUser->level = 1;
                        break;
                    }
                    else
                    {
                        GameUI::printLineNoBorders(GlobalConstants::PLAYING_WRONG_TRYAGAIN);
                        playingGameScreenPrint(expression.getExpression());
                        //Update the user's profile so that they cannot save scum
                        FileSystem::updateUser(*Controller::currentUser);
                    }
                    
                    continue;
                }

            }
            //If the input is invalid
            else
            {
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }
        }
    }
}

void AuthenticatedController::adminIncludeAccountConfirmationScreenPrint(const mstring& username)
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

bool AuthenticatedController::adminIncludeAccountConfirmation(const mstring& username)
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

void AuthenticatedController::adminExcludeAccountConfirmationScreenPrint(const mstring& username)
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

bool AuthenticatedController::adminExcludeAccountConfirmation(const mstring& username)
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

void AuthenticatedController::adminRecoverAccountConfirmationScreenPrint(const DeletionMessage& deletionMessage)
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

bool AuthenticatedController::adminRecoverAccountConfirmation(const DeletionMessage& deletionMessage)
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

void AuthenticatedController::adminDeleteAccountConfirmationScreenPrint(const DeletionMessage& deletionMessage)
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

bool AuthenticatedController::adminDeleteAccountConfirmation(const DeletionMessage& deletionMessage)
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

void AuthenticatedController::deleteOwnAccountConfirmationScreenPrint()
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

bool AuthenticatedController::deleteOwnAccountConfirmation()
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
            FileSystem::deleteUser(Controller::currentUser->username);

            //Set the current user to nullptr because it was deleted
            Controller::currentUser = nullptr;
            //If the user has deleted their own account, then send them a message to inform them of the account deletion
            GameUI::printLineNoBorders(GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_SUCCESS);

            //Return to title screen
            Controller::returnToTitleScreen = true;
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

void AuthenticatedController::mainMenuLoggedScreenPrint()
{
    bool continueGame = Controller::currentUser->continueingGame();
    size_t textArraySize = continueGame ? 6 : 5;

    bool isAdmin = Controller::currentUser->role == UserRoles::Admin;
    //Change the textArraySize and textArray based on the user being or not being an admin
    if (isAdmin) textArraySize += 7;

    mstring* textArray = new mstring[textArraySize];

    size_t textArrayIndex = 0;

    //Type out the fact that you are in admin profile
    if (isAdmin)
    {
        mstring loggedAsAdminText = "!!!LOGGED AS ADMIN!!!\n";
        textArray[textArrayIndex++] = loggedAsAdminText;
    }

    //Make text with current level
    mstring currentLevelText = GlobalConstants::MAINMENU_LEVEL_TEXT;
    mstring levelText = MStringManip::parseToString(Controller::currentUser->level);
    currentLevelText += levelText + "\n";
    textArray[textArrayIndex++] = currentLevelText;

    //Make text with current lives
    mstring currentLivesText = GlobalConstants::MAINMENU_LIVES_TEXT;
    mstring livesText = MStringManip::parseToString(Controller::currentUser->lives);
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
    if (!isAdmin) textArray[textArrayIndex++] = GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT;
    else
    {
        textArray[textArrayIndex++] = GlobalConstants::ADMIN_GETINFO;
        textArray[textArrayIndex++] = GlobalConstants::ADMIN_GETINFO_ALL;
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

bool AuthenticatedController::mainMenuLogged()
{
    mainMenuLoggedScreenPrint();
    bool isAdmin = Controller::currentUser->role == UserRoles::Admin;

    while (true)
    {
        mstring selection;
        std::cin >> selection;

        bool returnToScreen = false;
        bool continueGame = Controller::currentUser->continueingGame();

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
            if (Controller::returnToTitleScreen)
            {
                Controller::currentUser = nullptr;
                return true;
            }
        }
        //Users starts a new game
        else if (!continueGame && selection == GlobalConstants::COMMAND_GAME_START)
        {
            Controller::currentUser->level = 1;
            GameUI::printLineNoBorders(GlobalConstants::PLAYING_STARTING_GAME);
            returnToScreen = playingGame();
        }
        //User continues a game
        else if (continueGame && selection == GlobalConstants::COMMAND_GAME_CONTINUE)
        {
            GameUI::printLineNoBorders(GlobalConstants::PLAYING_CONTINUE_GAME);
            returnToScreen = playingGame();
        }
        //User restarts a started game
        else if (continueGame && selection == GlobalConstants::COMMAND_GAME_RESTART)
        {
            //Reset the user's game
            Controller::currentUser->level = 1;
            Controller::currentUser->lives = GlobalConstants::PLAYING_LIVES_DEFAULT;
            Controller::currentUser->setLastExpressionToNull();

            GameUI::printLineNoBorders(GlobalConstants::PLAYING_RESTART_GAME);
            returnToScreen = playingGame();
        }
        //Get info about a user
        else if (isAdmin && command == GlobalConstants::COMMAND_ADMIN_GETINFO)
        {
            //Get info for specific user
            if (partsCount == 2)
            {
                mstring username = splitSelection[1];

                //Dealloc dynamic memory
                delete[] splitSelection;

                User* targetUser = FileSystem::getUser(username);

                //Check if the user exists
                if (targetUser == nullptr)
                {
                    GameUI::printLineNoBorders(MStringManip::replaceFirst(GlobalConstants::ADMIN_GETINFO_DOESNOTEXIST,
                        GlobalConstants::USERNAME_PLACEHOLDER, username));
                    GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                    continue;
                }

                //Print the information about the user to the console
                GameUI::printLineNoBorders(GlobalConstants::ADMIN_GETINFO_SINGLE_HEADER);
                GameUI::printLineNoBorders(targetUser->getInfo());

                mainMenuLoggedScreenPrint();

                //Dealloc dynamic memory
                delete targetUser;

                continue;
            }
            else if (partsCount == 3 && splitSelection[1] == "all")
            {
                mstring includeDeletedString = splitSelection[2];
                bool includeDeleted = true;

                //Dealloc dynamic memory
                delete[] splitSelection;

                //Check if the command is invalid
                if (includeDeletedString != GlobalConstants::COMMAND_FALSE &&
                    includeDeletedString != GlobalConstants::COMMAND_TRUE &&
                    includeDeletedString != GlobalConstants::COMMAND_FALSE_SHORT &&
                    includeDeletedString != GlobalConstants::COMMAND_TRUE_SHORT &&
                    includeDeletedString != GlobalConstants::COMMAND_ADMIN_GETINFO_PARAM_DELETEDONLY)
                {
                    GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                    continue;
                }

                size_t countOfUsers = 0;
                User* allUsers = nullptr;

                //Filter out the users as necessary
                if (includeDeletedString == GlobalConstants::COMMAND_FALSE ||
                    includeDeletedString == GlobalConstants::COMMAND_FALSE_SHORT) includeDeleted = false;

                //Get only the deleted users
                if (includeDeletedString == GlobalConstants::COMMAND_ADMIN_GETINFO_PARAM_DELETEDONLY)
                {
                    allUsers = FileSystem::getDeletedUsers(countOfUsers);
                }
                //Get all the users, except maybe the deleted ones
                else
                {
                    allUsers = FileSystem::getAllUsers(countOfUsers, includeDeleted);
                }

                //Print the information about the user to the console
                GameUI::printLineNoBorders(GlobalConstants::ADMIN_GETINFO_MANY_HEADER);
                GameUI::printLineNoBorders(User::getInfoMany(allUsers, countOfUsers));

                mainMenuLoggedScreenPrint();

                //Dealloc dynamic memory
                delete[] allUsers;

                continue;
            }
            //Command is invalid
            else
            {
                GameUI::printLineNoBorders(GlobalConstants::COMMAND_INVALID);
                continue;
            }
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