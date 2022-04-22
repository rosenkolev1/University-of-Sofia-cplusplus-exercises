#include "BigNumberDivisionResult.h"
#include "BigNumber.h"

BigNumberDivisionResult::BigNumberDivisionResult(BigNumber& divisionQuotient, BigNumber& divisionLeftover)
	:divisionQuotient(divisionQuotient), divisionLeftover(divisionLeftover)
{
}

const BigNumber& BigNumberDivisionResult::getQuotient() const
{
	return this->divisionQuotient;
}

const BigNumber& BigNumberDivisionResult::getLeftover() const
{
	return this->divisionLeftover;
}

BigNumberDivisionResult::~BigNumberDivisionResult()
{

}
