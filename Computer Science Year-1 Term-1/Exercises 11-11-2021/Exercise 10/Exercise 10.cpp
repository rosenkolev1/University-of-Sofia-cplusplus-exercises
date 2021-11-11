// Exercise 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

bool checkIfPointLineIsParallelToAxis(double x1, double y1, double x2, double y2)
{
	return ( (x1 == x2) ^ (y1 == y2) );
}

int main()
{
	double x1, y1, x2, y2;
	
	do
	{
		cout << "Enter the coordinates of the first point(x y): "; cin >> x1 >> y1;
		cout << "Enter the coordinates of the second point(x y): "; cin >> x2 >> y2;

		cout << (checkIfPointLineIsParallelToAxis(x1, y1, x2, y2) ? "The points form a line, parallel to one of the axis!" : "The points don't form a line that is parallel to one of the axis!") << endl << endl;
	} while ( !(x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0) );
}