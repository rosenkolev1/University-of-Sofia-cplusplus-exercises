#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
#include "BigNumberDivisionResult.h"
#include "BigNumber.h"
#include "..\Project.StringManipulation\MStringManip.h"

BigNumber::BigNumber()
{
	this->number = "0";
	this->sign = 0;
}

BigNumber::BigNumber(mstring number)
	:BigNumber()
{
	changeNumber(number);
}

BigNumber::BigNumber(long long int number)
{
	if (number > 0) this->sign = 1;
	else if (number < 0) this->sign = -1;
	else this->sign = 0;

	number = abs(number);

	size_t numberSize = number == 0 ? 1 : 0;
	size_t numberCopy = number;
	while (numberCopy != 0)
	{
		numberSize++;
		numberCopy /= 10;
	}

	//Digits are stored in reverse. 
	for (long long int i = numberSize - 1; i >= 0; i--)
	{
		int digit = number % 10;
		number /= 10;
		this->number += ('0' + digit);
	}
}

/*
@brief Changes the number array to the specified number array
*/
void BigNumber::changeNumber(mstring number)
{
	bool otherNumberIsNegative = number[0] == '-';

	size_t trueSizeOfNumber = number.getSize();
	size_t numberSize = otherNumberIsNegative ? trueSizeOfNumber - 1 : trueSizeOfNumber;

	//Set sign
	if (otherNumberIsNegative) this->sign = -1;
	else if (numberSize == 1 && number[0] == '0' || numberSize == 0) this->sign = 0;
	else this->sign = 1;

	//If the number size is 0, then create the bigNumber as 0
	if (numberSize == 0)
	{
		this->number = "0";
		return;
	}

	mstring newNumber;
	for (size_t i = 0; i < numberSize; i++)
	{
		newNumber += number[trueSizeOfNumber - 1 - i];
	}

	this->number = newNumber;
}

int BigNumber::getSign()
{
	return this->sign;
}

bool BigNumber::operator==(const BigNumber& other) const
{
	//Compare the numbers
	if (other.number.getSize() != this->number.getSize()) return false;
	if (this->sign != other.sign) return false;
	for (size_t i = 0; i < other.number.getSize(); i++)
	{
		if (this->number[i] != other.number[i]) return false;
	}

	return true;
}

bool BigNumber::operator!=(const BigNumber& other) const
{
	return !(other == *this);
}

bool BigNumber::operator<(const BigNumber& other) const
{
	return !(*this > other) && !(*this == other);
}

bool BigNumber::operator<=(const BigNumber& other) const
{
	return !(*this > other);
}

bool BigNumber::operator>(const BigNumber& other) const
{
	int signOfOther = other.sign;
	int signOfThis = this->sign;

	//Check by sign of numbers first
	//Edge cases for 1 or both of the numbers being 0
	if (signOfOther == 0) return signOfThis > 0 ? true : false;
	if (signOfThis == 0) return signOfOther < 0 ? true : false;

	//Normal cases
	if (signOfOther > 0 && signOfThis < 0) return false;
	else if (signOfOther < 0 && signOfThis > 0) return true;
	else if (signOfOther > 0 && signOfThis > 0)
	{
		int comparisonResult = this->compareByAbsolute(other);
		return comparisonResult == 1;
	}
	else if (signOfOther < 0 && signOfThis < 0)
	{
		int comparisonResult = this->compareByAbsolute(other);
		return comparisonResult == -1;
	}

	//If we get to this point, then the 2 numbers are equal, meaning that we return false
	return false;
}

bool BigNumber::operator>=(const BigNumber& other) const
{
	return *this > other || *this == other;
}

bool BigNumber::isZero() const
{
	return this->sign == 0;
}

bool BigNumber::greaterThanOrEqualsAbsolute(const BigNumber& other) const
{
	return this->compareByAbsolute(other) >= 0;
}

