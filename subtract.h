//
//  subtract.h
//  subtract_v1
//
//  Created by Tom Shannon on 9/26/17.
//  Copyright © 2017 tom. All rights reserved.
//

#ifndef subtract_h
#define subtract_h

int computeDifference(int char1, int char2, int denominator, int num1, int num2);

int getCharacteristic(int difference, int denominator);

int getMantissa(int difference, int denominator);

int getNumDigits(int number);

int getMantissaZeros(int characteristic, int mantissa, int num1, int num2, int difference);

int getDigitArray(int number, char results[], int numDigits, int iterator);

bool appendData(int characteristic, int mantissa, int numZeros, char results[], int length);

bool subtract_helper(int denominator, int char1, int char2, int num1, int num2, int factor1, int factor2, char result[], int len);

bool subtract(int char1, int num1, int den1,  int char2, int num2, int den2, char result[], int len);

#endif /* subtract_h */
