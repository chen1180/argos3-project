/*Lattice paths
Problem 15

Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.

How many such routes are there through a 20×20 grid?
answer:14688017186506670080
*/

#include <iostream>
unsigned long factorial(int &x)
{
    if (x == 1)
        return 1;
    else
        return x * factorial(--x);
}
unsigned long factorial(int &total, int &count)
{
    if (total / 2 > count)
        return total * factorial(--total, --count);
    if (total / 2 <= count)
    {
        count = total - count;
        return total * factorial(--total, --count);
    }
    if (count == 0)
        return 1;
}
int main()
{
    int x = 2;
    int total = 40;
    std::cout << factorial(total, x) << std::endl;
}