int BigNumber::compareByAbsolute(const BigNumber& other) const
{
	if (this->number.getSize() > other.number.getSize()) return 1;
	else if (this->number.getSize() < other.number.getSize()) return -1;
	else
	{
		for (long long int i = other.number.getSize() - 1; i >= 0; i--)
		{
			int thisDigit = this->number[i] - '0';
			int otherDigit = other.number[i] - '0';
			//Return if the digits arent equal. Continue cycle if digits are equal
			if (thisDigit > otherDigit) return 1;
			else if (thisDigit < otherDigit) return -1;
		}
	}

	//If we get to here, then the numbers were equal by absolute value
	return 0;
}

BigNumber BigNumber::addAndReturn(const BigNumber& thisNumber, const BigNumber& other, bool areNegative) const
{
	size_t biggerSize = thisNumber.number.getSize() > other.number.getSize() ? thisNumber.number.getSize() : other.number.getSize();

	int carryOver = 0;

	mstring reversedNewNumber;

	for (size_t i = 0; i < biggerSize; i++)
	{
		int digitThis = thisNumber.number.getSize() > i ? thisNumber.number[i] - '0' : 0;
		int digitOther = other.number.getSize() > i ? other.number[i] - '0' : 0;

		int sum = digitThis + digitOther + carryOver;
		int newDigit = sum % 10;
		carryOver = sum / 10;

		reversedNewNumber += (newDigit + '0');
	}

	if (carryOver == 1)
	{
		reversedNewNumber += (1 + '0');
		biggerSize++;
	}

	//Reverse the number
	mstring newNumber = MStringManip::getReverse(reversedNewNumber);

	//If the result number is negative, then append a - to the front of the newNumber
	if (areNegative)
	{
		newNumber.push_front("-");
	}

	return newNumber;
}

BigNumber BigNumber::operator+(const BigNumber& other) const
{
	int signOfThis = this->sign;
	int signOfOther = other.sign;

	//Edge cases for 0
	if (signOfThis == 0 && signOfOther == 0)
	{
		return BigNumber();
	}

	if (signOfThis == 0 && signOfOther != 0)
	{
		return BigNumber(other);
	}
	else if (signOfThis != 0 && signOfOther == 0)
	{
		return BigNumber(*this);
	}

	if (signOfThis > signOfOther) // Substraction this - other! Change first digit of other
	{
		BigNumber invertedOtherCopy = other;
		invertedOtherCopy.sign *= -1;
		BigNumber result = subtractAndReturn(*this, invertedOtherCopy);
		return result;
	}
	else if (signOfThis < signOfOther) // Substraction other - this! Change first digit
	{
		BigNumber invertedThisCopy = *this;
		invertedThisCopy.sign *= -1;
		BigNumber result = subtractAndReturn(other, invertedThisCopy);
		return result;
	}
	else if (signOfThis == signOfOther && signOfThis > 0)
	{
		BigNumber result = addAndReturn(*this, other, false);
		return result;
	}
	else if (signOfThis == signOfOther && signOfThis < 0)
	{
		BigNumber result = addAndReturn(*this, other, true);
		return result;
	}
}

BigNumber& BigNumber::operator+=(const BigNumber& other)
{
	*this = *this + other;
	return *this;
}

