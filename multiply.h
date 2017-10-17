#pragma once

//Cole Sitzberger
//Multiply

#include <iostream>

using namespace std;
//int multiplyDigit(char firstnum[], char secondnum[]);
bool multiply(unsigned int chara1, unsigned int mantiU1, unsigned int mantiO1, unsigned int chara2, unsigned int mantiU2, unsigned int mantiO2, char result[], int len);
int findZeros(int mantiO);
void print(char num[]);
bool checkArrayLength(int length, int numberone, int numbertwo);

bool multiply(unsigned int characteristic1, unsigned int  mantissaNumerator1, unsigned int mantissaD1, unsigned int characteristic2, unsigned int mantissaNumerator2, unsigned int mantissaD2, char result[], int len)
{
	if (checkArrayLength(len, characteristic1, characteristic2) == true)
	{
		//convert params int char[] so they can be operated on as one number in multiplyDigit

		//create an array to hold the first number being multiplied 
		char firstNumber[10000];
		//create an array to hold the product
		char ret[10000];
		//Intialize 
		for (int i = 0; i < 100; i++)
		{
			//Setting all chars in array to /0 so the end can be found 
			firstNumber[i] = '/';
		}
		//set the first slot in the array to the charactersic
		firstNumber[0] = characteristic1;
		//set the second slot to a decimal
		firstNumber[1] = '.';
		//find the number of zeros
		if (mantissaD1 > 1)
		{
			int loopcount = 2;
			for (int j = 0; j < findZeros(mantissaD1); j++)
			{

				firstNumber[j] = 0;
			}

		}
		firstNumber[99] = '/';
		//finds the point in the array to place the first part of the mantissa 
		int loopone = 2;
		while (true)
		{

			if (firstNumber[loopone] == '/')
			{
				firstNumber[loopone] = mantissaNumerator1;
				break;
			}
			loopone++;

		}
		// repeat the previous portion for the second number 
		char secondNumber[100];
		for (int i = 0; i < 100; i++)
		{
			secondNumber[i] = '/';
		}
		secondNumber[0] = characteristic2;
		secondNumber[1] = '.';

		if (mantissaNumerator2 > 1)
		{
			int loopcount = 2;
			for (int j = 0; j < findZeros(mantissaD2); j++)
			{

				secondNumber[2] = 0;
			}

		}
		secondNumber[99] = '/';
		int looptwo = 2;
		while (true)
		{

			if (secondNumber[looptwo] == '/')
			{
				secondNumber[looptwo+1] = mantissaNumerator2;
				break;
			}
			looptwo++;
		}



		

		int product_one = (characteristic1*mantissaNumerator1)+(mantissaNumerator1 * mantissaNumerator2); 
		int product_two = (characteristic1*characteristic2) + (mantissaNumerator1 * characteristic2);
		
		if (product_one < 0)
		{
			product_one = product_one*-1;
		}
		if (product_one < mantissaD1)
		{
			while (product_one > mantissaD1)
			{
				if (product_two < 0)
				{
					product_two = product_two - 1;
				}
				else
				{
					product_two = product_two + 1;
				}
			}

		}
		ret[0] = product_two;
		ret[1] = '.';
		ret[2] = product_one;
		ret[3] = '\0';



		//
		int loopcount = len;
		//round the answer off to the desired length
		
		ret[len] = ret[len] + 1;
		ret[len + 1] = '/0';

		bool retval = true;

		return retval;
	}
	else
	{
		return false;
	}
}

//determines the number of zeros from the mantissa 
int findZeros(int mantiO)
{


	int loopcount = mantiO % 10;

	return loopcount;

}



void print(char num[])
{
	int loopcount = 0;
	while (true)
	{
		if (num[loopcount != '/'])
		{
			cout << num[loopcount];
			loopcount++;
		}
		else
		{
			false;
		}

	}
	cout << endl;
}


bool checkArrayLength(int length, int numberone, int numbertwo)
{
	bool retval = true;
	for (int i = 0; i < numberone; i++)
	{
		if (i > length)
		{
			retval = false;
			return retval;
			break;
		}
	}
	for (int j = 0; j < numbertwo; j++)
	{
		if (j > length)
		{
			retval = false;
			return retval;
			break;
		}
	}
	return retval;
}

