/*10001st prime
Problem 7

By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10 001st prime number?
answer:104743
*/
#include <iostream>
using namespace std;
bool check_if_prime_number(const int &n)
{
    bool isPrime = true;
    for (int i = 2; i <= n / 2; ++i)
    {
        if (n % i == 0)
        {
            isPrime = false;
            break;
        }
    }
    return isPrime;
}
int main()
{
    int count = 0;
    int initial_number = 1;
    while (count < 10001)
    {

        if (check_if_prime_number(++initial_number))
        {
            ++count;
        }
    }
    cout << count << "th prime number is:" << initial_number << endl;
}