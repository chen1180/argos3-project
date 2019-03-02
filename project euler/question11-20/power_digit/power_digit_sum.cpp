/*
Power digit sum
Problem 16

2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?
answer: 1366
*/

#include <iostream>
#include <vector>
int main()
{
    std::vector<int> number;
    number.push_back(1);
    for (int i = 0; i < 1000; i++)
    {

        for (int index = 0; index < number.size(); index++)
        {

            number[index] *= 2;
        }
        for (int index = 0; index < number.size(); index++)
        {
            if (number[index] >= 10)
            {
                number[index] %= 10;

                if ((index + 1) < number.size())
                    ++number[index + 1];
                else
                    number.push_back(1);
            }
        }
    }
    int sum = 0;
    for (int index = number.size() - 1; index >= 0; index--)
    {
        sum += number[index];
        std::cout << number[index];
    }
    std::cout << "\n";
    std::cout << "power digit sum is:" << sum << "\n";
}