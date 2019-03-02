/*

2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

Answer:
	232792560
*/

#include <iostream>

long gcd(long a, long b)
{
    while (b)
    {
        int prevB = b;
        b = a % b;
        a = prevB;
    }
    return a;
}

long lcm(long a, long b)
{
    return a * (b / gcd(a, b));
}

int main()
{
    long result = 10;
    for (long number = result - 1; number > 1; --number)
    {
        result = lcm(result, number);
    }
    std::cout << result << '\n';
}