BigNumber BigNumber::subtractAndReturn(const BigNumber& thisNumber, const BigNumber& other) const
{
	size_t biggerSize = thisNumber.number.getSize() > other.number.getSize() ? thisNumber.number.getSize() : other.number.getSize();

	mstring reversedNewNumber;
	int expectedResultsSign = 0;

	//Check if the numbers are equal
	if (thisNumber == other)
	{
		return BigNumber();
	}

	BigNumber largerAbsoluteNumber = thisNumber;
	BigNumber smallerAbsoluteNumber = other;

	//Determine which is the bigger number while flipping both of them to being positive integers
	if (smallerAbsoluteNumber.greaterThanOrEqualsAbsolute(largerAbsoluteNumber))
	{
		largerAbsoluteNumber = other;
		smallerAbsoluteNumber = thisNumber;
	}

	if (thisNumber == other)
	{
		expectedResultsSign = 0;
		return BigNumber();
	}
	else if (thisNumber > other)
	{
		expectedResultsSign = 1;
	}
	else if (thisNumber < other)
	{
		expectedResultsSign = -1;
	}

	int carryOver = 0;

	for (size_t i = 0; i < biggerSize; i++)
	{
		int digitLarger = largerAbsoluteNumber.number.getSize() > i ? largerAbsoluteNumber.number[i] - '0' : 0;
		int digitSmaller = smallerAbsoluteNumber.number.getSize() > i ? smallerAbsoluteNumber.number[i] - '0' : 0;

		bool carryOverLocked = false;

		if (digitLarger - carryOver < 0)
		{
			digitLarger = 9;
		}
		else
		{
			digitLarger -= carryOver;
			carryOver = 0;
		}

		if (digitLarger < digitSmaller && carryOver != 1) carryOver = 1;

		int subtractionResult = digitLarger < digitSmaller ? digitLarger + 10 - digitSmaller : digitLarger - digitSmaller;

		reversedNewNumber += (subtractionResult + '0');
	}

	//Remove trailing zeroes
	int trailingZeroesCounter = 0;
	for (long long int i = biggerSize - 1; i >= 0; i--)
	{
		if (reversedNewNumber[i] != '0') break;
		trailingZeroesCounter++;
	}

	size_t finalSize = biggerSize - trailingZeroesCounter;

	reversedNewNumber = MStringManip::getFrom(reversedNewNumber, 0, finalSize - 1);

	//Reverse the number
	mstring newNumber = MStringManip::getReverse(reversedNewNumber);

	//If the expectedResultsSign is negative, then append a - to the front of the new number
	if (expectedResultsSign < 0)
	{
		newNumber.push_front("-");
	}

	return newNumber;
}

BigNumber BigNumber::operator-(const BigNumber& other) const
{
	int signOfThis = this->sign;
	int signOfOther = other.sign;

	//Edge cases for 0
	if (signOfThis == 0 && signOfOther == 0)
	{
		return BigNumber();
	}

	if (signOfThis == 0 && signOfOther != 0)
	{
		BigNumber result = BigNumber(other);
		result.sign *= -1;
		return result;
	}
	else if (signOfThis != 0 && signOfOther == 0)
	{
		return *this;;
	}

	if (signOfThis > signOfOther) // Addition this + other! Change first digit of other
	{
		BigNumber result = addAndReturn(*this, other, false);
		return result;
	}
	else if (signOfThis < signOfOther) // Equivalent to -(this + other)! Change first digit of this
	{
		BigNumber results = addAndReturn(*this, other, false);
		results.sign *= -1;
		return results;
	}
	else if (signOfThis == signOfOther && signOfThis > 0)
	{
		BigNumber result = subtractAndReturn(*this, other);
		return result;
	}
	else if (signOfThis == signOfOther && signOfThis < 0)
	{
		BigNumber result = subtractAndReturn(*this, other);
		return result;
	}
}

BigNumber& BigNumber::operator-=(const BigNumber& other)
{
	*this = *this - other;
	return *this;
}

