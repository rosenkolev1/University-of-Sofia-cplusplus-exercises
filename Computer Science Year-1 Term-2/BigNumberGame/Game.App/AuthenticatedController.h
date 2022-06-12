#pragma once
#include "Controller.h"
#include ".\Game.IOS\DeletionMessage.h"

class AuthenticatedController
{
public:

    static void gameOverScreenPrint();

    static bool gameOver();

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

