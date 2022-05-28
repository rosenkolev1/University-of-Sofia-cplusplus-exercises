#pragma once

#include <iostream>
#include "List.h"
#include "Computer.h"

class ComputerShop
{
private:
	std::string name;
	List<Computer> computers;
	
	bool computerExists(const Computer& other);
	bool computerExists(std::string brand);

public:

	ComputerShop(std::string name);

	void addComputer(Computer& computer);
	void print();
	void buyComputer(std::string brand, double buyersMoney);
};

