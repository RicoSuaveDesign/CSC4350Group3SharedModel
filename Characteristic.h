#pragma once
#include <iostream>
using namespace std;
//using a pointer here so we can dynamically set the size of the array on the heap.
bool characteristic(char numString[], int& c);
int getArraySize(char array[]);
bool hasUnwantedChars(char array[]);
bool isCharInList(char lookingFor, char lookingThrough[]);

static char wantedList[] = " .+-0987654321";//{'+', '-','0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '/0' };


bool characteristic(char numString[], int& c)
{
	
	//return value 
	bool retval = true;

	//stores information for later array rebuild.
	
	//will be used to save the new arrays size.
	if(hasUnwantedChars(numString))
	{
		retval = false;
	}
	else
	{
		c = atoi(numString);
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
//this function steps through the array checking to see if the character is in the wanted list, if it is not, it breaks the loop
//while returning a true, which means we found something bad. will also return true if: we find a '.' before any other characters.
//or if we find a +,-, or ' ' (space) while inside the number.
bool hasUnwantedChars(char array[])
{
	bool retval = false;
	bool hasSeenCharacter = false;
	int iterator = getArraySize(array);
	for (int i = 0; i < iterator; i++)
	{
		if (array[i] == '.')
		{
			
			break;
		}
		if(!isCharInList(array[i], wantedList))
		{
			retval = true;
		}
		else if (array[i] == '+' || array[i] == '-')
		{
			if (hasSeenCharacter == true)
			{
				retval = true;
				break;
			}
		}
		if (hasSeenCharacter == false)
		{
			if (array[i] != ' ' && array[i] != '-'&& array[i] != '+')
			{
				hasSeenCharacter = true;
			}
			
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