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

void addCharacterToString(char *str_to_add_char, char char_to_add);

// this function figures out what power of 10 to divide by a number
// to get the first digit of that number. for example if I passed in 1234,
// the function would return 1000, which if I used in an integer devision
// would give me 1. int &times_looped will be used to allow me to figure
// out how many digits come after the first digit (vary useful if I throw in 10^(whatever)).
int findPower(int pow_of_num, int &times_looped);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

// HELPER FUNCTIONS FOR add
void makeDenominatorsEqual(int &d1, int &d2, int &n1, int &n2, int &len);

void putOutputInArray(int n1, int n2, int &outputIndex, int len, char result[]);

void addCharacteristic(int &i, int characteristic_sum, const char *sum_of_characteristic, char result[]);

char *longDivision(int &num_before_decimal, int numerator, int denominator, int len);

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

void addCharacterToString(char *str_to_add_char, char char_to_add){
    int len = strLen(str_to_add_char)+1;
    char *new_c_string = makeString(len-1);
    for(int i = 0; i <= len-1; i++) {
        new_c_string[i] = str_to_add_char[i];
    }

    delete []str_to_add_char;

    str_to_add_char = makeString(len);
    for(int i = 0; i < len; i++){
        if(i+1 == len){
            str_to_add_char[i] = char_to_add;
            str_to_add_char[i+1] = '\0';
            continue;
        }
        str_to_add_char[i] = new_c_string[i];
    }

    delete []new_c_string;
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

void makeDenominatorsEqual(int &d1, int &d2, int &n1, int &n2, int &len){
    int common_denominator = d1 * d2;
    int numerator_of_d1 = n1 * d2;
    int numerator_of_d2 = n2 * d1;
    d1 = common_denominator;
    d2 = common_denominator;
    n1 = numerator_of_d1;
    n2 = numerator_of_d2;
    findPower(d1, len);
}

char *longDivision(int &num_before_decimal, int numerator, int denominator, int len){
    char *output = makeString(len);
    output[0] = '+';
    for(int i = 1; i <= len; i++){
        bool num_bigger_then_denom = numerator > denominator;
        int remainder = 0;
        int how_many_times_goes_into = 0;
        int multiply = 0;
        bool add_zero = false;
        while(numerator < denominator){
            if(numerator == 0){
                numerator = 1;
            }
            numerator *= 10;
            if(add_zero){
                output[i] = '0';
                i++;
            }
            add_zero = true;
        }
        while (multiply + denominator < numerator){
            multiply += denominator;
            how_many_times_goes_into++;
            if(num_bigger_then_denom){
                num_before_decimal++;
            }
        }

        if(how_many_times_goes_into == 0){
            char num[] = {'+', output[i-1], '\0'};
            int last_digit = strToInt(num);
            char *new_num = intToStr(last_digit+1);
            output[i-1] = new_num[1];
            delete []new_num;
            break;
        }
        else if (!num_bigger_then_denom) {
            char *char_num = intToStr(how_many_times_goes_into);
            output[i] = char_num[1];
            delete[]char_num;
        }
        remainder = numerator - multiply;
        numerator = remainder;
    }
    return output;
}

void putOutputInArray(int n1, int n2, int &outputIndex, int len, char result[]){
    char *sum_of_numerators = intToStr(n1+n2);

    // these two variables below will be used to figure out
    // how many more iterations the for loop below must perform
    int start_point = outputIndex;

    // i added 1 to the length I got because I saw that a few characters
    // weren't being added into the results[] array
    int place_to_add_in_numerators = strLen(sum_of_numerators)+1;

    // I added 1 here in response to what I did above, otherwise I found the same bug
    // as above
    len++;

    for(; outputIndex < len+start_point; outputIndex++){

        // determines at which index I should start adding characters from sum_of_numerators to results
        int start_adding_dec = (len-place_to_add_in_numerators)-(outputIndex-start_point);

        if(start_adding_dec < 0){
            start_adding_dec *= -1;
            result[outputIndex] = sum_of_numerators[start_adding_dec];
        }
        else{
            result[outputIndex] = '0';
        }
    }
    delete[] sum_of_numerators;
}

void addCharacteristic(int &i, int characteristic_sum, const char *sum_of_characteristic, char result[]){
    for(; i < characteristic_sum; i++){
        result[i] = sum_of_characteristic[i];
    }
    result[i] = '.';
}

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len){


    // determines if the calculation can be done or not
    bool can_calc = true;
    if(d1 == 0 || d2 == 0){
        can_calc = false;
    }

    if(can_calc){

        n1 = n1 * d2;
        n2 = n2 * d1;
        int characteristic_found_from_mantissa = 0;
        char *mantissa = longDivision(characteristic_found_from_mantissa, n1+n2, d1*d2, len);

        char *characteristic = intToStr(c1+c2+characteristic_found_from_mantissa);
        int c_len = strLen(characteristic);
        int m_len = strLen(mantissa);
        int i = 0;
        for(;i < c_len; i++){
            result[i] = characteristic[i];
        }
        result[i] = '.';
        i++;
        int offset = 0;
        for(;i < len; i++){
            if(i >= m_len){
                break;
            }
            else if(mantissa[i-c_len] == ' ' || mantissa[i-c_len] == '-' || mantissa[i-c_len] == '+'){
                offset++;
                continue;
            }
            result[i-offset] = mantissa[i-c_len];
        }
        delete []mantissa;
        delete []characteristic;
        result[i] = '\0';
    }
    return can_calc;
}

int main() {
    char resulte[20];
    if(add(1, 1, 3, -2, 50, 128, resulte, 20)){
        print(resulte);
    }
    return 0;
}