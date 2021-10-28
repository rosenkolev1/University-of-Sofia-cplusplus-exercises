// Zada4a5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
    //Mai raboti samo za x <= 4 && x >= -4. Inache factoriela se 4upi

    double x;
    cin >> x;

    double sum = 0;
    const double eps = 0.00001;

    int numberCount = 0;

    while (true)
    {
        unsigned long long factorialOfNumberCount = 1;

        for (int i = 1; i <= numberCount; i++)
        {
            factorialOfNumberCount *= i;
        }

        double nextNumber = pow(x, numberCount)/ factorialOfNumberCount;

        if (nextNumber < eps && nextNumber > 0 || -nextNumber < eps && nextNumber < 0) break;

        sum += nextNumber;

        numberCount++;
    }

    cout << "This is the sum of the numbers: " <<  sum << endl;
    cout << "Count of numbers: " << numberCount;
}

