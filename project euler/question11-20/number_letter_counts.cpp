/*
Number letter counts
Problem 17

If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.

*/
#include <iostream>
enum NumberAlphabet
{
    ONE = 3,
    TWO = 3,
    THREE = 5,
    FOUR = 4,
    FIVE = 4,
    SIX = 6,
    SEVEN = 5,
    EIGHT = 5,
    NINE = 4,
    ZERO = 4,
    TEN = 3,
    ELEVEN = 6,
    TWELVE = 6,
    THIRTEEN = 8,
    FOURTEEN = 8,
    FIFTEEN = 7,
    SIXTEEN = 7,
    SVENTEEN = 8,
    EIGHTEEN = 8,
    NINETEEN = 8,
    TWENTY = 6,
    THIRTY = 6,
    FOURTY = 6,
    FIFTY = 5,
    SIXTY = 5,
    SVENTY = 6,
    EIGHTY = 6,
    NINETY = 6,
    HUNDRED = 7

};
int count_alpha(int num)
{
    if (num > 0 && num < 10)
    {
        switch (num)
        {
        case 0:
            return NumberAlphabet::ZERO;
        case 1:
            return NumberAlphabet::ONE;
        case 2:
            return NumberAlphabet::TWO;
        case 3:
            return NumberAlphabet::THREE;
        case 4:
            return NumberAlphabet::FOUR;
        case 5:
            return NumberAlphabet::FIVE;
        case 6:
            return NumberAlphabet::SIX;
        case 7:
            return NumberAlphabet::SEVEN;
        case 8:
            return NumberAlphabet::EIGHT;
        case 9:
            return NumberAlphabet::NINE;
        }
    }
    if (num >= 10 && num < 20)
    {
        switch (num)
        {
        case 10:
            return NumberAlphabet::TEN;
        case 11:
            return NumberAlphabet::ELEVEN;
        case 12:
            return NumberAlphabet::TWELVE;
        case 13:
            return NumberAlphabet::THIRTEEN;
        case 14:
            return NumberAlphabet::FOURTEEN;
        case 15:
            return NumberAlphabet::FIFTEEN;
        case 16:
            return NumberAlphabet::SIXTEEN;
        case 17:
            return NumberAlphabet::SVENTEEN;
        case 18:
            return NumberAlphabet::EIGHTEEN;
        case 19:
            return NumberAlphabet::NINETEEN;
        }
    }
};
int count_two_digit(int num)
{
    switch (num)
    {
    case 2:
        return NumberAlphabet::TWENTY;
    case 3:
        return NumberAlphabet::THIRTY;
    case 4:
        return NumberAlphabet::FOURTY;
    case 5:
        return NumberAlphabet::FIFTY;
    case 6:
        return NumberAlphabet::SIXTY;
    case 7:
        return NumberAlphabet::SVENTY;
    case 8:
        return NumberAlphabet::EIGHTY;
    case 9:
        return NumberAlphabet::NINETY;
    }
}

int alphabet_number_to_number(int num)
{
    if (num > 0 && num < 20)
        return static_cast<int>(count_alpha(num));
    else
    {
        int alpha_sum = 0;
        int last_digit = num % 10;
        num /= 10;
        int middle_digit = num % 10;
        num / 10;
        int first_digit = num / 10;
        if (first_digit == 0)
        {
            return static_cast<int>(count_alpha(last_digit) + count_two_digit(middle_digit));
        }
        else
        {
            if(middle_digit==0&&last_digit==0)
            {
                return 10;
            }
            return static_cast<int>(count_alpha(first_digit) + NumberAlphabet::HUNDRED + 3 + count_two_digit(middle_digit) + count_alpha(last_digit));
        }
    }
}
int main()
{

    std::cout<<alphabet_number_to_number(312);
}