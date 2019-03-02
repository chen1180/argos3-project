/*Summation of primes
Problem 10

The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
asnwer:142913828922
*/

#include <iostream>

int main()
{
    int count = 2000000;
    bool prime_number[count];
    for (int i = 0; i < count; i++)
    {
        prime_number[i] = true;
    }
    for (int p = 2; p * p <= count; p++)
    {
        if (prime_number[p] == true)
        {
            for (int i = 2 * p; i <= count; i += p)
                prime_number[i] = false;
        }
    }
    unsigned long sum = 0;
    for (int i = 2; i <= count; i++)
    {

        if (prime_number[i] == true)
        {
            sum += i;
            std::cout << i<< std::endl;
        }
    }
    std::cout << "sum: " << sum << std::endl;
}