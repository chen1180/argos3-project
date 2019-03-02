/*
Longest Collatz sequence
Problem 14

The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:
13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1

It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
answer:837799
*/
#include <iostream>
int generate_sequence_term(const unsigned int &number)
{
    unsigned int start_number = number;
    int term = 1;
    while (start_number != 1)
    {
        if (start_number % 2 == 0)
        {
            start_number /= 2;
            ++term;
        }
        else
        {
            start_number = 3 * start_number + 1;
            ++term;
        }
    }
    return term;
}
int main()
{
    unsigned long start_number = 1000000;
    int max_sequence = 0;
    unsigned int result = 0;
    for (unsigned int i = 1; i <= start_number; i++)
    {
        if (i % 2 != 0)
        {
            int current_sequence = generate_sequence_term(i);
            if (current_sequence > max_sequence)
            {
                max_sequence = current_sequence;
                result = i;
            }
        }
    }
    std::cout << "number is:" << result << " term is:" << max_sequence;
}