/*Problem 4

A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
answe:
*/
#include <cmath>
#include <iostream>
bool check_panlindrome_product(const int &number)
{
    int num = number;
    int digit_count = 0;
    int reversed_number = 0;
    do
    {
        num /= 10;
        ++digit_count;

    } while (num > 0);
    int digit_number[digit_count];
    num = number;
    for (int i = 0; i < digit_count; i++)
    {
        digit_number[i] = (num % 10);
        num /= 10;
        reversed_number += digit_number[i] * pow(10, digit_count - i - 1);
        //std::cout << num << std::endl;
        //std::cout << reversed_number << std::endl;
    }
    if (reversed_number == number)
        return true;
    else
        return false;
}
int main()
{
    int digit = 999;
    bool find_result = false;
    int result = 0;

    for (int i = digit; i >= 900; i--)
    {
        for (int j = digit; j >= 900; j--)
        {
            int tmp = i * j;
            if (check_panlindrome_product(tmp))
            {
                if (tmp > result)
                {
                    result = tmp;
                    std::cout << i << ' ' << j << ' ';
                }
            }
        }
    }
    std::cout << result << ' ';
}