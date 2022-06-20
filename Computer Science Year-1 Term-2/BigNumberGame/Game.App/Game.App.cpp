#include <iostream>
#include "UnauthenticatedController.h"

int main()
{
    //Init the randomness properly for the generation of the levels
    //TODO: MOVE THIS INTO A PROPER CLASS
    Controller::initialize();
    
    UnauthenticatedController::startUp();
}