#pragma once
#include "Controller.h"
#include "..\Game.IOS\DeletionMessage.h"

class UnauthenticatedController
{
public:

    static void loginUserScreenPrint();

    static bool loginUser();

    static void registerUserScreenPrint();

    static bool registerUser();

    static void loginOrRegisterScreenPrint();

    static bool loginOrRegister();

    static void startUpScreenPrint();

    static void startUp();
};

