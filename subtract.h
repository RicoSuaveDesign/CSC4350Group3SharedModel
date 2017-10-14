//
//  subtract.h
//  subtract_v1
//
//  Created by Tom Shannon on 9/26/17.
//  Copyright © 2017 tom. All rights reserved.
//

#ifndef subtract_h
#define subtract_h

bool paramsAreGood(int num1, int num2, int den1, int den2);

int computeDifference(int char1, int char2, int denominator, int num1, int num2);

int getCharacteristic(int difference, int denominator);

int getMantissa(int difference, int denominator);

int getNumDigits(int number);

int getMantissaZeros(int characteristic, int mantissa, int num1, int num2, int difference);

int getDigitArray(int number, char results[], int numDigits, int iterator);

bool appendData(int characteristic, int mantissa, int numZeros, char results[], int length, int longData);

void printDifference(int num1, int num2, int characteristic, int mantissa, int numLeadingZeros);

bool subtractHelper(int denominator, int char1, int char2, int num1, int num2, int factor1, int factor2, char result[], int len, int longDigit);

int pow(int base, int exponent);

int getNoneBaseTen(int char1, int num1, int den1, int char2, int num2, int den2, int factor);

int getNoneBaseTenMan(int difference, int factor);


bool subtract(int char1, int num1, int den1,  int char2, int num2, int den2, char result[], int len);

#endif /* subtract_h */
