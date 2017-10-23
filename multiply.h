#pragma once

//Cole Sitzberger
//Multiply
using namespace std;
//int multiplyDigit(char firstnum[], char secondnum[]);
char *intToCStr(int num_to_convert);
char *createStringRepOfFloatNum(char *characteristic, char *mantissa);

char* makeCString(int len) {
	// I add 2 to len, so the c_string will have room for a unary sign ('+' or '-')
	// and a terminator character '\0'
	len += 2;


	char *c_string_with_unary = new char[len];

	// initalizes the c_string with blank spots so I can decide what
	// to fill the c_string in with later
	int null_index = 0;
	for (; null_index < len - 1; null_index++) {
		c_string_with_unary[null_index] = ' ';
	}
	c_string_with_unary[null_index] = '\0';

	return c_string_with_unary;
}

int strLength(const char *str) {
	int length = 0;
	while (str[length] != '\0') {
		length++;
	}
	return length;
}

bool makeNumPositive(int &c, int &n, int &d) {
	bool retVal = false;
	if (c < 0) {
		c = -c;
		retVal = true;
	}
	if (n < 0) {
		n = -n;
		retVal = true;
	}
	if (d < 0) {
		d = -d;
		retVal = true;
	}
	return retVal;
}


int makeNewNumeratorForMultiplycation(int c, int n, int d) {
	return ((c*d) + n);
}

void findNumAfterDecimalPlace(int &numerator, int &denominator, bool &add_zero, char *output, int &i) {
	while (numerator < denominator) {
		if (numerator == 0) {
			break;
		}
		numerator *= 10;

		// will add significant zeros
		if (add_zero) {
			output[i] = '0';
			i++;
		}
		add_zero = true;
	}
}

char *longDivisionOfFraction(int num_before_decimal, int numerator, int denominator, int len) {
	num_before_decimal = 0;
	char *output = makeCString(len);

	bool num_bigger_then_denom;
	int how_many_times_goes_into;
	bool add_zero;

	output[0] = '+';

	if (numerator < 0 ^ denominator < 0) {
		output[0] = '-';
		if (numerator < 0) {
			numerator = -numerator;
		}
		if (denominator < 0) {
			denominator = -denominator;
		}
	}

	int i = 1;
	for (; i <= len; i++) {
		num_bigger_then_denom = numerator > denominator;
		add_zero = false;

		findNumAfterDecimalPlace(numerator, denominator, add_zero, output, i);

		how_many_times_goes_into = numerator / denominator;

		// checks to see if division is don

		// makes sure we aren't adding the characteristic
		// to the mantissa
		if (!num_bigger_then_denom) {
			output[i] = char('0' + how_many_times_goes_into);
		}
		else {
			i--;
		}

		if (how_many_times_goes_into == 0) {
			break;
		}

		numerator -= (denominator*how_many_times_goes_into);
		if (num_bigger_then_denom) {
			num_before_decimal = how_many_times_goes_into;
		}
	}
	char *new_ch_string = intToCStr(num_before_decimal);
	char *float_string = createStringRepOfFloatNum(new_ch_string, output);
	delete[]output;
	delete[]new_ch_string;
	return float_string;
}

int findPowerOfTenForNum(int pow_of_num, int &times_looped) {
	int base = 1;
	while (true) {
		if (pow_of_num / base >= 0 && pow_of_num / base <= 9) {
			break;
		}
		times_looped++;
		base *= 10;
	}
	return base;
}

char *intToCStr(int num_to_convert) {
	// this will determine how many digits is in num_to_covert
	// which will allow me to figure out how many times he for loop
	// should run
	int len = 1;

	char sign = '+';

	if (num_to_convert < 0) {
		sign = '-';
		// I have to convert it to a positive number
		// because find_power(int, int) doesn't work
		// if the number passed in is negitive
		num_to_convert *= -1;
	}


	int pow_of_10_for_digit = findPowerOfTenForNum(num_to_convert, len);
	char *c_string_converted_from_int = makeCString(len);
	c_string_converted_from_int[0] = sign;

	// gets where I should start adding the digits of the number
	// to the string
	int place_in_string = 1;

	for (int i = 0; i < len; i++) {
		// gets the digit associated with the power of 10
		// going back to the example of 1234
		// digit will first hold 1, then 2, and so on until
		// the last digit is reached
		int digit = num_to_convert / pow_of_10_for_digit;

		// converts the int to a character
		c_string_converted_from_int[place_in_string] = char('0' + digit);

		// decreases num_to_covert by the current power of 10
		// so 1234 becomes 1234-1000, then 234-100, and so on until the end of the loop
		num_to_convert -= (num_to_convert / pow_of_10_for_digit)*pow_of_10_for_digit;

		// this will get the next digit in num_to_convert
		pow_of_10_for_digit /= 10;

		// gets the next place in the c_string to store the character
		place_in_string++;
	}
	return c_string_converted_from_int;
}

char *createStringRepOfFloatNum(char *characteristic, char *mantissa) {
	int c_len = strLength(characteristic);
	int m_len = strLength(mantissa);

	int new_num_len = c_len + m_len;

	char *new_num = makeCString(new_num_len);

	int offset = 0;
	for (int i = 0; i < c_len; i++) {
		new_num[i] = characteristic[i];
		offset = i;
	}

	offset++;
	new_num[offset] = '.';

	for (int i = 1; i < m_len; i++) {
		new_num[i + offset] = mantissa[i];
	}

	return new_num;
}

int strLenAndDeleteCString(const char *num_str) {
	int retval = strLength(num_str) - 1;
	delete[]num_str;
	return retval;
}

bool testIfNumCanFitInOutputArray(int c, int n, int d, int len) {
	bool retVal = true;

	int c_len = strLenAndDeleteCString(intToCStr(c));
	int n_len = strLenAndDeleteCString(intToCStr(n));
	int d_len = strLenAndDeleteCString(intToCStr(d));
	if (c_len > len || n_len > len || d_len > len) {
		retVal = false;
	}
	return retVal;
}

bool multiply(int characteristic1, int  mantissaNumerator1, int mantissaD1, int characteristic2, int mantissaNumerator2, int mantissaD2, char result[], int len)
{

	bool sign1 = makeNumPositive(characteristic1, mantissaNumerator1, mantissaD1);
	bool sign2 = makeNumPositive(characteristic2, mantissaNumerator2, mantissaD2);


	int new_numerator = makeNewNumeratorForMultiplycation(characteristic1, mantissaNumerator1, mantissaD1) * makeNewNumeratorForMultiplycation(characteristic2, mantissaNumerator2, mantissaD2);
	int new_denominator = mantissaD1 * mantissaD2;

	if (!testIfNumCanFitInOutputArray(characteristic2, new_numerator, new_denominator, len)
		|| !testIfNumCanFitInOutputArray(characteristic1, new_numerator, new_denominator, len)) {
		return false;
	}

	char *output = longDivisionOfFraction(0, new_numerator, new_denominator, len);


	int offset = 0;
	if (sign1 && sign2) {
		output[0] = '+';
		offset = 1;
	}
	else if (sign1 != sign2) {
		if (output[0] == '+') {
			output[0] = '-';
		}
		else if (output[0] == '-') {
			output[0] = '+';
			offset = 1;
		}
	}
	else if (!sign1 && !sign2) {
		offset = 1;
	}


	for (int i = 0; i < len; i++) {
		if (i + 1 == len) {
			result[i] = '\0';
		}
		else {
			result[i] = output[i + offset];
		}
	}

	delete[]output;

	return true;

}

//determines the number of zeros from the mantissa 
