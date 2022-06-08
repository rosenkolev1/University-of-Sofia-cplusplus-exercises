#pragma once
#include "..\Game.IOS\User.h"
#include "..\Game.IOS\DeletionMessage.h"

class GameController
{
public:
    static User* currentUser;
    static bool returnToTitleScreen;

    static void adminRecoverAccountConfirmationScreenPrint(DeletionMessage deletionMessage);

    static bool adminRecoverAccountConfirmation(DeletionMessage deletionMessage);

    static void adminDeleteAccountConfirmationScreenPrint(DeletionMessage deletionMessage);

    static bool adminDeleteAccountConfirmation(DeletionMessage deletionMessage);

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
