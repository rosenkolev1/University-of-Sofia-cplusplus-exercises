// GuzTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "List.h"

int main()
{
	List<int> intList;

	for (size_t i = 0; i < 20; i++)
	{
		intList.add(i);
	}

	std::cout << "Adding to list: " << intList << "\n\n";

	for (size_t i = 5; i < 10; i++)
	{
		intList.removeAt(i);
	}

	std::cout << "Removing 5-9 from list" << intList << "\n\n";

	std::cout << "\nIs the list empty: " << (intList.isEmpty() ? "Empty" : "NOT-Empty") << std::endl;
	std::cout << "The list size: " << intList.getSize() << std::endl;

	List<int> intListCopy1(intList);
	List<int> intListCopy2 = intList;
	std::cout << intListCopy1 << std::endl;
	std::cout << intListCopy2 << std::endl;

	std::cout << "Print 20 from the intList with [] operator: " << intList[14];
}

