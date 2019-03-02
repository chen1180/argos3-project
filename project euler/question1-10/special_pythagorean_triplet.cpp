/*Problem 9

A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
a2 + b2 = c2

For example, 32 + 42 = 9 + 16 = 25 = 52.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
answer:31875000
*/
#include <iostream>
#include <cmath>
double find_pythagorean_side(const double &a, const double &b)
{
    return sqrt(pow(a, 2) + pow(b, 2));
}
int main()
{

    for (double a = 1; a <= 1000; a++)
    {
        for (double b = 1; b <= 1000 - a; b++)
        {
            double c = find_pythagorean_side(a, b);
            if ((a + b > c) && (a + c > b) && (b + c) > a)
            {
                if ((a + b + c) == 1000)
                {
                    std::cout << " a:" << a << " b: " << b << " c: " << c << "\n product of abc is: " << a * b * c << std::endl;
                }
            }
        }
    }
}