#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
#include "BigNumberDivisionResult.h"
#include "BigNumber.h"
#include "..\Project.StringManipulation\StringManip.h"

BigNumber::BigNumber()
{
	this->capacity = INIT_CAPACITY;
	this->size = 1;
	this->number = new char[INIT_CAPACITY];
	this->number[0] = '0';
	this->number[1] = '\0';
	this->sign = 0;
}

BigNumber::BigNumber(const BigNumber& other)
	:BigNumber()
{
	this->copy(other);
}

BigNumber::BigNumber(const char* number)
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

	this->capacity = numberSize + 1;
	this->size = numberSize;
	this->number = new char[this->capacity];
	this->number[this->size] = '\0';

	//Digits are stored in reverse. 
	for (long long int i = numberSize - 1; i >= 0; i--)
	{
		int digit = number % 10;
		number /= 10;
		this->number[numberSize - 1 - i] = '0' + digit;
	}
}

void BigNumber::copy(const BigNumber& other)
{
	this->capacity = other.capacity;
	this->size = other.size;
	this->sign = other.sign;
	delete[] this->number;
	this->number = new char[other.capacity];
	this->number[other.size] = '\0';
	for (size_t i = 0; i < other.size; i++)
	{
		this->number[i] = other.number[i];
	}
}

/*
@brief Changes the number array to the specified number array
*/
void BigNumber::changeNumber(const char* number)
{
	bool otherNumberIsNegative = number[0] == '-';

	size_t numberSize = 0;
	if (otherNumberIsNegative) numberSize++;
	while (number[numberSize] - '0' >= 0 && number[numberSize] - '0' <= 9)
	{
		numberSize++;
	}
	if (otherNumberIsNegative) numberSize--;

	//Set sign
	if (otherNumberIsNegative) this->sign = -1;
	else if (numberSize == 1 && number[0] == '0' || numberSize == 0) this->sign = 0;
	else this->sign = 1;

	//Delete the old number
	delete[] this->number;

	//If the number size is =0, then create the bigNumber as 0
	if (numberSize == 0)
	{
		this->capacity = 2;
		this->size = 1;
		this->number = new char[2];
		this->number[0] = '0';
		this->number[1] = '\0';
		return;
	}

	this->capacity = numberSize + 1;
	this->size = numberSize;

	//Copy the reversed number into this->number
	this->number = new char[this->capacity];
	this->number[this->size] = '\0';
	size_t trueSizeOfNumber = otherNumberIsNegative ? numberSize + 1 : numberSize;
	for (size_t i = 0; i < numberSize; i++)
	{
		this->number[i] = number[trueSizeOfNumber - 1 - i];
	}
}

BigNumber::~BigNumber()
{
	delete[] this->number;
}

int BigNumber::getSign()
{
	return this->sign;
}

BigNumber& BigNumber::operator=(const BigNumber& other)
{
	if (this != &other)
	{
		copy(other);
	}
	return *this;
}

bool BigNumber::operator==(const BigNumber& other) const
{
	//Compare the numbers
	if (other.size != this->size) return false;
	if (this->sign != other.sign) return false;
	for (size_t i = 0; i < other.size; i++)
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
		//Check by size of numbers second
		if (this->size > other.size) return true;
		else if (this->size < other.size) return false;
		else
		{
			for (long long int i = other.size - 1; i >= 0; i--)
			{
				int thisDigit = this->number[i] - '0';
				int otherDigit = other.number[i] - '0';
				//Return if the digits arent equal. Continue cycle if digits are equal
				if (thisDigit > otherDigit) return true;
				else if (thisDigit < otherDigit) return false;
			}
		}
	}
	else if (signOfOther < 0 && signOfThis < 0)
	{
		//Check by size of numbers second
		if (this->size > other.size) return false;
		else if (this->size < other.size) return true;
		else
		{
			for (long long int i = other.size - 1; i >= 0; i--)
			{
				//abs is included here because the front digits are negative, which means comparing them is weird
				int thisDigit = this->number[i] - '0';
				int otherDigit = other.number[i] - '0';
				//Return if the digits arent equal. Continue cycle if digits are equal
				if (thisDigit > otherDigit) return false;
				else if (thisDigit < otherDigit) return true;
			}
		}
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
	return (*this > other && this->sign == 1) || (*this < other && this->sign == -1);
}

