// Homework1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstddef>
#include <limits>

using namespace std;

//double toFloorPrecision(double floatValue, int precision)
//{
//    char buffer[64];
//    int ret = snprintf(buffer, sizeof buffer, "%f", floatValue);
//
//    if (ret < 0) {
//        return EXIT_FAILURE;
//    }
//    if (ret >= sizeof buffer) {
//        // Result was truncated - resize the buffer and retry.
//    }
//}

double toPrecisionFloor(double floatValue, int precision)
{
    return floor(floatValue * pow(10, precision)) / pow(10, precision);
}

void exerciseOne()
{
    double x, y;
    cout << "Enter the coordinates of the point(x y): "; cin >> x >> y;

    const string thePointIsOutsideAnyArea = "The point isn't inside any of the coloured areas";

    //If x or y are really big values, then the next calculations might throw an error.
    if (x > 5 || x < -5 || y  > 6 || y < -8)
    {
        cout << thePointIsOutsideAnyArea;
        return;
    }
    
    //Set the precision to 3 decimal digits
    x = toPrecisionFloor(x, 3);
    y = toPrecisionFloor(y, 3);

    //Needed so I can calculate the distance from a given point to the center of the coordinate system (0;0). Once again, precision to 3 decimal digits is applied
    double xSecondPower = toPrecisionFloor(x * x, 3);
    double ySecondPower = toPrecisionFloor(y * y, 3);
    double distanceToCenterSecondPower = toPrecisionFloor(xSecondPower + ySecondPower, 3);

    const double circleRadiusSecondPower = 16;

    //Check if the point is in a shared border or point
    if (
        //Points D,B,C,E
        (abs(x) == 2.8 && abs(y) == 2.8) || 
        //Line QP
        (x == 0 && y >= -4 && y <= 4 ) ||
        //Lines CB, DA
        (x == y || (x < 0 && y > 0 && abs(x) == abs(y))) ||
        //Line BE
        (x == 2.8 && y > -2.8 && y < 2.8)
        )
    {
        cout << thePointIsOutsideAnyArea;
    }
    //Check if the point is in the pink area
    else if (x >= -2.8 && x <= 0 && y <= 2.8 && y >= -2.8 && abs(x) >= abs(y))
    {
        cout << "The point is in the pink area";
    }
    //Check if the point is in the red area
    else if (x >= -2.8 && x <= 0 && y <= 4 && y >= 0 && abs(y) >= abs(x) && distanceToCenterSecondPower <= circleRadiusSecondPower)
    {
        cout << "The point is in the red area";
    }
    //Check if the point is in the yellow area
    else if (
        (x <= 2.8 && x >= 0 && y <= 2.8 && y >= -2.8 && abs(x) >= abs(y)) ||
        (x <= 2.8 && x >= 0 && y >= -4 && y <= 0 && abs(y) >= abs(x) && distanceToCenterSecondPower <= circleRadiusSecondPower)
        )
    {
        cout << "The point is in the yellow area";
    }
    //Check if the point is in the green area
    else if (x >= 0 && x <= 2.8 && y <= 4 && y >= 0 && abs(y) >= abs(x) && distanceToCenterSecondPower <= circleRadiusSecondPower)
    {
        cout << "The point is in the green area";
    }
    //Check if the point is in the blue area
    else if (x <= 0 && x >= -2.8 && y >= -4 && y <= 0 && abs(y) >= abs(x) && distanceToCenterSecondPower <= circleRadiusSecondPower)
    {
        cout << "The point is in the blue area";
    }
    //Check if the point is in the purple area
    else if (x >= 2.8 && distanceToCenterSecondPower <= circleRadiusSecondPower)
    {
        cout << "The point is in the purple area";
    }
    //Check if the point is in the grey area. If the point is on the border of the grey area, then it counts as being inside it, since the grey are doesn't share a border with any other coloured area.
    else if (
        (x >= -2 && x <= 2 && y <= -7 && y >= -6) ||
        (x >= -1 && x <= 1 && y == 5)
        )
    {
        cout << "The point is in the grey area";
    }
    else
    {
        cout << thePointIsOutsideAnyArea;
    }
}

void exerciseTwo()
{
    int x;
    cout << "Enter the number x = f1(x): "; cin >> x;

    int lastFunctionValue = x;

    for (int i = 2; i <= 35; i++)
    {
        if (lastFunctionValue % 2 == 0)
        {
            lastFunctionValue /= 2;
        }
        else if (lastFunctionValue % 2 == 1)
        {
            lastFunctionValue = lastFunctionValue*3 + 1;
        }
    }

    cout << "F35(" << x << ") = " << lastFunctionValue;
}

