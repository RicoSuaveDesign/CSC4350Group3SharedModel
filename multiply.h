#pragma once

//Cole Sitzberger
//Multiply
using namespace std;

char *intToCStr(int numToConvert);
char *createStringRepOfFloatNum(char *characteristic, char *mantissa);

char* makeCString(int cStringLength) 
{
	cStringLength += 2;
	char *cString = new char[cStringLength];
	int nullIndex;
	for (int i = 0; i < cStringLength - 1; i++) {
		cString[i] = ' ';
		nullIndex = i;
	}
	cString[nullIndex+1] = '\0';
	return cString;
}

int strLength(const char *cString) 
{
	int length = 0;
	while (cString[length] != '\0') 
	{
		length++;
	}
	return length;
}

bool makeNumPositive(int &characteristic, int &numerator, int &denominator) 
{
	bool retVal = false;
	if (characteristic < 0) 
	{
		characteristic = -characteristic;
		retVal = true;
	}
	if (numerator < 0) 
	{
		numerator = -numerator;
		retVal = true;
	}
	if (denominator < 0) 
	{
		denominator = -denominator;
		retVal = true;
	}
	return retVal;
}


int makeNewNumeratorForMultiplycation(int characteristic, int numerator, int denominator) {
	return ((characteristic*denominator) + numerator);
}

void findNumAfterDecimalPlace(int &numerator, int &denominator, bool &addZero, char *output, int &i) 
{
	while (numerator < denominator) 
	{
		if (numerator == 0) 
		{
			break;
		}
		numerator *= 10;

		// will add significant zeros
		if (addZero) 
		{
			output[i] = '0';
			i++;
		}
		addZero = true;
	}
}

char *longDivisionOfFraction(int numBeforeDecimal, int numerator, int denominator, int numLength) 
{
	char *output = makeCString(numLength);
	bool numBiggerThenDenominator;
	int howManyTimesGoesInto;
	bool addZero;
	output[0] = '+';
	if ((numerator < 0) ^ (denominator < 0)) 
	{
		output[0] = '-';
		if (numerator < 0) 
		{
			numerator = -numerator;
		}
		if (denominator < 0) 
		{
			denominator = -denominator;
		}
	}
	for (int i = 1; i <= numLength; i++) {
		numBiggerThenDenominator = numerator > denominator;
		addZero = false;
		findNumAfterDecimalPlace(numerator, denominator, addZero, output, i);
		howManyTimesGoesInto = numerator / denominator;
		if (!numBiggerThenDenominator) {
			output[i] = char('0' + howManyTimesGoesInto);
		}
		else {
			i--;
		}
		if (howManyTimesGoesInto == 0) {
			break;
		}
		numerator -= (denominator*howManyTimesGoesInto);
		if (numBiggerThenDenominator) {
			numBeforeDecimal = howManyTimesGoesInto;
		}
	}
	char *newCharacteristicString = intToCStr(numBeforeDecimal);
	char *floatString = createStringRepOfFloatNum(newCharacteristicString, output);
	delete[]output;
	delete[]newCharacteristicString;
	return floatString;
}

int findPowerOfTenForNum(int powOfNum, int &timesLooped) 
{
	int base = 1;
	while (true) 
	{
		if (powOfNum / base >= 0 && powOfNum / base <= 9) 
		{
			break;
		}
		timesLooped++;
		base *= 10;
	}
	return base;
}

