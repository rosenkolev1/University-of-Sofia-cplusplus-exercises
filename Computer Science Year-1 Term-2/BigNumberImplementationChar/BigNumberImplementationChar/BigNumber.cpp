#include <iostream>
#include <cassert>
#include <cmath>
#include "BigNumberDivisionResult.h"
#include "BigNumber.h"

BigNumber::BigNumber()
{
	this->capacity = INIT_CAPACITY;
	this->size = 1;
	this->number = new char[INIT_CAPACITY];
	this->number[0] = '0';
	this->sign = 0;
	this->uninitializedCopier = false;
}

BigNumber::BigNumber(const BigNumber& other)
{
	this->copy(other);
}

BigNumber::BigNumber(const char* number)
{
	bool otherNumberIsNegative = number[0] == '-';

	long long int numberSize = 0;
	if (otherNumberIsNegative) numberSize++;
	while (number[numberSize] - '0' >= 0 && number[numberSize] - '0' <= 9)
	{
		numberSize++;
	}
	if (otherNumberIsNegative) numberSize--;

	this->capacity = numberSize;
	this->size = numberSize;
	this->uninitializedCopier = false;
	
	//Set sign
	if (otherNumberIsNegative) this->sign = -1;
	else if (numberSize == 1 && number[0] == '0') this->sign = 0;
	else this->sign = 1;

	//Copy the reversed number into this->number
	this->number = new char[numberSize];
	long long int trueSizeOfNumber = otherNumberIsNegative ? numberSize + 1 : numberSize;
	for (long long int i = 0; i < numberSize; i++)
	{
		this->number[i] = number[trueSizeOfNumber - 1 - i];
	}
}

BigNumber::BigNumber(long long int number)
{
	if (number > 0) this->sign = 1;
	else if (number < 0) this->sign = -1;
	else this->sign = 0;

	number = abs(number);

	long long int numberSize = number == 0 ? 1 : 0;
	long long int numberCopy = number;
	while (numberCopy != 0)
	{
		numberSize++;
		numberCopy /= 10;
	}

	this->capacity = numberSize;
	this->size = numberSize;
	this->uninitializedCopier = false;
	this->number = new char[this->capacity];

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
	this->uninitializedCopier = false;
	if(other.uninitializedCopier == false) delete[] this->number;
	this->number = new char[other.capacity];
	for (long long int i = 0; i < other.size; i++)
	{
		this->number[i] = other.number[i];
	}
}

void BigNumber::changeNumber(int* const number, long long int newCapacity, long long int newSize, int sign)
{
	this->capacity = newCapacity;
	this->size = newSize;
	this->sign = sign;
	delete[] this->number;
	this->number = new char[this->capacity];
	for (long long int i = 0; i < this->size; i++)
	{
		this->number[i] = number[i] + '0';
	}
}

/*
@brief Changes the number array to the specified number array
*/
void BigNumber::changeNumber(char* const number, long long int newCapacity, long long int newSize, int sign)
{
	this->capacity = newCapacity;
	this->size = newSize;
	this->sign = sign;
	delete[] this->number;
	this->number = new char[newCapacity];
	for (long long int i = 0; i < newSize; i++)
	{
		this->number[i] = number[i];
	}
}

