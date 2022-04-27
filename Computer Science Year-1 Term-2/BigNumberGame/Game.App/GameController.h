#pragma once
#include "..\Game.IOS\User.h"

class GameController
{
public:
    static User* currentUser;

    static void playingLevelScreenPrint();

    static bool playingLevel();

    static void loginUserScreenPrint();

    static bool loginUser();

    static void registerUserScreenPrint();

    static bool registerUser();

    static void loginOrRegisterScreenPrint();

    static bool loginOrRegister();

    static void startUpScreenPrint();

    static void startUp();

};
