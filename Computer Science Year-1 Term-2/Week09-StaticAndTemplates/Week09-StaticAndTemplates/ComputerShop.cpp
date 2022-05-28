#include "ComputerShop.h"

bool ComputerShop::computerExists(const Computer& other)
{
	return this->computerExists(other.getBrand());
}

bool ComputerShop::computerExists(std::string brand)
{
	for (size_t i = 0; i < this->computers.size(); i++)
	{
		if (this->computers[i].getBrand() == brand)
		{
			return true;
		}
	}
}

ComputerShop::ComputerShop(std::string name)
{
	this->name = name;
}

void ComputerShop::addComputer(Computer& computer)
{
	for (size_t i = 0; i < this->computers.size(); i++)
	{
		if (this->computers[i].getBrand() == computer.getBrand())
		{
			this->computers[i].setQuantity(this->computers[i].getQuantity() + 1);
			return;
		}
	}

	this->computers.add(computer);
}

void ComputerShop::print()
{
	std::cout << "Here are all the computers of the " << this->name << "\n";
	for (size_t i = 0; i < this->computers.size(); i++)
	{
		std::cout << this->computers[i] << "\n\n";
	}
}

void ComputerShop::buyComputer(std::string brand, double buyersMoney)
{
	bool computerExists = this->computerExists(brand);

	if (!computerExists)
	{
		std::cout << "The computer doesn't exist!!!";
		return;
	}

	int indexOfComputer = -1;
	for (size_t i = 0; i < this->computers.size(); i++)
	{
		if (this->computers[i].getBrand() == brand)
		{
			indexOfComputer = i;
			break;
		}
	}

	double computerPrice = this->computers[indexOfComputer].getPrice();
	int quantity = this->computers[indexOfComputer].getQuantity();

	if (quantity <= 0)
	{
		std::cout << "All of the computers have been bought!!!";
		return;
	}
	else if (computerPrice > buyersMoney)
	{
		std::cout << "The computer is too expensive. Not enough money from buyer!!!";
		return;
	}

	this->computers[indexOfComputer].setQuantity(this->computers[indexOfComputer].getQuantity() - 1);
	std::cout << "Purchase is successful!!!";
}
