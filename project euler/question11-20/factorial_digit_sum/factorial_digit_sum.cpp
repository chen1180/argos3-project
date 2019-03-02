/*
Factorial digit sum
Problem 20

n! means n × (n − 1) × ... × 3 × 2 × 1

For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100!
answer:648
*/
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
std::vector<int> Factorial(int number)
{
    std::vector<int> factorial;
    factorial.push_back(1);
    for (int i = 1; i <= number; i++)
    {
        for (int j = 0; j < factorial.size(); j++)
        {
            factorial[j] *= i;
        }
        for (int j = 0; j < factorial.size(); j++)
        {
            if (factorial[j] >= 10)
            {

                if (j + 1 >= factorial.size())
                {
                    factorial.push_back(factorial[j] / 10);
                }
                else
                    factorial[j + 1] += factorial[j] / 10;
                factorial[j] %= 10;
            }
        }
    }
    std::reverse(factorial.begin(), factorial.end());
    return factorial;
}
int main()
{
    std::vector<int> a = Factorial(100);
    int sum = 0;
    for (const int &ele : a)
    {
        std::cout << ele;
        sum += ele;
    }
    std::cout << "\n"
              << "final sum is:" << sum << std::endl;
}
