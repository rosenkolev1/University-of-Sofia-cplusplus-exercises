#pragma once

#include <iostream>
#include "GameUI.h"
#include "..\Game.IOS\FileSystem.h"
#include "..\Game.IOS\SomeClass.h"

static class GameController
{
public:
    static void registerUserScreenPrint();

    static bool registerUser();

    static void loginOrRegisterScreenPrint();

    static bool loginOrRegister();

    static void startUpScreenPrint();
    
    static void startUp();

};
