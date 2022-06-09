#pragma once
#include "..\Game.IOS\User.h"
#include "..\Game.IOS\DeletionMessage.h"

class GameController
{
public:
    static User* currentUser;
    static bool returnToTitleScreen;

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

    static void loginUserScreenPrint();

    static bool loginUser();

    static void registerUserScreenPrint();

    static bool registerUser();

    static void loginOrRegisterScreenPrint();

    static bool loginOrRegister();

    static void startUpScreenPrint();

    static void startUp();
};
