//
// Created by Daniel Schechtman on 10/12/2017.
//
int findDecimal(char numString[], bool &neg);

bool mantissa(char numString[], int& numerator, int& denominator)
{
    bool retVal = true;
    bool space = false;

    char currentChar = '1';
    int iterator = 0;
    int decimalPlacement = 0;
    int mantissaSize = 0;
    numerator = 0;
    denominator = 1; // Assume value is a whole number, mantissa starts at 0/1
    bool neg = false;

    // findDecimal checks the characteristic as well as finding where decimal is. No point in
    // finding mantissa if the characteristic is invalid.
    iterator = findDecimal(numString, neg);
    decimalPlacement = iterator;
    if (iterator == -1)
    {
        retVal = false;
    }
    while (currentChar != '\0' && retVal != false)
    {
        currentChar = numString[iterator];
        // Only checks between '0' and '9' because can't have '.' after decimal point.
        // If null terminator is what's hit, good and break. Otherwise break, unless it's trailing space.
        // Can't know a space is trailing until \0 is hit though.
        if (numString[iterator] > '9' || numString[iterator] < '0' && space == false)
        {
            if (currentChar == ' ')
            {
                space = true;
            }
            else if (currentChar == '.' && iterator == 0)
            {
                //This is the '.456' case. Move decimal placement forward, '.' doesn't
                // count for mantissa.
                mantissaSize--;
                decimalPlacement++;
            }
            else if (currentChar == '\0')
            {
                break;
            }
            else
            {
                retVal = false;
                break;
            }
        }
            // Making sure trailing spaces are trailing. If we hit a nonspace that isn't \0, bad value
        else if (space == true)
        {
            if (currentChar != ' ')
            {
                if (currentChar == '\0')
                {
                    break;
                }

                else
                {
                    retVal = false;
                    break;
                }
            }
        }


        iterator++;
        mantissaSize++;

    }
    iterator--;
    currentChar = numString[iterator];

    // Check that there aren't any trailing 0s or spaces by moving backwards through char array.
    // Characteristic shouldn't be hit since '.' is not a 0 or a space. So if it's all 0s, '.' is still stop point
    while ((currentChar == '0' || currentChar == ' ') && retVal != false)
    {
        mantissaSize--;
        iterator--;
        currentChar = numString[iterator];
    }

    // Size of mantissa determines denominator. Denominator should be a power of 10 greater than numerator.
    // Denominator starts at size 1. Keep multiplying by 10 until end of counter is reached.
    int denominatorCounter = mantissaSize;
    while (denominatorCounter > 0 && retVal != false)
    {
        denominator *= 10;
        denominatorCounter--;
    }

    // Denominator counter is now a sort of numerator counter, so we start off a power of ten less
    // than the denominator. As we move through the mantissa, divide denominatorCounter by ten
    // Say the mantissa is 134/1000. Counter starts at 100 (1000/10 = 100). 100 * 1 = 100. Add to numerator. 100
    // Divide counter by 10, now it's 10. Move through mantissa, 3 * 10 = 30, add to numerator. 130.
    // Divide counter by 10, now is 1. Final value in mantissa. 4*1 = 4, add to numerator. 134.
    denominatorCounter = denominator / 10;
    int currentDigit = 0;
    if (retVal == true)
    {
        for (int i = decimalPlacement; i < (mantissaSize + decimalPlacement); i++)
        {
            currentDigit = numString[i] - 48;
            currentDigit *= denominatorCounter;
            numerator += currentDigit;
            denominatorCounter /= 10;
        }
    }

    if (neg == true)
    {
        numerator *= -1;
    }
    if (denominator == 1)
    {
        denominator *= 10; // Specs have lowest denominator be 10
    }


    return retVal;
}

int findDecimal(char numString[], bool &neg)
{
    // Assume that there are leading spaces and zeroes
    bool space = true;
    bool firstNonZero = false;
    int charVal = 0; // For cases of '         -0.12'
    int thisChar = 0;

    // For the case of ''1234456           '
    bool postSpace = false;

    int retVal = 0;
    char currentChar = numString[retVal];
    while (currentChar != '.')
    {

        if (firstNonZero == false && space == false)
        {
            thisChar = currentChar - 48;
            charVal += thisChar;
        }
        // First nonzero is only ever true for one iteration, if it is true.
        if (firstNonZero == true)
        {
            firstNonZero = false;
        }

        currentChar = numString[retVal];
        if (currentChar != ' ' && space == true)
        {
            space = false;
            firstNonZero = true;
        }
        // '/' is specifically enumerated because it is between '.' and '1', but it is not a good value.
        // Algorithm works for whole number cases because '\0' is not within range, and will return 0 for mantissa,
        // with whole mantissa being 0/1, which is 0.
        if ((currentChar > '9' || currentChar < '.' || currentChar == '/') && space == false)
        {
            if (firstNonZero == true && (currentChar == '+' || currentChar == '-'))
            {
                firstNonZero = false;
                if (currentChar == '-')
                {
                    neg = true;
                }
            }
            else if (currentChar == '\0')
            {
                break;
            }
            else if (currentChar == ' ' && postSpace == true)
            {
                // continue as expected
            }
            else if ((currentChar != ' ' && currentChar != '\0') && postSpace == true)
            {
                retVal = -1;
                break;
            }
            else if (currentChar == ' ' && postSpace == false)
            {
                postSpace = true;
            }
            else
            {
                retVal = -1;
                break;
            }

        }

        retVal++;
    }
    if (charVal > 0)
        neg = false;
    return retVal;
}