BigNumber BigNumber::operator*(const BigNumber& other) const
{
	//Check if either of the numbers are 0
	int thisSign = this->sign;
	int otherSign = other.sign;
	if (thisSign == 0 || otherSign == 0) return BigNumber();

	bool resultIsNegative = thisSign != otherSign;

	bool thisHasSmallerSize = this->number.getSize() < other.number.getSize();
	size_t smallerSize = thisHasSmallerSize ? this->number.getSize() : other.number.getSize();
	size_t biggerSize = thisHasSmallerSize ? other.number.getSize() : this->number.getSize();

	const BigNumber& smallerNumber = thisHasSmallerSize ? *this : other;
	const BigNumber& largerNumber = thisHasSmallerSize ? other : *this;

	BigNumber finalMultiplicationSum = BigNumber();
	size_t zeroesPadding = 0;

	for (size_t i = 0; i < smallerSize; i++)
	{
		int digitOfSmallerNumber = smallerNumber.number[i] - '0';

		//If digit is 0, then just move on to the next digit
		if (digitOfSmallerNumber == 0) continue;

		BigNumber sumOfMultiplicationDigit = BigNumber();
		//Multiply and add together to get the multiplication sum numbers
		for (size_t y = 0; y < biggerSize; y++)
		{
			//Multiply the larger number with the digit from the smaller number
			int digitOfLargerNumber = largerNumber.number[y] - '0';

			//If digit is 0, then just move on to the next digit
			if (digitOfLargerNumber == 0) continue;

			int multiplicationRes = digitOfSmallerNumber * digitOfLargerNumber;

			//Pad with zeroes
			zeroesPadding = y;
			int firstDigitOfRes = multiplicationRes / 10;
			int secondDigitOfRes = multiplicationRes % 10;
			int sizeOfMultiplicationRes = firstDigitOfRes == 0 ? 1 : 2;

			mstring digitsOfNewNumber;
			if (sizeOfMultiplicationRes == 2)
			{
				digitsOfNewNumber += ('0' + firstDigitOfRes);
				digitsOfNewNumber += ('0' + secondDigitOfRes);
			}
			else digitsOfNewNumber += ('0' + secondDigitOfRes);

			for (size_t z = 0; z < zeroesPadding; z++)
			{
				digitsOfNewNumber += '0';
			}

			BigNumber multiplicationResNumber = BigNumber(digitsOfNewNumber);
			sumOfMultiplicationDigit += multiplicationResNumber;
		}
		//Multiplication with one digits has been made
		//Pad with zeroes
		zeroesPadding = i;
		
		mstring charsOfMultiplication;
		for (size_t y = 0; y < sumOfMultiplicationDigit.number.getSize(); y++)
		{
			charsOfMultiplication += sumOfMultiplicationDigit.number[sumOfMultiplicationDigit.number.getSize() - 1 - y];
		}

		for (size_t y = 0; y < zeroesPadding; y++)
		{
			charsOfMultiplication += '0';
		}

		BigNumber multiplicationWithDigitFinalSum = BigNumber(charsOfMultiplication);
		finalMultiplicationSum += multiplicationWithDigitFinalSum;

	}

	if (resultIsNegative) finalMultiplicationSum.sign *= -1;

	return finalMultiplicationSum;
}

BigNumber& BigNumber::operator*=(const BigNumber& other)
{
	*this = *this * other;
	return *this;
}

