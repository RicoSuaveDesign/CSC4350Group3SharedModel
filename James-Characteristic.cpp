#include <iostream>

using namespace std;

bool characteristic(char number[], int& c);
void testCharacteristic(char number[], int& c);

int main()
{

	char test1[] = "123.456";
	int c1 = 0;
	testCharacteristic(test1, c1);


	char test2[] = "-4.06";
	int c2 = 0;
	testCharacteristic(test2, c2);

	char test3[] = "-23 .3";
	int c3 = 0;
	testCharacteristic(test3, c3);

	
}

bool characteristic(char numString[], int& c)
{
	char *ptr;
	bool firstChar = true;
	ptr = numString;
	// Iterate through number looking for '.' or '\n'. If '.', then preceding characters are characteristic
	// If '\n', then whole number must be characteristic

	while(*ptr != '.' && *ptr != '\0')
	{
		// If not the first char and char is '-', '+', or ' ', then invalid
		if(firstChar == false && (*ptr == '-' || *ptr == '+' || *ptr == ' '))
		{
			//Invalid string
			c = -1;
			return false;
		}

		ptr++;
		firstChar = false;
	}

	// atoi seems like cheating
	c = atoi(numString);
	return true;
}

void testCharacteristic(char numbers[], int& c)
{
	bool retVal = characteristic(numbers, c);

	printf("retVal: %i \n c: %i \n", retVal, c);


}