// Homework1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstddef>
#include <limits>

using namespace std;

double toPrecisionFloor(double floatValue, int precision)
{
    return floor(floatValue * pow(10, precision)) / pow(10, precision);
}

void exerciseOne()
{
    double x, y;
    cout << "Enter the coordinates of the point(x y): "; cin >> x >> y;

    const string thePointIsOutsideAnyArea = "The point isn't inside any of the coloured areas";

    //The x coordinate of the points B,D
    const double pointX = 2.828;
    //The y coordinate of the points B,D
    const double pointY = 2.828;

    //If x or y are really big values that are guaranteed to be outside the area, then the next calculations might throw an error, so instead return the correct input immediately.
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
    
    //Check if the point is in the pink area
    if (x > -pointX && x < 0 && y < pointY && y > -pointY && abs(x) > abs(y))
    {
        cout << "The point is in the pink area";
    }
    //Check if the point is in the red area
    else if (x > -pointX && x < 0 && y < 4 && y > 0 && abs(y) > abs(x) && distanceToCenterSecondPower < circleRadiusSecondPower)
    {
        cout << "The point is in the red area";
    }
    //Check if the point is in the yellow area
    else if (
        (x < pointX && x > 0 && y < pointY && y > -pointY && abs(x) > abs(y)) ||
        (x < pointX && x > 0 && y > -4 && y < 0 && abs(y) > abs(x) && distanceToCenterSecondPower < circleRadiusSecondPower) ||
        //Edge case when the point is, for example, (2, -2)
        (x > 0 && x < pointX && x == -y) 
        )
    {
        cout << "The point is in the yellow area";
    }
    //Check if the point is in the green area
    else if (x > 0 && x < pointX && y < 4 && y > 0 && abs(y) > abs(x) && distanceToCenterSecondPower < circleRadiusSecondPower)
    {
        cout << "The point is in the green area";
    }
    //Check if the point is in the blue area
    else if (x < 0 && x > -pointX && y > -4 && y < 0 && abs(y) > abs(x) && distanceToCenterSecondPower < circleRadiusSecondPower)
    {
        cout << "The point is in the blue area";
    }
    //Check if the point is in the purple area
    else if (x > pointX && distanceToCenterSecondPower < circleRadiusSecondPower)
    {
        cout << "The point is in the purple area";
    }
    //Check if the point is in the grey area. 
    else if (x > -2 && x < 2 && y > -7 && y < -6)
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
            if (typeCode % 7 == 0) borovinkovTypeCount++;
            else if (typeCode % 13 == 0) praskovTypeCount++;
            else if (typeCode % 17 == 0) shipkovTypeCount++;

            //Annulate the typeCode and stop counting it 
            typeCode = 0;
            currentlyCountingTypeCode = false;
        }

        if (currentlyCountingTypeCode)
        {
            //If the digit isn't positive or even a digit at all, then the barcode is invalid
            if (digit < 0 || digit > 9) 
            {
                currentlyCountingTypeCode = false;
            }
            else 
            {
                typeCode += digit * pow(10, 3 - (i % 4));
            }
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

bool numberContainsZeroAsDigit(int number)
{
    if (number == 0) return true;

    while (number != 0)
    {
        int digit = number % 10;

        if (digit == 0) return true;

        number /= 10;
    }

    return false;
}

bool numberHasRepeatingDigits(int number)
{
    int digitsCount = 0;
    int digits[100] = {};

    if (number >= -9 && number <= 9) return false;

    while (number != 0)
    {
        int digit = number % 10;
        digits[digitsCount] = digit;
        digitsCount++;
        number /= 10;
    }

    if (digitsCount > 10) return true;

    for (int i = 0; i < digitsCount; i++)
    {
        int digit = digits[i];

        for (int y = 0; y < digitsCount; y++)
        {
            int currentDigit = digits[y];
            if (digit == currentDigit && i != y)
            {
                return true;
            }
        }
    }

    return false;
}

int createRandomNumberForBikoveAndKraviGame()
{
    int computerNumber = 0;

    srand(time(NULL));

    while (true)
    {
        computerNumber = rand() % 9000 + 1000;

        int* digitsOfComputerNumber = returnDigitsOfNumberInArray(computerNumber);

        bool repeatingDigits = numberHasRepeatingDigits(computerNumber);
        bool numberContainsZero = numberContainsZeroAsDigit(computerNumber);

        if (repeatingDigits || numberContainsZero) continue;

        return computerNumber;
    }
}

void exerciseFive()
{
    int computerNumber = 0, playerNumber = 0;
    const int N = 3;
    const string invalidInput = "Invalid number input! Try again! \n \n";

    computerNumber = createRandomNumberForBikoveAndKraviGame();

    cout << "Created random number for Bikove and Kravi Game." << endl << "Begin game!" << endl;

    int* digitsOfComputerNumber = returnDigitsOfNumberInArray(computerNumber);

    for (int i = 0; i < N; i++)
    {
        while (true)
        {
            cout << "Number of guesses left: " << N - i << " | Enter your next guess: ";

            if (cin >> playerNumber);
            else 
            {
                cout << invalidInput;
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            if (playerNumber == computerNumber)
            {
                cout << "The player has guessed the correct number in not more than " << N << " turns. Congrats!";
                return;
            }

            //Player number validations
            if (playerNumber < 1000 || playerNumber > 9999)
            {
                cout << invalidInput;
                continue;
            }
            if (numberContainsZeroAsDigit(playerNumber))
            {
                cout << invalidInput;
                continue;
            }
            if (numberHasRepeatingDigits(playerNumber))
            {
                cout << invalidInput;
                continue;
            }

            int* digitsOfPlayerNumber = returnDigitsOfNumberInArray(playerNumber);

            outputBikoveAndKravi(digitsOfPlayerNumber, digitsOfComputerNumber);

            break;
        }
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

