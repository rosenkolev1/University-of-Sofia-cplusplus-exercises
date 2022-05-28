#pragma once
#include <string>
#include <iostream>

class Computer
{
private:
	static int objectId;

	int serialNumber;
	std::string brand;
	std::string processor;
	std::string video;
	std::string harddrive;
	double weight;
	double batteryLife;
	double price;
	int quantity;

	void copy(const Computer& other);

public:

	Computer();
	Computer(std::string brand, std::string processor, std::string video, std::string harddrive, double weight, double batteryLife, double price, int quantity);

	Computer(const Computer& other);
	Computer& operator=(const Computer& other);

	//Getter and Setters
	int getSerialNumber() const;

	std::string getBrand() const;
	void setBrand(std::string brand);

	std::string getProcessor() const;
	void setProcessor(std::string processor);

	std::string getVideo() const;
	void setVideo(std::string video);

	std::string getHarddrive() const;
	void setHarddrive(std::string harddrive);

	double getWeight() const;
	void setWeight(double weight);

	double getBatteryLife() const;
	void setBatteryLife(double batteryLife);

	double getPrice() const;
	void setPrice(double price);

	int getQuantity() const;
	void setQuantity(int quantity);

	//IO operators
	friend std::ostream& operator<< (std::ostream& os, const Computer& other);
	friend std::istream& operator>> (std::istream& is, Computer& other);
};

