#include "MBigNumberDivisionResult.h"
#include "MBigNumber.h"

MBigNumberDivisionResult::MBigNumberDivisionResult(MBigNumber& divisionQuotient, MBigNumber& divisionLeftover)
	:divisionQuotient(divisionQuotient), divisionLeftover(divisionLeftover)
{
}

const MBigNumber& MBigNumberDivisionResult::getQuotient() const
{
	return this->divisionQuotient;
}

const MBigNumber& MBigNumberDivisionResult::getLeftover() const
{
	return this->divisionLeftover;
}

