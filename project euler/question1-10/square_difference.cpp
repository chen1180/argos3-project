#include <iostream>
#include <cmath>
int main()
{
    int max_number = 100;
    int sum_of_square = 0;
    int square_of_sum = 0;
    for (int i = 1; i <= max_number; i++)
    {
        sum_of_square += pow(i, 2);
        square_of_sum += i;
    }
    std::cout << static_cast<long>(pow(square_of_sum, 2) - sum_of_square) << std::endl;
}