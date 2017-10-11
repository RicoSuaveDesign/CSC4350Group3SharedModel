#include <iostream>
#include "James-Characteristic.cpp"

using namespace std;

void testCharacteristicAndMantissa();
void shouldConvert(char number[], int expectedCharacteristic);
void shouldNotConvert(char number[]);

void testMath();
void testAdd();
void testSubtract();
void testMultiply();
void testDivide();

int main()
{
	//characteristic and mantissa test
	testCharacteristicAndMantissa();
	
	//math function tests
	//testMath();

	return 0;
}
//--
void testCharacteristicAndMantissa()
{
	shouldConvert("123.456", 123);
	shouldConvert("    123.456", 123);
	shouldConvert("123.456    ", 123);
	shouldConvert("    123.456    ", 123);

	shouldConvert("+123.456", 123);
	shouldConvert("   +123.456", 123);
	shouldConvert("+123.456   ", 123);
	shouldConvert("   +123.456   ", 123);

	shouldConvert("-123.456", -123);
	shouldConvert("   -123.456", -123);
	shouldConvert("-123.456   ", -123);
	shouldConvert("    -123.456   ", -123);

	shouldConvert("0.456", 0);
	shouldConvert("   0.456", 0); 
	shouldConvert("0.456   ", 0);
	shouldConvert("   0.456   ", 0);

	shouldConvert("-0.456", 0);
	shouldConvert("   -0.456", 0);
	shouldConvert("-0.456   ", 0);
	shouldConvert("   -0.456   ", 0);

	shouldConvert(".456", 0);
	shouldConvert("    .456", 0);
	shouldConvert(".456   ", 0);
	shouldConvert("   .456   ", 0);

	shouldConvert("-.456", 0);
	shouldConvert("    -.456", 0);
	shouldConvert("-.456   ", 0);
	shouldConvert("   -.456   ", 0);

	shouldConvert("123456", 123456);
	shouldConvert("   123456", 123456);
	shouldConvert("123456   ", 123456);
	shouldConvert("   123456   ", 123456);

	shouldConvert("-123456", -123456);
	shouldConvert("   -123456", -123456);
	shouldConvert("-123456   ", -123456);
	shouldConvert("   -123456   ", -123456);

	shouldConvert("000123.456", 123);
	shouldConvert("123.45600000", 123);
	shouldConvert("00000123.45600000", 123);

	shouldConvert("-000123.456", -123);
	shouldConvert("-123.45600000", -123);
	shouldConvert("-00000123.45600000", -123);

	shouldConvert("123.00000456", 123);
	shouldConvert("-123.00000456", -123);
}
//--
void shouldConvert(char number[], int expectedCharacteristic)
{
	int c, n, d;

	//if the conversion from C string to integers can take place
	if (characteristic(number, c) )
	{
		if (c == expectedCharacteristic)
		{
			//test passes, do not print anything on a successful test
		}
		else
		{
			cout << "Test failed: '" << number << "' "
				<< "was parsed but did not produce the expected results" << endl;

			if (expectedCharacteristic != c)
			{
				cout << "expected characteristic: " << expectedCharacteristic << " "
					<< "actual characteristic: " << c << endl;
			}

			
		}
	}
	else
	{
		cout << "Test failed: '" << number << "' "
			<< "was NOT parsed when it should have been." << endl;
	}
}

//--
void shouldNotConvert(char number[])
{
	int c, n, d;

	//if the conversion from C string to integers can take place
	if (characteristic(number, c))
	{
		cout << "Test failed: '" << number << "' "
			<< "was parsed when it should NOT have been." << endl;
	}
}
//--