BigNumber::~BigNumber()
{
	delete[] this->number;
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
	for (long long int i = 0; i < other.size; i++)
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

bool BigNumber::greaterThanOrEqualsAbsolute(const BigNumber& other) const
{
	return BigNumber(this->number) >= BigNumber(other.number);
}

BigNumber BigNumber::addAndReturn(const BigNumber& thisNumber, const BigNumber& other, bool areNegative) const
{
	long long int biggerSize = thisNumber.size > other.size ? thisNumber.size : other.size;
	long long int biggerCapacity = thisNumber.capacity > other.capacity ? thisNumber.capacity : other.capacity;
	biggerCapacity++;

	int carryOver = 0;

	char* newNumber = new char[biggerCapacity + 1];

	for (long long int i = 0; i < biggerSize; i++)
	{
		int digitThis = thisNumber.size > i ? thisNumber.number[i] - '0' : 0;
		int digitOther = other.size > i ? other.number[i] - '0' : 0;

		int sum = digitThis + digitOther + carryOver;
		int newDigit = sum % 10;
		carryOver = sum / 10;

		newNumber[i] = newDigit + '0';
	}

	if (carryOver == 1)
	{
		newNumber[biggerSize] = 1 + '0';
		biggerSize++;
	}

	int signOfNumber = areNegative ? -1 : 1;
	BigNumber newBigNumber = BigNumber();
	newBigNumber.changeNumber(newNumber, biggerCapacity, biggerSize, signOfNumber);
	delete[] newNumber;
	newBigNumber.uninitializedCopier = true;
	return newBigNumber;
}

BigNumber BigNumber::operator+(const BigNumber& other) const
{
	int signOfThis = this->sign;
	int signOfOther = other.sign;

	//Edge cases for 0
	if (signOfThis == 0 && signOfOther == 0)
	{
		BigNumber result = BigNumber();
		result.uninitializedCopier = true;
		return result;
	}

	if (signOfThis == 0 && signOfOther != 0)
	{
		BigNumber result = BigNumber(other);
		result.uninitializedCopier = true;
		return result;
	}
	else if (signOfThis != 0 && signOfOther == 0)
	{
		BigNumber result = BigNumber(*this);
		result.uninitializedCopier = true;
		return result;
	}

	if (signOfThis > signOfOther) // Substraction this - other! Change first digit of other
	{
		//TODO SUBTRACTION
		BigNumber invertedOtherCopy = other;
		invertedOtherCopy.sign *= -1;
		BigNumber result = subtractAndReturn(*this, invertedOtherCopy, false);
		result.uninitializedCopier = true;
		return result;
	}
	else if (signOfThis < signOfOther) // Substraction other - this! Change first digit
	{
		//TODO SUBTRACTION
		BigNumber invertedThisCopy = *this;
		invertedThisCopy.sign *= -1;
		BigNumber result = subtractAndReturn(other, invertedThisCopy, false);
		result.uninitializedCopier = true;
		return result;
	}
	else if (signOfThis == signOfOther && signOfThis > 0)
	{
		BigNumber result = addAndReturn(*this, other, false);
		result.uninitializedCopier = true;
		return result;
	}
	else if (signOfThis == signOfOther && signOfThis < 0)
	{
		BigNumber result = addAndReturn(*this, other, true);
		result.uninitializedCopier = true;
		return result;
	}

	//This is error state
	//return BigNumber();
}

BigNumber& BigNumber::operator+=(const BigNumber& other)
{
	*this = *this + other;
	return *this;
}

//TODO: STOP USING INT ARRAYS BECAUSE IT DEFEATS THE PURPOSE OF USING A CHAR ARRAY FOR THE DIGITS OF THE NUMBERS IN THE FIRST PLACE
BigNumber BigNumber::subtractAndReturn(const BigNumber& thisNumber, const BigNumber& other, bool areNegative) const
{
	long long int biggerSize = thisNumber.size > other.size ? thisNumber.size : other.size;
	long long int biggerCapacity = thisNumber.capacity > other.capacity ? thisNumber.capacity : other.capacity;
	char* newNumber = new char[biggerCapacity];

	int expectedResultsSign = 0;

	BigNumber largerAbsoluteNumber = thisNumber;
	BigNumber smallerAbsoluteNumber = other;

	//Determine which is the bigger number while flipping both of them to being positive integers

	if (thisNumber == other)
	{
		expectedResultsSign = 0;
		return BigNumber();
	}
	else if (thisNumber > other)
	{
		expectedResultsSign = 1;
		if (areNegative)
		{
			largerAbsoluteNumber = other;
			smallerAbsoluteNumber = thisNumber;
		}
		else
		{
			largerAbsoluteNumber = thisNumber;
			smallerAbsoluteNumber = other;
		}
	}
	else if (thisNumber < other)
	{
		expectedResultsSign = -1;
		if (areNegative)
		{
			largerAbsoluteNumber = thisNumber;
			smallerAbsoluteNumber = other;
		}
		else
		{
			largerAbsoluteNumber = other;
			smallerAbsoluteNumber = thisNumber;
		}
	}

	int carryOver = 0;

	for (long long int i = 0; i < biggerSize; i++)
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

		newNumber[i] = subtractionResult + '0';
	}

	//Remove trailing zeroes
	int trailingZeroesCounter = 0;
	for (long long int i = biggerSize - 1; i >= 0; i--)
	{
		if (newNumber[i] != '0') break;
		trailingZeroesCounter++;
	}

	long long int finalSize = biggerSize - trailingZeroesCounter;
	char* newNumberCopy = new char[finalSize];
	for (long long int i = 0; i < finalSize; i++)
	{
		newNumberCopy[i] = newNumber[i];
	}

	delete[] newNumber;
	newNumber = newNumberCopy;

	BigNumber newBigNumber = BigNumber();
	newBigNumber.changeNumber(newNumber, biggerCapacity, finalSize, expectedResultsSign);
	delete[] newNumber;
	newBigNumber.uninitializedCopier = true;
	return newBigNumber;
}

