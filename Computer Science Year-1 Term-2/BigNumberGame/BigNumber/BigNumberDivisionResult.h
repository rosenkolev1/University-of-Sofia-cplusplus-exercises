#pragma once

#include<iostream>

class BigNumber;
class BigNumberDivisionResult
{
private:
	//Quotient means result the result of the division
	BigNumber& divisionQuotient;
	//The leftover (%) part of the division
	BigNumber& divisionLeftover;
public:
	BigNumberDivisionResult(BigNumber& divisionQuotient, BigNumber& divisionLeftover);
	//BigNumberDivisionResult(const BigNumberDivisionResult& other);
	const BigNumber& getQuotient() const;
	const BigNumber& getLeftover() const;
	~BigNumberDivisionResult();
};


