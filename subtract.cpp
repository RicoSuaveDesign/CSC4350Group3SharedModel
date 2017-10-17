//
//  subtract.cpp
//  subtract_v1
//
//  Created by Tom Shannon on 9/26/17.
//  Copyright © 2017 tom. All rights reserved.
//

#include <iostream>
#include "subtract.h"
using namespace std;

//---------------------------------------------------------------------------------------------------------------------------------------
//									                 Check Mantissa
//---------------------------------------------------------------------------------------------------------------------------------------
bool paramsAreGood(int num1, int num2, int den1, int den2) {
    
    bool goodParams = true;
    
    if(num1 < 0 || num2 < 0) {
        cout << "Mantissa's must be positive integers. Results array was not filled." << endl;
        goodParams = false;
    }
    
    if(den1 < 0 || den2 < 0) {
        cout << "Denominator's must negative integers. Results array was not filled" << endl;
        goodParams = false;
    }
    
    return goodParams;
}

//---------------------------------------------------------------------------------------------------------------------------------------
//									                 Compute Difference
//---------------------------------------------------------------------------------------------------------------------------------------
int computeDifference(int char1, int char2, int denominator, int num1, int num2) {
    
    // Convert numbers to improper numerators; adjust if characteristics are negative
    int number1 = (char1 < 0) ? (char1 * denominator - num1) : (char1 * denominator + num1);
    
    int number2 = (char2 < 0) ? (char2 * denominator - num2) : (char2 * denominator + num2);
    
    return number1 - number2;
}

//---------------------------------------------------------------------------------------------------------------------------------------
//                                                Get Characteristic
//---------------------------------------------------------------------------------------------------------------------------------------

int getCharacteristic(int difference, int denominator){
    
    int characteristic = difference / denominator;
    
    return characteristic;
}

//---------------------------------------------------------------------------------------------------------------------------------------
//                                                   Get Mantissa
//---------------------------------------------------------------------------------------------------------------------------------------
int getMantissa(int difference, int denominator) {
    
    int mantissa = difference % denominator;
    
    mantissa = (mantissa < 0) ? mantissa * -1 : mantissa;
    
    return mantissa;
}

//---------------------------------------------------------------------------------------------------------------------------------------
//                                                Get Number of Digits
//---------------------------------------------------------------------------------------------------------------------------------------
int getNumDigits(int number) {
    
    int numDigits = 0;
    
    while(number /= 10) {
        numDigits++;
    }
    
    return numDigits;
}

//---------------------------------------------------------------------------------------------------------------------------------------
//                                             Get Leading Mantissa Zeros
//---------------------------------------------------------------------------------------------------------------------------------------

int getMantissaZeros(int characteristic, int mantissa, int num1, int num2, int difference) {
    
    // Get the number of digits total
    int charNumDigits = getNumDigits(abs(characteristic));
    int manNumDigits = getNumDigits(abs(mantissa));
    int numDiffDigits = getNumDigits(abs(difference));
    
    // Find the number of digits remaining -- this is the number of zeros
    int totalNumZeros = numDiffDigits - manNumDigits - charNumDigits - 1;
    
    return totalNumZeros;
    
}

//---------------------------------------------------------------------------------------------------------------------------------------
//                                               Get Leading Mantissa Zeros
//---------------------------------------------------------------------------------------------------------------------------------------

int getDigitArray(int number, char results[], int numDigits, int iterator)
{
    int placement = 1;
    
    // Get denominator to divide by, corresponding to number of digits
    for(int i = 1; i <= numDigits; i++) {
        placement *= 10;
    }
    
    // Divide by the placement (denominator) to get each digit
    while(placement >= 1) {
        
        // Get each digit in integer from left to right
        int digit = abs((number / placement) % 10);
        
        //Place digit in char array (add 48 -- start of zero)
        results[iterator] = (char)digit + 48;
        
        // Decrement to get next digit right of last digit and iterate
        placement /= 10;
        iterator++;
    }
    
    return iterator;
}

