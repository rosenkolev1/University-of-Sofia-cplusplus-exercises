#pragma once

#include<iostream>

class MBigNumber;
class MBigNumberDivisionResult
{
private:
	//Quotient means result the result of the division
	MBigNumber& divisionQuotient;
	//The leftover (%) part of the division
	MBigNumber& divisionLeftover;
public:
	MBigNumberDivisionResult(MBigNumber& divisionQuotient, MBigNumber& divisionLeftover);
	const MBigNumber& getQuotient() const;
	const MBigNumber& getLeftover() const;
};

