#pragma once
#include "Controller.h"
#include ".\Game.IOS\DeletionMessage.h"

class AuthenticatedController
{
private:
    static void printGetinfoTable(bool includeDeleted, bool getDeletedOnly);

    static void printGetinfoTableSingle(const User& user);

    static void printLeaderboardsTable(bool includeDeleted, bool getDeletedOnly);
public:

    static void gameOverScreenPrint(bool newHighscore);

    static bool gameOver(bool newHighscore);

    static void playingGameScreenPrint(const mstring& expression);

    static bool playingGame();

    static void adminIncludeAccountConfirmationScreenPrint(const mstring& username);

    static bool adminIncludeAccountConfirmation(const mstring& username);

    static void adminExcludeAccountConfirmationScreenPrint(const mstring& username);

    static bool adminExcludeAccountConfirmation(const mstring& username);

    static void adminRecoverAccountConfirmationScreenPrint(const DeletionMessage& deletionMessage);

    static bool adminRecoverAccountConfirmation(const DeletionMessage& deletionMessage);

    static void adminDeleteAccountConfirmationScreenPrint(const DeletionMessage& deletionMessage);

    static bool adminDeleteAccountConfirmation(const DeletionMessage& deletionMessage);

    static void deleteOwnAccountConfirmationScreenPrint();

    static bool deleteOwnAccountConfirmation();

    static void mainMenuLoggedScreenPrint();

    static bool mainMenuLogged();
};