//---------------------------------------------------------------------------------------------------------------------------------------
//                                                      Append Data
//---------------------------------------------------------------------------------------------------------------------------------------
bool appendData(int characteristic, int mantissa, int numZeros, char results[], int length, int longData) {
    int start_index = 0;

	int start_index = 0;

	int charNumDigits = getNumDigits(abs(characteristic));
	int manNumDigits = getNumDigits(abs(mantissa));

	if ((characteristic < 0) || (characteristic == 0 && mantissa < 0)) {
		// 45 in ASCII is negative sign
		results[0] = 45;
		start_index = 1;
	}

	int index = start_index;

	if (characteristic == 0) {
		index = start_index;
	}
	else {
		index = getDigitArray(characteristic, results, charNumDigits, start_index);
	}


	// Get the chracteristic and add to results array (note index in getDigitArray)


	// Add intermediary decimal in between characteristic and mantissa
	results[index] = '.';
	index++;

	// Add leading zeros to mantissa if necessary
	for (int zeros = 0; zeros < numZeros; zeros++) {
		results[index] = zeros;
		index++;
	}

	// Add mantissa to results array (note index in getDigitArray)
	int end_index = getDigitArray(mantissa, results, manNumDigits, index);

	int lastDigit = end_index;

	if (longData != 0) {
		for (int i = lastDigit; i < longData + lastDigit; i++) {
			results[i] = 54;
			end_index++;
		}
	}

	// End character results with NULL terminator
	results[end_index] = '\0';

	return true;
}

//---------------------------------------------------------------------------------------------------------------------------------------
//                                                        Subtract Helper
//---------------------------------------------------------------------------------------------------------------------------------------


bool subtractHelper(int denominator, int char1, int char2, int num1, int num2, int factor1, int factor2, char result[], int len, int longDigit) {
    
    
    int difference = computeDifference(char1, char2, denominator, num1*factor1, num2*factor2);
    
    //Find characteristic and mantissa of difference
    int characteristic = getCharacteristic(difference, denominator);
    int mantissa = getMantissa(difference, denominator);
    
    //Check if mantissa has leading zeros
    int numLeadingZeros = getMantissaZeros(characteristic, mantissa, num1, num2, difference);
    
    //Append data to char results
    bool wasAppended = appendData(characteristic, mantissa, numLeadingZeros, result, len, longDigit);
    
    //Note that transaction was a success
    return wasAppended;
    
}


int pow(int base, int exponent) {
    
    if(exponent == 0)
    {
        return 1;
    }
    else
    {
        return base * pow(base, exponent-1);
    }
}

int computeNoneBaseTen(int char1, int num1, int den1, int char2, int num2, int den2, int factor) {
    
    int man1 = num1 * (factor / den1);
    int man2 = num2 * (factor / den2);
    
    
    int difference = man1 - man2;
    
    return difference;
}


int getNoneBaseTenChar(int difference, int factor) {
    
    int characteristic = difference / factor;
    
    return characteristic;
    
}

int getNoneBaseTenMan(int difference, int factor) {
    
    int mantissa = (difference < 0) ? -1 * (difference * -1 % factor): difference % factor;
    
    return mantissa;
    
}


//---------------------------------------------------------------------------------------------------------------------------------------
//                                                          Subtraction
//---------------------------------------------------------------------------------------------------------------------------------------
bool subtract(int char1, int num1, int den1,  int char2, int num2, int den2, char result[], int len)
{
    /* Subtraction method uses common denominator technique and finds factors in which the
     mantissa numerator need to be multiplied by in order to get the right answer.    */
    
    bool answerSubtracted = false;
    
    if(!paramsAreGood(num1, num2, den1, den2)) {
        return false;
    }
    
    if(char1 == INT_MIN && char2 == INT_MAX) {
        return false;
    }
    
    if(den1 < 10 && den2 < 10) {
        
        int newLen = len;
        int longData = 0;
        if(len > 10) {
            newLen -= 8;
            longData = 8;
        }
        
        int factor = pow(10, newLen - 3);
        
        int difference = computeNoneBaseTen(char1, num1, den1, char2, num2, den2, factor);
        
        int characteristic = getNoneBaseTenChar(difference, factor);
        
        int mantissa = getNoneBaseTenMan(difference, factor);
        
        answerSubtracted = appendData(characteristic, mantissa, 0, result, len, longData);
        
        return answerSubtracted;
    }
    
    
    
    if(den1 == den2) {
        
        int factor1 = 1;
        int factor2 = 1;
        
        answerSubtracted = subtractHelper(den1, char1, char2, num1, num2, factor1, factor2, result, len, 0);
    }
    else if(den1 > den2) {
        
        int factor1 = 1;
        int factor2 = (den1 / den2);
        
        answerSubtracted = subtractHelper(den1, char1, char2, num1, num2, factor1, factor2, result, len, 0);
    }
    else if(den1 < den2)
    {
        
        int factor1 = (den2 / den1);
        int factor2 = 1;
        
        answerSubtracted = subtractHelper(den2, char1, char2, num1, num2, factor1, factor2, result, len, 0);
    }
    
    return answerSubtracted;
}
