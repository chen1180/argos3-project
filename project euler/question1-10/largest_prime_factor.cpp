/*
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?

Answer:
	6857
*/

#include <iostream>
int main()
{
    long number = 600851475143;
    for (long i = 2; i <= number; i++)
    {
        if (number % i == 0)
        {
            number /= i;
            std::cout << i << ' ';
        }
    }
}