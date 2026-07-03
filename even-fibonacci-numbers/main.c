#include <stdio.h>
#include <stdlib.h>

int sum_even_fib(int max)
{
    int sum = 0;
    int x = 1;
    int y = 2;
    while (x <= max)
    {
        const int z = x + y;
        x = y;
        y = z;
        if (x % 2 == 0)
            sum += x;
    }
    return sum;
}

int main(int argc, char **argv)
{
    const int max = argc == 2 ? strtol(argv[1], NULL, 10) : 4000000;
    const int sum = sum_even_fib(max);
    printf("Sum of even fibonacci numbers under %d: %d\n", max, sum);
    return 0;
}