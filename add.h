//
// Created by Daniel Schechtman on 10/13/2017.
//

#include <iostream>

using namespace std;

// FUNCTIONS FOR STRINGS BELOW

// returns a pointer to a character array
// since idk how to return an array from a function without
// a pointer
char *makeString(int len);

// gets the length of the string
int strLen(const char *str);

// takes an array and prints each character in it to the screen
void print(const char str[]);


// converts an integer to a c_string and returns the c_string
char *intToStr(int num_to_convert);

int strToInt(char *str_to_convert);

// this function figures out what power of 10 to divide by a number
// to get the first digit of that number. for example if I passed in 1234,
// the function would return 1000, which if I used in an integer devision
// would give me 1. int &times_looped will be used to allow me to figure
// out how many digits come after the first digit (vary useful if I throw in 10^(whatever)).
int findPower(int pow_of_num, int &times_looped);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

// HELPER FUNCTIONS FOR add

char *longDivision(int &num_before_decimal, int numerator, int denominator, int len);

void findNumAfterDecimal(int &numerator, int &denominator, bool &add_zero, char *output, int &i);

void howManyTimeDenominatorGoesIntoNumerator(int &multiply, int &denominator, int &numerator, int &how_many_times_goes_into, bool &num_bigger_then_denom, int &num_before_decimal);

char *createStringRepOfFloat(char *characteristic, char *mantissa);


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

// HELPER FUNCTIONS FOR add
char* makeString(int len){
    // I add 2 to len, so the c_string will have room for a unary sign ('+' or '-')
    // and a terminator character '\0'
    len += 2;


    char *c_string_with_unary = new char[len];

    // initalizes the c_string with blank spots so I can decide what
    // to fill the c_string in with later
    int null_index = 0;
    for(;null_index < len-1; null_index++){
        c_string_with_unary[null_index] = ' ';
    }
    c_string_with_unary[null_index] = '\0';

    return c_string_with_unary;
}

int strLen(const char *str){
    int length = 0;
    while(str[length] != '\0'){
        length++;
    }
    return length;
}

void print(const char str[]){
    int length = strLen(str);
    for(int character_index = 0; character_index < length; character_index++){
        cout << str[character_index];
    }
    cout << '\n';
}

int strToInt(char *str_to_convert){
    int length = strLen(str_to_convert)-1;
    int loop_num = length+1;
    int sum = 0;
    int pow_of = 1;

    for(int i = 0; i < length-1; i++){
        pow_of *= 10;
    }

    for(int i = 0; i < loop_num; i++){
        if(str_to_convert[i] == '+'){
            continue;
        }
        sum += (int(str_to_convert[i]) - '0')*pow_of;
        pow_of /= 10;
    }
    return sum;
}

char *intToStr(int num_to_convert){
    // this will determine how many digits is in num_to_covert
    // which will allow me to figure out how many times he for loop
    // should run
    int len = 1;

    char sign = '+';

    if(num_to_convert < 0){
        sign = '-';
        // I have to convert it to a positive number
        // because find_power(int, int) doesn't work
        // if the number passed in is negitive
        num_to_convert *= -1;
    }


    int pow_of_10_for_digit = findPower(num_to_convert, len);
    char *c_string_converted_from_int = makeString(len);
    c_string_converted_from_int[0] = sign;

    // gets where I should start adding the digits of the number
    // to the string
    int place_in_string = 1;

    for(int i = 0; i < len; i++){
        // gets the digit associated with the power of 10
        // going back to the example of 1234
        // digit will first hold 1, then 2, and so on until
        // the last digit is reached
        int digit = num_to_convert/pow_of_10_for_digit;

        // converts the int to a character
        c_string_converted_from_int[place_in_string] = char('0'+digit);

        // decreases num_to_covert by the current power of 10
        // so 1234 becomes 1234-1000, then 234-100, and so on until the end of the loop
        num_to_convert -= (num_to_convert/pow_of_10_for_digit)*pow_of_10_for_digit;

        // this will get the next digit in num_to_convert
        pow_of_10_for_digit /= 10;

        // gets the next place in the c_string to store the character
        place_in_string++;
    }
    return c_string_converted_from_int;
}

// FUNCTIONS FOR STRINGS ABOVE


int findPower(int pow_of_num, int &times_looped) {
    int base = 1;
    while(true){
        if(pow_of_num/base >= 0 && pow_of_num/base <= 9){
            break;
        }
        times_looped++;
        base *= 10;
    }
    return base;
}

