#include <iostream>

using namespace std;

bool characteristic(char number[], int& c);


bool characteristic(char numString[], int& c)
{
	char *ptr;
	bool seenNumber = false;
	ptr = numString;
	// Iterate through number looking for '.' or '\0'. If '.', then preceding characters are characteristic
	// If '\n', then whole number must be characteristic

	while(*ptr != '.' && *ptr != '\0')
	{
		// If not the first char and char is '-', '+', or ' ', then invalid
		if( seenNumber == true && (*ptr == '-' || *ptr == '+'))
		{
			//Invalid string
			c = -1;
			return false;
		}

		if( seenNumber == false && (*ptr != ' ' && *ptr != '+' && *ptr != '-'))
		{
			seenNumber = true;
		}
		ptr++;
		
	}

	// atoi seems like cheating
	c = atoi(numString);
	return true;
}