#include "Computer.h"

int Computer::objectId = 0;

void Computer::copy(const Computer& other)
{
	this->setBrand(other.brand);
	this->setProcessor(other.processor);
	this->setVideo(other.video);
	this->setHarddrive(other.harddrive);
	this->setWeight(other.weight);
	this->setBatteryLife(other.batteryLife);
	this->setPrice(other.price);
	this->setQuantity(other.quantity);
}

Computer::Computer()
	:Computer("NovBrand", "NovProcessor", "NovoVideo", "NovHarddrive", 2, 5, 1000, 3)
{
}

Computer::Computer(std::string brand, std::string processor, std::string video, std::string harddrive, double weight, double batteryLife, double price, int quantity)
{
	this->objectId++;
	this->serialNumber = this->objectId;
	this->setBrand(brand);
	this->setProcessor(processor);
	this->setHarddrive(harddrive);
	this->setWeight(weight);
	this->setBatteryLife(batteryLife);
	this->setPrice(price);
	this->setQuantity(quantity);
}

int Computer::getSerialNumber() const
{
	return this->serialNumber;
}

Computer::Computer(const Computer& other)
{
	copy(other);
}

Computer& Computer::operator=(const Computer& other)
{
	copy(other);
	return *this;
}

std::string Computer::getBrand() const
{
	return this->brand;
}

void Computer::setBrand(std::string brand)
{
	this->brand = brand;
}

std::string Computer::getProcessor() const
{
	return this->processor;
}

void Computer::setProcessor(std::string processor)
{
	this->processor = processor;
}

std::string Computer::getVideo() const
{
	return this->video;
}

void Computer::setVideo(std::string video)
{
	this->video = video;
}

std::string Computer::getHarddrive() const
{
	return this->harddrive;
}

void Computer::setHarddrive(std::string harddrive)
{
	this->harddrive = harddrive;
}

double Computer::getWeight() const
{
	return this->weight;
}

void Computer::setWeight(double weight)
{
	this->weight = weight;
}

double Computer::getBatteryLife() const
{
	return this->batteryLife;
}

void Computer::setBatteryLife(double batteryLife)
{
	this->batteryLife = batteryLife;
}

double Computer::getPrice() const
{
	return this->price;
}

void Computer::setPrice(double price)
{
	this->price = price;
}

int Computer::getQuantity() const
{
	return this->quantity;
}

void Computer::setQuantity(int quantity)
{
	this->quantity = quantity;
}

std::ostream& operator<<(std::ostream& os, const Computer& other)
{
	os << "Computer: SN#" << other.getSerialNumber() << " | " << other.brand << "\n";
	os << "Processor" << other.getProcessor() << "\n";
	os << "Video Card: " << other.getVideo() << "\n";
	os << "Harddrive" << other.getHarddrive() << "\n";
	os << "Weight" << other.getWeight() << "\n";
	os << "Battery Life: " << other.getBatteryLife() << "\n";
	os << "Price: " << other.getPrice() << "\n";
	os << "Quantity: " << other.getQuantity();

	return os;
}

std::istream& operator>> (std::istream& is, Computer& other)
{
	std::cout << "Entering computer: \n";

	std::string brand;
	std::string processor;
	std::string video;
	std::string harddrive;
	double weight;
	double batteryLife;
	double price;
	int quantity;

	std::cout << "Brand:  ";
	is >> brand;
	std::cout << "Processor";
	is >> processor;
	std::cout << "Video Card: ";
	is >> video;
	std::cout << "Harddrive";
	is >> harddrive;
	std::cout << "Weight";
	is >> weight;
	std::cout << "Battery Life: ";
	is >> batteryLife;
	std::cout << "Price: ";
	is >> price;
	std::cout << "Quantity: ";
	is >> quantity;

	other.setBrand(brand);
	other.setProcessor(processor);
	other.setVideo(video);
	other.setHarddrive(harddrive);
	other.setWeight(weight);
	other.setBatteryLife(batteryLife);
	other.setPrice(price);
	other.setQuantity(quantity);

	return is;
}
