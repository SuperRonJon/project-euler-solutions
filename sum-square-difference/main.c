#include <stdio.h>
#include <stdlib.h>

int sum_of_squares(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += (i * i);
    }
    return sum;
}

int square_of_sum(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
    return sum * sum;
}

int main(int argc, char **argv)
{
    int n = argc == 2 ? strtol(argv[1], NULL, 10) : 100;

    const int sum = sum_of_squares(n);
    const int square = square_of_sum(n);
    const int diff = square - sum;

    printf("First %d natural numbers\nSum of squares: %d\nSquare of sum: %d\nDifference: %d", n, sum, square, diff);
    return 0;
}