char *intToCStr(int numToConvert) 
{
	int length = 1;
	char sign = '+';
	if (numToConvert < 0) {
		sign = '-';
		numToConvert *= -1;
	}
	int powOf10ForDigit = findPowerOfTenForNum(numToConvert, length);
	char *cStringConvertedFromInt = makeCString(length);
	cStringConvertedFromInt[0] = sign;
	int placeInString = 1;
	for (int i = 0; i < length; i++) 
	{
		int digit = numToConvert / powOf10ForDigit;
		char charVersionOfDigit;
		if (digit == 0)
		{
			charVersionOfDigit = '0';
		}
		else if (digit == 1)
		{
			charVersionOfDigit = '1';
		}
		else if (digit == 2)
		{
			charVersionOfDigit = '2';
		}
		else if (digit == 3)
		{
			charVersionOfDigit = '3';
		}
		else if (digit == 4)
		{
			charVersionOfDigit = '4';
		}
		else if (digit == 5)
		{
			charVersionOfDigit = '5';
		}
		else if (digit == 6)
		{
			charVersionOfDigit = '6';
		}
		else if (digit == 7)
		{
			charVersionOfDigit = '7';
		}
		else if (digit == 8)
		{
			charVersionOfDigit = '8';
		}
		else if (digit == 9)
		{
			charVersionOfDigit = '9';
		}
		cStringConvertedFromInt[placeInString] = charVersionOfDigit;
		numToConvert -= (numToConvert / powOf10ForDigit)*powOf10ForDigit;
		powOf10ForDigit /= 10;
		placeInString++;
	}
	return cStringConvertedFromInt;
}

char *createStringRepOfFloatNum(char *characteristic, char *mantissa) {
	int cLength = strLength(characteristic);
	int mLength = strLength(mantissa);
	int newNumLength = cLength + mLength;
	char *newNumberString = makeCString(newNumLength);
	int offset = 0;
	for (int i = 0; i < cLength; i++) 
	{
		newNumberString[i] = characteristic[i];
		offset = i;
	}
	offset++;
	newNumberString[offset] = '.';
	for (int i = 1; i < mLength; i++) 
	{
		newNumberString[i + offset] = mantissa[i];
	}
	return newNumberString;
}

int numOfDigitsInNumber(int numberToFindDigits)
{
	int numberOfDigits = 0;
	findPowerOfTenForNum(numberToFindDigits, numberOfDigits);
	return numberOfDigits+1;
}

bool testIfNumCanFitInOutputArray(int characteristic, int numerator, int denominator, int length) 
{
	bool retVal = true;
	int characteristicLength = numOfDigitsInNumber(characteristic);
	int numeratorLength = numOfDigitsInNumber(numerator);
	int denominatorLength = numOfDigitsInNumber(denominator);
	if (characteristicLength > length || numeratorLength > length || denominatorLength > length)
	{
		retVal = false;
	}
	return retVal;
}

bool multiply(int characteristic1, int  mantissaNumerator1, int mantissaD1, int characteristic2, int mantissaNumerator2, int mantissaD2, char result[], int len)
{
	bool sign1 = makeNumPositive(characteristic1, mantissaNumerator1, mantissaD1);
	bool sign2 = makeNumPositive(characteristic2, mantissaNumerator2, mantissaD2);
	int newNumerator = makeNewNumeratorForMultiplycation(characteristic1, mantissaNumerator1, mantissaD1) * makeNewNumeratorForMultiplycation(characteristic2, mantissaNumerator2, mantissaD2);
	int newDenominator = mantissaD1 * mantissaD2;
	if (!testIfNumCanFitInOutputArray(characteristic2, newNumerator, newDenominator, len) || !testIfNumCanFitInOutputArray(characteristic1, newNumerator, newDenominator, len))
	{
		return false;
	}
	char *output = longDivisionOfFraction(0, newNumerator, newDenominator, len);
	int offset = 0;
	if (sign1 && sign2) 
	{
		output[0] = '+';
		offset = 1;
	}
	else if (sign1 != sign2)
	{
		if (output[0] == '+')
		{
			output[0] = '-';
		}
		else if (output[0] == '-')
		{
			output[0] = '+';
			offset = 1;
		}
	}
	else if (!sign1 && !sign2)
	{
		offset = 1;
	}
	for (int i = 0; i < len; i++) 
	{
		if (i + 1 == len)
		{
			result[i] = '\0';
		}
		else 
		{
			result[i] = output[i + offset];
		}
	}
	delete[]output;
	return true;
}