BigNumber BigNumber::addAndReturn(const BigNumber& thisNumber, const BigNumber& other, bool areNegative) const
{
	size_t biggerSize = thisNumber.size > other.size ? thisNumber.size : other.size;
	size_t biggerCapacity = thisNumber.capacity > other.capacity ? thisNumber.capacity : other.capacity;
	biggerCapacity++;

	int carryOver = 0;

	char* reversedNewNumber = new char[biggerSize + 2];
	reversedNewNumber[biggerSize] = '\0';

	for (size_t i = 0; i < biggerSize; i++)
	{
		int digitThis = thisNumber.size > i ? thisNumber.number[i] - '0' : 0;
		int digitOther = other.size > i ? other.number[i] - '0' : 0;

		int sum = digitThis + digitOther + carryOver;
		int newDigit = sum % 10;
		carryOver = sum / 10;

		reversedNewNumber[i] = newDigit + '0';
	}

	if (carryOver == 1)
	{
		reversedNewNumber[biggerSize] = 1 + '0';
		reversedNewNumber[biggerSize+1] = '\0';
		biggerSize++;
	}

	//Reverse the number
	char* newNumber = StringManip::getReverse(reversedNewNumber);
	//Delete dynamic memory
	delete[] reversedNewNumber;

	//If the result number is negative, then append a - to the front of the newNumber
	if (areNegative)
	{
		char* newNumberCopy = new char[strlen(newNumber) + 2];
		newNumberCopy[0] = '-';
		newNumberCopy[1] = '\0';
		strcat(newNumberCopy, newNumber);
		delete[] newNumber;
		newNumber = newNumberCopy;
	}
	
	BigNumber newBigNumber = BigNumber(newNumber);
	
	return newBigNumber;
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
	size_t biggerSize = thisNumber.size > other.size ? thisNumber.size : other.size;
	size_t biggerCapacity = thisNumber.capacity > other.capacity ? thisNumber.capacity : other.capacity;
	char* reversedNewNumber = new char[biggerSize + 1];
	reversedNewNumber[biggerSize] = '\0';
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
		int digitLarger = largerAbsoluteNumber.size > i ? largerAbsoluteNumber.number[i] - '0' : 0;
		int digitSmaller = smallerAbsoluteNumber.size > i ? smallerAbsoluteNumber.number[i] - '0' : 0;

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

		reversedNewNumber[i] = subtractionResult + '0';
	}

	//Remove trailing zeroes
	int trailingZeroesCounter = 0;
	for (long long int i = biggerSize - 1; i >= 0; i--)
	{
		if (reversedNewNumber[i] != '0') break;
		trailingZeroesCounter++;
	}

	size_t finalSize = biggerSize - trailingZeroesCounter;

	char* reversedNewNumberCopy = StringManip::getFrom(reversedNewNumber, 0, finalSize - 1);
	delete[] reversedNewNumber;
	reversedNewNumber = reversedNewNumberCopy;

	//Reverse the number
	char* newNumber = StringManip::getReverse(reversedNewNumber);

	//If the expectedResultsSign is negative, then append a - to the front of the new number
	if (expectedResultsSign < 0)
	{
		char* newNumberCopy = new char[strlen(newNumber) + 2];
		newNumberCopy[0] = '-';
		newNumberCopy[1] = '\0';
		strcat(newNumberCopy, newNumber);
		delete[] newNumber;
		newNumber = newNumberCopy;
	}

	//Delete dynamic memory
	delete[] reversedNewNumber;

	BigNumber newBigNumber = BigNumber(newNumber);
	delete[] newNumber;
	return newBigNumber;
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

	bool thisHasSmallerSize = this->size < other.size;
	size_t smallerSize = thisHasSmallerSize ? this->size : other.size;
	int biggerSize = thisHasSmallerSize ? other.size : this->size;

	const BigNumber& smallerNumber = thisHasSmallerSize ? *this : other;
	const BigNumber& largerNumber = thisHasSmallerSize ? other : *this;

	BigNumber finalMultiplicationSum = BigNumber();
	int zeroesPadding = 0;

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

			char* digitsOfNewNumber = new  char[sizeOfMultiplicationRes + zeroesPadding + 1];
			digitsOfNewNumber[sizeOfMultiplicationRes + zeroesPadding] = '\0';
			if (sizeOfMultiplicationRes == 2)
			{
				digitsOfNewNumber[0] = '0' + firstDigitOfRes;
				digitsOfNewNumber[1] = '0' + secondDigitOfRes;
			}
			else digitsOfNewNumber[0] = '0' + secondDigitOfRes;

			for (size_t z = 0; z < zeroesPadding; z++)
			{
				digitsOfNewNumber[z + sizeOfMultiplicationRes] = '0';
			}

			BigNumber multiplicationResNumber = BigNumber(digitsOfNewNumber);
			sumOfMultiplicationDigit += multiplicationResNumber;

			//Delete dynamic memory
			delete[] digitsOfNewNumber;
		}
		//Multiplication with one digits has been made
		//Pad with zeroes
		zeroesPadding = i;
		size_t newSize = sumOfMultiplicationDigit.size + zeroesPadding;
		char* charsOfMultiplication = new char[newSize + 1];
		charsOfMultiplication[newSize] = '\0';

		for (size_t y = 0; y < sumOfMultiplicationDigit.size; y++)
		{
			charsOfMultiplication[y] = sumOfMultiplicationDigit.number[sumOfMultiplicationDigit.size - 1 - y];
		}

		for (size_t y = 0; y < zeroesPadding; y++)
		{
			charsOfMultiplication[sumOfMultiplicationDigit.size + y] = '0';
		}

		BigNumber multiplicationWithDigitFinalSum = BigNumber(charsOfMultiplication);
		finalMultiplicationSum += multiplicationWithDigitFinalSum;

		//Delete dynamic memory
		delete[] charsOfMultiplication;
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
	if (*this == other)
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

	size_t lowerSize = thisIsBiggerAbsolute ? other.size : this->size;
	size_t upperSize = thisIsBiggerAbsolute ? this->size : other.size;

	//Unreverse the numbers of this and other
	char* largerNumberChars = StringManip::getReverse(largerNumber.number);

	char* smallerNumberChars = StringManip::getReverse(smallerNumber.number);

	char* tempNumber = new char[lowerSize + 1];
	tempNumber[lowerSize] = '\0';
	char* resultChars = new char[upperSize + 1];
	resultChars[upperSize] = '\0';

	size_t resultCharsCounter = 0;
	size_t finalSize = 0;
	size_t largerNumberCounter = 0;
	bool endOfLargeNumberReached = false;
	bool tempIsGarbage = true;
	//Get the initial temp
	for (size_t i = 0; i < lowerSize - 1; i++)
	{
		tempNumber[i] = largerNumberChars[largerNumberCounter];
		largerNumberCounter++;
		tempIsGarbage = false;
	}

	//START of cycle
	while (largerNumberCounter < largerNumber.size)
	{
		//REMOVE THE FRONT ZERO LATER
		BigNumber tempBigNumber = tempIsGarbage ? BigNumber() : BigNumber(tempNumber);
		if (tempBigNumber < smallerNumber)
		{
			if (!endOfLargeNumberReached)
			{
				tempBigNumber *= BIGNUMBER10;
				tempBigNumber += BigNumber(largerNumber.number[largerNumber.size - 1 - largerNumberCounter] - '0');
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
					resultChars[resultCharsCounter] = (tempDividedResult)+'0';
					resultCharsCounter++;
					finalSize++;
					break;
				}
			}
		}
		else
		{
			resultChars[resultCharsCounter] = '0';
			resultCharsCounter++;
			finalSize++;
		}
		BigNumber leftOverFromTemp = tempDividedResult == 0 ? tempBigNumber : tempBigNumber - (smallerNumber * BigNumber(tempDividedResult));
		//Change old temp char array to new temp
		delete[] tempNumber;
		tempNumber = new char[lowerSize + 1];
		tempNumber[lowerSize] = '\0';

		//temp char array remains with no chars if leftover is 0
		if (leftOverFromTemp.sign != 0)
		{
			for (size_t i = 0; i < leftOverFromTemp.size; i++)
			{
				tempNumber[i] = leftOverFromTemp.number[leftOverFromTemp.size - 1 - i];
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
	if (StringManip::stringStartsWith(resultChars, "0"))
	{
		char* newResultChars = StringManip::replaceFrom(resultChars, "", 0, 0);
		delete[] resultChars;
		resultChars = newResultChars;
		finalSize--;
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

	//Delete dynamic memory
	delete[] resultChars;
	delete[] tempNumber;
	delete[] smallerNumberChars;
	delete[] largerNumberChars;

	return divisionResult;
}

//OPTIONAL
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

const char* BigNumber::getNumber() const
{
	//Calculate comma spacings
	bool addCommas = this->size >= 5;
	int threeDigitSpaces = this->size / 3;
	int leftOverDigitSpaces = this->size % 3;
	int initialDigitsSpaces = leftOverDigitSpaces != 0 ? leftOverDigitSpaces : 3;
	int commaCounter = leftOverDigitSpaces != 0 ? threeDigitSpaces : threeDigitSpaces - 1;
	int commaStep = initialDigitsSpaces;

	//Get the number string size and create it
	size_t numberStringSize = this->size + commaCounter;
	if (!addCommas) numberStringSize -= commaCounter;
	if (this->sign == -1) numberStringSize++;
	char* numberString = new char[numberStringSize + 1];
	numberString[numberStringSize] = '\0';
	size_t numberStringIndex = 0;

	if (this->sign == -1) numberString[numberStringIndex++] = '-';
	for (long long int i = this->size - 1; i >= 0; i--)
	{
		numberString[numberStringIndex++] = this->number[i];
		commaStep--;
		if (commaStep == 0 && commaCounter > 0 && addCommas)
		{
			numberString[numberStringIndex++] = ',';
			commaCounter--;
			commaStep = 3;
		}
	}
	return numberString;
}

const char* BigNumber::getNumberRaw() const
{
	//Get the number string size and create it
	/*numberString[numberStringSize] = '\0';
	size_t numberStringIndex = 0;

	if (this->sign == -1) numberString[numberStringIndex++] = '-';
	for (long long int i = this->size - 1; i >= 0; i--)
	{
		numberString[numberStringIndex++] = this->number[i];
	}*/

	char* numberString = StringManip::getReverse(this->number);
	if (this->sign == -1)
	{
		char* numberStringCopy = new char[strlen(numberString) + 2];
		numberStringCopy[0] = '-';
		numberStringCopy[1] = '\0';
		strcat(numberStringCopy, numberString);
		delete[] numberString;
		numberString = numberStringCopy;
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
	const char* numberTextRaw = getNumberRaw();
	std::cout << numberTextRaw;
}

std::istream& operator>>(std::istream& is, BigNumber& other)
{
	//Lets just agree that 100000000 is the max symbol count of a BigNumber
	char* number = new char[100000002];
	number[100000001] = '\0';

	is.getline(number, 100000001);

	int numberSign = number[0] == '-' ? -1 : 1;
	//In this case the new number is just 0
	if (number[0] == '0')
	{
		other.changeNumber("0");
		return is;
	}

	/*size_t sizeOfNumber = 0;
	if (numberSign < 0) sizeOfNumber++;
	while (number[sizeOfNumber])
	{
		sizeOfNumber++;
	}
	if (numberSign < 0) sizeOfNumber--;

	char* reversedNumber = new char[sizeOfNumber];

	int numberTrueSize = numberSign < 0 ? sizeOfNumber + 1 : sizeOfNumber;

	for (size_t i = 0; i < sizeOfNumber; i++)
	{
		reversedNumber[i] = number[numberTrueSize - 1 - i];
	}

	delete[] number;
	size_t largerCapacity = other.capacity > sizeOfNumber + 1 ? other.capacity : sizeOfNumber + 1;

	other.changeNumber(reversedNumber, largerCapacity, sizeOfNumber, numberSign);*/
	other.changeNumber(number);

	return is;
}

std::ostream& operator<<(std::ostream& os, const BigNumber& other) 
{
	const char* numberVerbose = other.getNumber();
	os << numberVerbose;
	return os;
}

std::ofstream& operator<<(std::ofstream& os, const BigNumber& other)
{
	const char* number = other.getNumber();
	os.write(number, strlen(number));
	return os;
}