void exerciseThree()
{
    int digit, numberOfDigits, typeCode = 0, shipkovTypeCount = 0, borovinkovTypeCount = 0, praskovTypeCount = 0;
    cout << "Enter the number of digits: "; cin >> numberOfDigits;

    bool currentlyCountingTypeCode = false;

    if (numberOfDigits % 8 != 0) numberOfDigits = numberOfDigits - (numberOfDigits % 8);

    for (int i = 1; i <= numberOfDigits; i++)
    {
        cin >> digit;

        if (i % 4 == 0 && i % 8 != 0)
        {
            currentlyCountingTypeCode = true;
        }
        else if (i % 4 == 0 && i % 8 == 0)
        {
            //Ne sum siguren dali edin marmalad moje da e ednovremenno ot dva vida, primerno borovinkov i praskov marmalad.
            if (typeCode % 7 == 0 && typeCode % 13 != 0 && typeCode % 17 != 0) borovinkovTypeCount++;
            else if (typeCode % 13 == 0 && typeCode % 7 != 0 && typeCode && 17 != 0) praskovTypeCount++;
            else if (typeCode % 17 == 0 && typeCode % 7 != 0 && typeCode % 13 != 0) shipkovTypeCount++;

            //Annulate the typeCode and stop counting it 
            typeCode = 0;
            currentlyCountingTypeCode = false;
        }

        if (currentlyCountingTypeCode)
        {
            typeCode += digit * pow(10, 3 - (i % 4));
        }
    }

    cout << "Marmalade from blueberries " << borovinkovTypeCount << endl;
    cout << "Marmalade from peaches: " << praskovTypeCount << endl;
    cout << "Marmalade from shipka: " << shipkovTypeCount;
}

bool numberIsInteresting(int number)
{
    if (number < 0) number = abs(number);

    if (number < 10) return true;

    int digitCount = 0;
    int numberCopy = number;

    while (numberCopy != 0)
    {
        digitCount++;
        numberCopy /= 10;
    }

    int digits[100];

    for (int i = 0; i < digitCount; i++)
    {
        digits[i] = number % 10;
        number /= 10;
    }

    for (int i = 0; i < digitCount - 1; i++)
    {
        int firstDigit = digits[i];
        int secondDigit = digits[i + 1];

        if (firstDigit % 2 == 0 && secondDigit % 2 == 0 || firstDigit % 2 == 1 && secondDigit % 2 == 1)
        {
            return false;
        }
    }

    return true;
}

void exerciseFour()
{
    int a, b;
    cout << "Enter the range for the numbers (a b): ";  cin >> a >> b;

    for (int i = a; i <= b; i++)
    {
        if (numberIsInteresting(i))
        {
            cout << i << " | ";
        }
    }
}

int* returnDigitsOfNumberInArray(int number)
{
    int digitCount = 0;
    int numberCopy = number;

    int* digits = new int[100];

    while (numberCopy != 0)
    {
        digitCount++;
        numberCopy /= 10;
    }


    for (int i = 0; i < digitCount; i++)
    {
        digits[i] = number % 10;
        number /= 10;
    }

    return digits;
}

void outputBikoveAndKravi(int* digitsOfPlayerNumber, int* digitsOfComputerNumber)
{
    int bikove = 0;
    int kravi = 0;

    for (int i = 0; i < 4; i++)
    {
        int digitOfPlayerNumber = digitsOfPlayerNumber[i];

        for (int y = 0; y < 4; y++)
        {
            int digitOfComputerNumber = digitsOfComputerNumber[y];
            if (digitOfPlayerNumber == digitOfComputerNumber && i == y) bikove++;
            else if (digitOfPlayerNumber == digitOfComputerNumber && i != y) kravi++;
        }
    }

    cout << bikove << " bik(ove) and " << kravi << " krava/kravi"<< endl << endl;
}

int createRandomNumberForBikoveAndKraviGame()
{
    int computerNumber = 0;

    srand(time(NULL));

    while (true)
    {
        computerNumber = rand() % 9000 + 1000;

        int* digitsOfComputerNumber = returnDigitsOfNumberInArray(computerNumber);

        bool repeatingDigits = false;
        bool digitsIsZero = false;

        for (int i = 0; i < 4; i++)
        {
            int digit = digitsOfComputerNumber[i];
            if (digit == 0)
            {
                digitsIsZero = true;
                break;
            }

            for (int y = 0; y < 4; y++)
            {
                int currentDigit = digitsOfComputerNumber[y];
                if (digit == currentDigit && i != y)
                {
                    repeatingDigits = true;
                    break;
                }
            }

            if (repeatingDigits == true) break;
        }

        if (!repeatingDigits && !digitsIsZero) break;
    }

    return computerNumber;
}

void exerciseFive()
{
    int computerNumber = 0, playerNumber = 0;
    const int N = 3;

    computerNumber = createRandomNumberForBikoveAndKraviGame();

    cout << "Created random number for Bikove and Kravi Game." << endl << "Begin game!" << endl;

     int* digitsOfComputerNumber = returnDigitsOfNumberInArray(computerNumber);

    for (int i = 0; i < N; i++)
    {
        cout << "Number of guesses left: " << N - i << " | Enter your next guess: "; 
        cin >> playerNumber;

        if (playerNumber == computerNumber)
        {
            cout << "The player has guessed the correct number in not more than " << N << " turns. Congrats!";
            return;
        }

        int* digitsOfPlayerNumber = returnDigitsOfNumberInArray(playerNumber);

        int a = digitsOfComputerNumber[0];
        int b = digitsOfComputerNumber[1];
        int c = digitsOfComputerNumber[2];
        int d = digitsOfComputerNumber[3];

        outputBikoveAndKravi(digitsOfPlayerNumber, digitsOfComputerNumber);
    }

    cout << "The player was unable to guess the correct number in " << N << " turns. The number was: " << computerNumber;
}

int main()
{
    //exerciseOne();
    //exerciseTwo();
    //exerciseThree();
    //exerciseFour();
    //exerciseFive();
}

