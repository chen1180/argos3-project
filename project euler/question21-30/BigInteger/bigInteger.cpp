#include "bigInteger.h"
#include <cmath>
BigInteger::BigInteger()
{
    b_digit.push_back(0);
}
BigInteger::BigInteger(const std::string &big_number)
{
    if (!big_number.empty())
    {
        for (int i = 0; i < big_number.size(); i++)
        {
            b_digit.push_back(big_number[i] - '0');
        }
    }
}
BigInteger::BigInteger(std::vector<int> &digit) : b_digit(digit)
{
    checkOverflow();
}

const std::vector<int> &BigInteger::getNumber() const
{
    return b_digit;
}
int BigInteger::getDigitSize() const
{
    return b_digit.size();
}
int BigInteger::getDigit(int digit) const
{
    return getNumber()[digit];
}

void BigInteger::checkOverflow()
{
    for (int i = b_digit.size() - 1; i >= 0; i--)
    {
        if (b_digit[i] >= 10)
        {
            int overflow = b_digit[i] / 10;
            b_digit[i] %= 10;
            if (i == 0)
            {
                b_digit.insert(b_digit.begin(),overflow);
            }

            else
                b_digit[i - 1] += overflow;
        }
        else
        {
            if (b_digit[i] >= 0)
                continue;
            else
            {
                b_digit[i] += 10;
                --b_digit[i - 1];
            }
        }
    }
}
BigInteger &BigInteger::operator=(const BigInteger &num)
{
    b_digit = num.b_digit;
    return *this;
}
std::ostream &operator<<(std::ostream &out, const BigInteger &big_integer)
{
    for (int i = 0; i < big_integer.getDigitSize(); i++)
        out << big_integer.getDigit(i);
    return out;
}
BigInteger operator+(const BigInteger &num1, const BigInteger &num2)
{
    std::vector<int> result;
    if (num1.getDigitSize() > num2.getDigitSize())
    {
        for (int i = 0; i < num1.getDigitSize(); i++)
        {
            if (i < (num1.getDigitSize() - num2.getDigitSize()))
            {
                result.push_back(num1.getDigit(i));
            }
            else
            {
                result.push_back(num1.getDigit(i) + num2.getDigit(i - (num1.getDigitSize() - num2.getDigitSize())));
            }
        }
    }
    else
    {
        for (int i = 0; i < num2.getDigitSize(); i++)
        {
            if (i < (num2.getDigitSize() - num1.getDigitSize()))
            {
                result.push_back(num2.getDigit(i));
            }
            else
            {
                result.push_back(num1.getDigit(i - (num2.getDigitSize() - num1.getDigitSize())) + num2.getDigit(i));
            }
        }
    }
    return BigInteger(result);
}
BigInteger &operator+=(BigInteger &num1, const BigInteger &num2)
{
    num1 = num1 + num2;
    return num1;
}
BigInteger operator-(BigInteger &num1, const BigInteger &num2)
{
    std::vector<int> result;
    if (num1.getDigitSize() > num2.getDigitSize())
    {
        for (int i = 0; i < num1.getDigitSize(); i++)
        {
            if (i < (num1.getDigitSize() - num2.getDigitSize()))
            {
                result.push_back(num1.getDigit(i));
            }
            else
            {
                result.push_back(num1.getDigit(i) - num2.getDigit(i - (num1.getDigitSize() - num2.getDigitSize())));
            }
        }
    }
    else
    {
        for (int i = 0; i < num2.getDigitSize(); i++)
        {
            if (i < (num2.getDigitSize() - num1.getDigitSize()))
            {
                result.push_back(num2.getDigit(i));
            }
            else
            {
                result.push_back(num2.getDigit(i) - num1.getDigit(i - (num2.getDigitSize() - num1.getDigitSize())));
            }
        }
    }

    return BigInteger(result);
}
// comparison
bool operator<(int num1, const BigInteger &num2)
{
    int num_digit_count = 1;
    while (num1 != 0)
    {
        num1 /= 10;
        ++num_digit_count;
    }
    if (num_digit_count == num2.getDigitSize())
    {
        int sum_of_bigNumber = 0;
        for (int i = 0; i < num2.getDigitSize(); i++)
        {
            sum_of_bigNumber += num2.getDigit(num2.getDigitSize() - 1 - i) * pow(10, i);
            if (sum_of_bigNumber > num1)
                return true;
        }
        return false;
    }
    else
    {
        return num_digit_count < num2.getDigitSize();
    }
}
BigInteger operator*(const BigInteger &num1, const BigInteger &num2)
{
    BigInteger result;
    for (int i = 0; i < num2.getDigitSize(); i++)
    {
        std::vector<int> tmp_multiplication;
        for (int j = 0; j < num1.getDigitSize(); j++)
        {
            tmp_multiplication.push_back(num1.getDigit(j) * num2.getDigit(num2.getDigitSize() - 1 - i));
        }
        for (int k = 0; k < i; k++)
        {
            tmp_multiplication.push_back(0);
        }
        result += BigInteger(tmp_multiplication);
    
    }
    return result;
}
int main()
{
    BigInteger a("3456");
    BigInteger c("1234567890123456789012345678901234567890");
}