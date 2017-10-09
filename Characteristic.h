#pragma once
#include <iostream>
using namespace std;
//using a pointer here so we can dynamically set the size of the array on the heap.
void removeUnwantedChars(char* numberString[]);
bool characteristic(char numString[], int& c);
int getArraySize(char array[]);
int numWantedChars(char array[]);
bool isCharInList(char lookingFor, char lookingThrough[]);
bool hasSign(char numberString[]);

static char wantedList[] = {'+', '-','0', '1', '2', '3', '4', '5', '6', '7', '8', "9" };


bool characteristic(char numString[], int& c)
{

	//return value 
	bool retval = true;

	//stores information for later array rebuild.
	bool isNegative = false;
	if (hasSign(numString))
	{
		bool isNegative = true;
	}
	//will be used to save the new arrays size.
	removeUnwantedChars(&numString);
	cout << getArraySize(numString) << endl;
	return retval;
}

void removeUnwantedChars(char* numberString[])
{

	//gets the number of characters that we want.
	int newSize = numWantedChars(*numberString);
	int iterator = getArraySize(*numberString);
	int numCharsInNewArray = 0;
	char* newArray = new char[newSize];
	for (int i = 0; i < iterator; i++)
	{
		//we do not need to see anything past the decimal
		if (*numberString[i] == '.')
		{
			break;
		}
		if (isCharInList(*numberString[i], wantedList))
		{
			newArray[numCharsInNewArray] = *numberString[i];
		}
	}
	//if i set "newArray = 0" then it would set the array that i want to a null pointer. i think.
	*numberString = newArray;
}

bool hasSign(char numberString[])
{
	bool retval = false;

	int iterator = getArraySize(numberString);
	for (int i = 0; i < iterator; i++)
	{
		if (numberString[i] == '-')
		{
			retval = true;
			break;
		}
		//if we have not found a negative sign, but we have found something other than a space,
		//that means their cant be a negaive sign
		if (numberString[i] != ' ')
		{
			//break out of the function to save time. as there is no use checking.
			break;
		}
	}
	return retval;

}

int getArraySize(char array[])
{
	int retval = 0;
	while (array[retval] != NULL)
	{
		retval++;
	}
	return retval;
}

int numWantedChars(char array[])
{
	int retval = 0;
	int iterator = getArraySize(array);
	for (int i = 0; i < iterator; i++)
	{
		if (array[i] == '.')
		{
			break;
		}
		if (isCharInList(array[i], wantedList))
		{
			retval++;
		}
	}
	return retval;
}

bool isCharInList(char lookingFor, char lookingThrough[])
{
	//start out as false, if we find it, set it to true
	bool retval = false;

	int iterator = getArraySize(lookingThrough);
	for (int i = 0; i < iterator; i++)
	{
		if (lookingFor == lookingThrough[i])
		{
			retval = true;
			break;
		}
	}
	return retval;
}