BigNumberDivisionResult BigNumber::divideAndReturn(const BigNumber& other) const
{
	//Edge Cases for 0
	if (other.sign == 0)
	{
		throw "CANNOT DIVIDE BY ZERO YOU IDIOT!";
	}

	if (this->sign == 0)
	{
		BigNumber* divisionQuotient = new BigNumber();
		BigNumber* divisionLeftover = new BigNumber();
		BigNumberDivisionResult divisionResult = BigNumberDivisionResult(*divisionQuotient, *divisionLeftover);
		return divisionResult;
	}

	bool resultIsNegative = this->sign != other.sign;

	//If the numbers are equal, then just return 1 or -1;
	if (this->number == other.number)
	{
		if (resultIsNegative)
		{
			BigNumber* divisionQuotient = new BigNumber(-1);
			BigNumber* divisionLeftover = new BigNumber();
			BigNumberDivisionResult divisionResult = BigNumberDivisionResult(*divisionQuotient, *divisionLeftover);
			return divisionResult;
		}
		else
		{
			BigNumber* divisionQuotient = new BigNumber(1);
			BigNumber* divisionLeftover = new BigNumber();
			BigNumberDivisionResult divisionResult = BigNumberDivisionResult(*divisionQuotient, *divisionLeftover);
			return divisionResult;
		}
	}

	//Check this and other by absolute value
	bool thisIsBiggerAbsolute = this->greaterThanOrEqualsAbsolute(other);

	BigNumber smallerNumber = thisIsBiggerAbsolute ? other : *this;
	BigNumber largerNumber = thisIsBiggerAbsolute ? *this : other;

	if (smallerNumber.sign < 0) smallerNumber *= -1;
	else if (largerNumber.sign < 0) largerNumber *= -1;

	// this/other = 0; this%other = this
	if (thisIsBiggerAbsolute == false)
	{
		BigNumber* divisionQuotient = new BigNumber();
		BigNumber* divisionLeftover = new BigNumber(*this);
		BigNumberDivisionResult divisionResult = BigNumberDivisionResult(*divisionQuotient, *divisionLeftover);
		return divisionResult;
	}

	const BigNumber BIGNUMBER10 = BigNumber(10);

	size_t lowerSize = thisIsBiggerAbsolute ? other.number.getSize() : this->number.getSize();
	size_t upperSize = thisIsBiggerAbsolute ? this->number.getSize() : other.number.getSize();

	//Unreverse the numbers of this and other
	mstring largerNumberChars = MStringManip::getReverse(largerNumber.number);
	mstring smallerNumberChars = MStringManip::getReverse(smallerNumber.number);
	mstring tempNumber;
	mstring resultChars;

	size_t largerNumberCounter = 0;
	bool endOfLargeNumberReached = false;
	bool tempIsGarbage = lowerSize - 1 <= 0;

	//Get the initial temp
	for (size_t i = 0; i < lowerSize - 1; i++)
	{
		tempNumber += largerNumberChars[largerNumberCounter];
		largerNumberCounter++;
	}

	//START of cycle
	while (largerNumberCounter < largerNumber.number.getSize())
	{
		//REMOVE THE FRONT ZERO LATER
		BigNumber tempBigNumber = tempIsGarbage ? BigNumber() : BigNumber(tempNumber);
		if (tempBigNumber < smallerNumber)
		{
			if (!endOfLargeNumberReached)
			{
				tempBigNumber *= BIGNUMBER10;
				tempBigNumber += BigNumber(largerNumber.number[largerNumber.number.getSize() - 1 - largerNumberCounter] - '0');
				largerNumberCounter++;
			}
		}

		int tempDividedResult = 0;
		if (tempBigNumber >= smallerNumber)
		{
			for (int i = 2; i <= 10; i++)
			{
				BigNumber multiplierBigNumber = BigNumber(i);
				BigNumber multipliedBigNumber = smallerNumber * multiplierBigNumber;
				if (tempBigNumber < multipliedBigNumber)
				{
					tempDividedResult = i - 1;
					resultChars += (tempDividedResult + '0');
					break;
				}
			}
		}
		else
		{
			resultChars += '0';
		}
		BigNumber leftOverFromTemp = tempDividedResult == 0 ? tempBigNumber : tempBigNumber - (smallerNumber * BigNumber(tempDividedResult));
		//Change old temp char array to new temp
		tempNumber = "";

		//temp char array remains with no chars if leftover is 0
		if (leftOverFromTemp.sign != 0)
		{
			for (size_t i = 0; i < leftOverFromTemp.number.getSize(); i++)
			{
				tempNumber += leftOverFromTemp.number[leftOverFromTemp.number.getSize() - 1 - i];
				tempIsGarbage = false;
			}
		}
		else
		{
			tempIsGarbage = true;
		}
	}

	//tempNumber holds the chars of the leftover, i.e % operator result
	//resultChars holds the chars of the division, i.e / operator result. It may or may not have an invalid zero as first integer, however!
	//Remove possible zero as first digit of resultChars
	if (MStringManip::stringStartsWith(resultChars, "0"))
	{
		resultChars = MStringManip::replaceFrom(resultChars, "", 0, 0);
	}

	BigNumber* divisionQuotient = new BigNumber(resultChars);

	//Check if temp number is 0
	BigNumber* divisionLeftover = tempIsGarbage ? new BigNumber() : new BigNumber(tempNumber);

	if (resultIsNegative)
	{
		(*divisionQuotient).sign *= -1;
	}
	if (this->sign < 0) (*divisionLeftover).sign *= -1;

	BigNumberDivisionResult divisionResult = BigNumberDivisionResult(*divisionQuotient, *divisionLeftover);

	return divisionResult;
}