// gets the mantissa
void findNumAfterDecimal(int &numerator, int &denominator, bool &add_zero, char *output, int &i){
    while(numerator < denominator){
        if(numerator == 0){
            break;
        }
        numerator *= 10;

        // will add significant zeros
        if(add_zero){
            output[i] = '0';
            i++;
        }
        add_zero = true;
    }
}

void howManyTimeDenominatorGoesIntoNumerator(int &multiply, int &denominator, int &numerator, int &how_many_times_goes_into, bool &num_bigger_then_denom, int &num_before_decimal){
    while (multiply < numerator){
        multiply = denominator*(how_many_times_goes_into+1);
        how_many_times_goes_into++;
        if(num_bigger_then_denom){

            // this will be turned into the characteristic
            num_before_decimal++;
        }
    }
}

char *longDivision(int &num_before_decimal, int numerator, int denominator, int len){
    num_before_decimal = 0;
    char *output = makeString(len);

    bool num_bigger_then_denom;
    int how_many_times_goes_into;
    bool add_zero;

    output[0] = '+';

    if(numerator < 0 ^ denominator < 0){
        output[0] = '-';
        if (numerator < 0){
            numerator = -numerator;
        }
        if(denominator < 0){
            denominator = -denominator;
        }
    }

    int i = 1;
    for(;i <= len; i++){
        num_bigger_then_denom = numerator > denominator;
        add_zero = false;

        findNumAfterDecimal(numerator, denominator, add_zero, output, i);

        how_many_times_goes_into = numerator/denominator;

        // checks to see if division is don

        // makes sure we aren't adding the characteristic
        // to the mantissa
        if (!num_bigger_then_denom) {
            output[i] = char('0' + how_many_times_goes_into);
        }
        else{
            i--;
        }

        if(how_many_times_goes_into == 0){
            break;
        }

        numerator -= (denominator*how_many_times_goes_into);
        if(num_bigger_then_denom){
            num_before_decimal = how_many_times_goes_into;
        }
    }
    return output;
}

char *createStringRepOfFloat(char *characteristic, char *mantissa){
    int c_len = strLen(characteristic);
    int m_len = strLen(mantissa);

    int new_num_len = c_len + m_len;

    char *new_num = makeString(new_num_len);

    int offset = 0;
    for(int i = 0; i < c_len; i++){
        new_num[i] = characteristic[i];
        offset = i;
    }

    offset++;
    new_num[offset] = '.';

    for(int i = 1; i < m_len; i++){
        new_num[i+offset] = mantissa[i];
    }

    return new_num;
}

bool makePositive(int &c, int &n, int &d){
    bool retVal = false;
    if (c < 0){
        c = -c;
        retVal = true;
    }
    if (n < 0){
        n = -n;
        retVal = true;
    }
    if (d < 0){
        d = -d;
        retVal = true;
    }
    return retVal;
}

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len){


    // determines if the calculation can be done or not
    bool can_calc = true;
    if(d1 == 0 || d2 == 0){
        can_calc = false;
    }

    if(can_calc){
        char sign1 = '+';
        char sign2 = '+';

        if(makePositive(c1, n1, d1)){
            sign1 = '-';
        }
        if(makePositive(c2, n2, d2)){
            sign2 = '-';
        }

        int new_n1 = ((c1*d1)+n1);
        int new_n2 = ((c2*d2)+n2);

        int common_d = d1*d2;

        new_n1 *= d2;
        new_n2 *= d1;

        if(sign1 == '-'){
            new_n1 = -new_n1;
        }
        if(sign2 == '-'){
            new_n2 = -new_n2;
        }

        int new_n = new_n1 + new_n2;
        int new_c;
        char *matissa = longDivision(new_c, new_n, common_d, len);
        char *characteristic = intToStr(new_c);
        char *output = createStringRepOfFloat(characteristic, matissa);

        int offset = 0;

        if(matissa[0] == '-' && output[0] == '-') {
            output[0] = '+';
            offset = 1;
        }
        else{
            output[0] = matissa[0];
            if(matissa[0] == '+'){
                offset = 1;
            }
        }

        for(int i = 0; i < len; i++){
            if(i+1 == len){
                result[i] = '\0';
            }
            else{
                result[i] = output[i+offset];
            }
        }

        delete []output;
        delete []matissa;
        delete []characteristic;
    }
    return can_calc;
}