BigNumber BigNumber::operator-(const BigNumber& other) const
{
	int signOfThis = this->sign;
	int signOfOther = other.sign;

	//Edge cases for 0
	if (signOfThis == 0 && signOfOther == 0)
	{
		BigNumber result = BigNumber();
		result.uninitializedCopier = true;
		return result;
	}

	if (signOfThis == 0 && signOfOther != 0)
	{
		BigNumber result = BigNumber(other);
		result.sign *= -1;
		result.uninitializedCopier = true;
		return result;
	}
	else if (signOfThis != 0 && signOfOther == 0)
	{
		BigNumber result = *this;
		result.uninitializedCopier = true;
		return result;
	}

	if (signOfThis > signOfOther) // Addition this + other! Change first digit of other
	{
		//TODO Make Addition
		BigNumber invertedOtherCopy = other;
		invertedOtherCopy.sign *= -1;
		BigNumber result = addAndReturn(*this, invertedOtherCopy, false);
		result.uninitializedCopier = true;
		return result;
	}
	else if (signOfThis < signOfOther) // Equivalent to -(this + other)! Change first digit of this
	{
		//TODO Make Addition
		BigNumber invertedThisCopy = *this;
		invertedThisCopy.sign *= -1;
		BigNumber results = addAndReturn(invertedThisCopy, other, false);
		results.sign *= -1;
		results.uninitializedCopier = true;
		return results;
	}
	else if (signOfThis == signOfOther && signOfThis > 0)
	{
		BigNumber result = subtractAndReturn(*this, other, false);
		result.uninitializedCopier = true;
		return result;
	}
	else if (signOfThis == signOfOther && signOfThis < 0)
	{
		BigNumber result = subtractAndReturn(*this, other, true);
		result.uninitializedCopier = true;
		return result;
	}

	//This is error state
	//return BigNumber();
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
	int smallerSize = thisHasSmallerSize ? this->size : other.size;
	int biggerSize = thisHasSmallerSize ? other.size : this->size;

	const BigNumber& smallerNumber = thisHasSmallerSize ? *this : other;
	const BigNumber& largerNumber = thisHasSmallerSize ? other : *this;


	BigNumber finalMultiplicationSum = BigNumber();
	int zeroesPadding = 0;

	for (long long int i = 0; i < smallerSize; i++)
	{
		int digitOfSmallerNumber = smallerNumber.number[i] - '0';

		//If digit is 0, then just move on to the next digit
		if (digitOfSmallerNumber == 0) continue;

		BigNumber sumOfMultiplicationDigit = BigNumber();
		//Multiply and add together to get the multiplication sum numbers
		for (long long int y = 0; y < biggerSize; y++)
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

			char* digitsOfNewNumber = new char[sizeOfMultiplicationRes + zeroesPadding];
			if (sizeOfMultiplicationRes == 2)
			{
				digitsOfNewNumber[0] = '0' + firstDigitOfRes;
				digitsOfNewNumber[1] = '0' + secondDigitOfRes;
			}
			else digitsOfNewNumber[0] = '0' + secondDigitOfRes;

			for (long long int z = 0; z < zeroesPadding; z++)
			{
				digitsOfNewNumber[z + sizeOfMultiplicationRes] = '0';
			}

			BigNumber multiplicationResNumber = BigNumber(digitsOfNewNumber);
			sumOfMultiplicationDigit += multiplicationResNumber;

			//Cleanup digitsOfNewNumber
			delete[] digitsOfNewNumber;
		}
		//Multiplication with one digits has been made
		//Pad with zeroes
		zeroesPadding = i;
		long long int newSize = sumOfMultiplicationDigit.size + zeroesPadding;
		char* charsOfMultiplication = new char[newSize];

		for (long long int y = 0; y < sumOfMultiplicationDigit.size; y++)
		{
			charsOfMultiplication[y] = sumOfMultiplicationDigit.number[sumOfMultiplicationDigit.size - 1 - y];
		}

		for (long long int y = 0; y < zeroesPadding; y++)
		{
			charsOfMultiplication[sumOfMultiplicationDigit.size + y] = '0';
		}

		BigNumber multiplicationWithDigitFinalSum = BigNumber(charsOfMultiplication);
		finalMultiplicationSum += multiplicationWithDigitFinalSum;

		//Clean up chars of multiplication
		delete[] charsOfMultiplication;
	}

	if (resultIsNegative) finalMultiplicationSum.sign *= -1;

	finalMultiplicationSum.uninitializedCopier = true;
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
		while (true)
		{
			std::cout << "Idiot ";
		}
	}

	if (this->sign == 0)
	{
		BigNumber* divisionQuotient = new BigNumber();
		BigNumber* divisionLeftover = new BigNumber();
		BigNumberDivisionResult divisionResult = BigNumberDivisionResult(*divisionQuotient, *divisionLeftover);
		return divisionResult;
	}

	bool resultIsNegative = this->sign != other.sign;
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

	long long int lowerSize = thisIsBiggerAbsolute ? other.size : this->size;
	long long int upperSize = thisIsBiggerAbsolute ? this->size : other.size;

	//Unreverse the numbers of this and other
	char* largerNumberChars = new char[largerNumber.size];
	for (int i = 0; i < largerNumber.size; i++)
	{
		largerNumberChars[i] = largerNumber.number[largerNumber.size - 1 - i];
	}
	char* smallerNumberChars = new char[smallerNumber.size];
	for (int i = 0; i < smallerNumber.size; i++)
	{
		smallerNumberChars[i] = smallerNumber.number[smallerNumber.size - 1 - i];
	}

	char* tempNumber = new char[lowerSize];
	char* resultChars = new char[upperSize];
	long long int resultCharsCounter = 0;
	long long int finalSize = 0;
	long long int largerNumberCounter = 0;
	long long int tempNumberOffset = 0;
	bool endOfLargeNumberReached = false;
	bool tempIsGarbage = true;
	//Get the initial temp
	for (long long int i = 0; i < lowerSize - 1; i++)
	{
		tempNumber[i] = largerNumberChars[largerNumberCounter];
		largerNumberCounter++;
		tempIsGarbage = false;
		/*if (largerNumberCounter >= largerNumber.size)
		{
			endOfLargeNumberReached = true;
			break;
		}*/
	}
	//START of cycle
	while (largerNumberCounter < largerNumber.size)
	{
		//REMOVE THE FRONT ZERO LATER
		BigNumber tempBigNumber = tempIsGarbage ? BigNumber() : BigNumber(tempNumber);
		bool tempIsLessThanSmaller = tempBigNumber < smallerNumber;
		if (tempIsLessThanSmaller)
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
			for (long long int i = 2; i <= 10; i++)
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
		tempBigNumber.uninitializedCopier = true;
		BigNumber leftOverFromTemp = tempDividedResult == 0 ? tempBigNumber : tempBigNumber - (smallerNumber * BigNumber(tempDividedResult));
		//Change old temp char array to new temp
		delete[] tempNumber;
		tempNumber = new char[lowerSize];
		//temp char array remains with no chars if leftover is 0
		if (leftOverFromTemp.sign != 0)
		{
			for (long long int i = 0; i < leftOverFromTemp.size; i++)
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
	if (resultChars[0] == '0')
	{
		finalSize--;
		char* copyOfResultChars = new char[finalSize];
		for (long long int i = 0; i < finalSize; i++)
		{
			if (i + 1 > upperSize)
			{
				std::cout << "ERROR: Somehow the results char holds more characters than the larger of the numbers being divided";
			}
			copyOfResultChars[i] = resultChars[i + 1];
		}
		delete[] resultChars;
		resultChars = copyOfResultChars;
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

//OPTIONAL
BigNumber BigNumber::operator/(const BigNumber& other) const
{
	BigNumberDivisionResult divisionResult = divideAndReturn(other);
	BigNumber divisionQuotient = divisionResult.getQuotient();
	divisionQuotient.uninitializedCopier = true;
	//MAIKO MILA KOLKO VREME MI OTNE DA UPRAVQ SHIBANIQT MEMORI LEAK BEZ DA RAZRUSHA VUTRESNITE MEMORY UDRESI. FUUUUK
	delete&(divisionResult.getQuotient());
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
	divisionLeftover.uninitializedCopier = true;
	//MAIKO MILA KOLKO VREME MI OTNE DA UPRAVQ SHIBANIQT MEMORI LEAK BEZ DA RAZRUSHA VUTRESNITE MEMORY UDRESI. FUUUUK
	delete& (divisionResult.getQuotient());
	delete& (divisionResult.getLeftover());
	return divisionLeftover;
}

BigNumber& BigNumber::operator%=(const BigNumber& other)
{
	*this = *this % other;
	return *this;
}

//Printing shit and reading shit
void BigNumber::printOutNumber()
{
	//Cacluclate comma spacings
	bool addCommas = this->size >= 5;
	int threeDigitSpaces = this->size / 3;
	int leftOverDigitSpaces = this->size % 3;
	int initialDigitsSpaces = leftOverDigitSpaces != 0 ? leftOverDigitSpaces : 3;
	int commaCounter = leftOverDigitSpaces != 0 ? threeDigitSpaces : threeDigitSpaces - 1;
	int commaStep = initialDigitsSpaces;

	if (this->sign == -1) std::cout << '-';
	for (long long int i = this->size - 1; i >= 0; i--)
	{
		std::cout << this->number[i];
		commaStep--;
		if (commaStep == 0 && commaCounter > 0 && addCommas)
		{
			std::cout << ",";
			commaCounter--;
			commaStep = 3;
		}
	}
	std::cout << std::endl;
}


std::istream& operator>>(std::istream& cin, BigNumber& other)
{
	//
	char* number = new char[100000000];

	cin.getline(number, INT_MAX - 1);

	std::cout << "This is the number: " << number << std::endl;

	int numberSign = number[0] == '-' ? -1 : 1;
	if (number[0] == '0') numberSign = 0;

	long long int sizeOfNumber = 0;
	if (numberSign < 0) sizeOfNumber++;
	while (number[sizeOfNumber])
	{
		sizeOfNumber++;
	}
	if (numberSign < 0) sizeOfNumber--;

	char* reversedNumber = new char[sizeOfNumber];

	int numberTrueSize = numberSign < 0 ? sizeOfNumber + 1 : sizeOfNumber;

	for (long long int i = 0; i < sizeOfNumber; i++)
	{
		reversedNumber[i] = number[numberTrueSize - 1 - i];
	}

	delete[] number;
	long long int largerCapacity = other.capacity > sizeOfNumber + 1 ? other.capacity : sizeOfNumber + 1;

	other.changeNumber(reversedNumber, largerCapacity, sizeOfNumber, numberSign);

	delete[] reversedNumber;

	return cin;
}