BigNumber BigNumber::operator/(const BigNumber& other) const
{
	BigNumberDivisionResult divisionResult = divideAndReturn(other);
	BigNumber divisionQuotient = divisionResult.getQuotient();
	//MAIKO MILA KOLKO VREME MI OTNE DA UPRAVQ SHIBANIQT MEMORI LEAK BEZ DA RAZRUSHA VUTRESNITE MEMORY UDRESI. FUUUUK
	delete& (divisionResult.getQuotient());
	delete& (divisionResult.getLeftover());
	return divisionQuotient;
}

BigNumber& BigNumber::operator/=(const BigNumber& other)
{
	*this = *this / other;
	return *this;
}

BigNumber BigNumber::operator%(const BigNumber& other) const
{
	BigNumberDivisionResult divisionResult = divideAndReturn(other);
	BigNumber divisionLeftover = divisionResult.getLeftover();
	//MAIKO MILA KOLKO VREME MI OTNE DA UPRAVQ SHIBANIQT MEMORI LEAK BEZ DA RAZRUSHA VUTRESNITE MEMORY UDRESI. FUUUUK
	delete& (divisionResult.getQuotient());
	delete& (divisionResult.getLeftover());
	return divisionLeftover;
}

BigNumber& BigNumber::operator--()
{
	*this -= 1;
	return *this;
}

BigNumber BigNumber::operator--(int)
{
	BigNumber temp = *this;
	*this -= 1;
	return temp;
}

BigNumber& BigNumber::operator++()
{
	*this += 1;
	return *this;
}

BigNumber BigNumber::operator++(int)
{
	BigNumber temp = *this;
	*this += 1;
	return temp;
}

BigNumber& BigNumber::operator%=(const BigNumber& other)
{
	*this = *this % other;
	return *this;
}

mstring BigNumber::getNumber() const
{
	//Calculate comma spacings
	bool addCommas = this->number.getSize() >= 5;
	size_t threeDigitSpaces = this->number.getSize() / 3;
	int leftOverDigitSpaces = this->number.getSize() % 3;
	int initialDigitsSpaces = leftOverDigitSpaces != 0 ? leftOverDigitSpaces : 3;
	int commaCounter = leftOverDigitSpaces != 0 ? threeDigitSpaces : threeDigitSpaces - 1;
	int commaStep = initialDigitsSpaces;

	//Get the number string size and create it
	size_t numberStringSize = this->number.getSize() + commaCounter;
	if (!addCommas) numberStringSize -= commaCounter;
	if (this->sign == -1) numberStringSize++;

	mstring numberString;

	if (this->sign == -1) numberString += '-';
	for (long long int i = this->number.getSize() - 1; i >= 0; i--)
	{
		numberString += this->number[i];
		commaStep--;
		if (commaStep == 0 && commaCounter > 0 && addCommas)
		{
			numberString += ',';
			commaCounter--;
			commaStep = 3;
		}
	}

	return numberString;
}

mstring BigNumber::getNumberRaw() const
{
	//Get the number string in the correct order
	mstring numberString = MStringManip::getReverse(this->number);
	if (this->sign == -1)
	{
		numberString.push_front("-");
	}

	return numberString;
}

//Printing shit and reading shit
void BigNumber::printOutNumber() const
{
	std::cout << *this;
}

void BigNumber::printOutNumberRaw() const
{
	mstring numberTextRaw = getNumberRaw();
	std::cout << numberTextRaw;
}

std::istream& operator>>(std::istream& is, BigNumber& other)
{
	mstring number;
	is >> number;

	int numberSign = number[0] == '-' ? -1 : 1;

	//In this case the new number is just 0
	if (number == '0')
	{
		other.changeNumber("0");
		return is;
	}

	other.changeNumber(number);

	return is;
}

std::ostream& operator<<(std::ostream& os, const BigNumber& other)
{
	mstring numberVerbose = other.getNumber();
	os << numberVerbose;
	return os;
}

std::ofstream& operator<<(std::ofstream& os, const BigNumber& other)
{
	os << other.getNumber();
	return os;
}


