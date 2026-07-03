#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime(int value)
{
    if (value <= 1)
        return 0;
    if (value == 2)
        return 1;
    if (value % 2 == 0)
        return 0;
    
    for (int i = 3; i <= sqrt(value); i+=2)
    {
        if (value % i == 0)
            return 0;
    }
    return 1;
}

unsigned long long sum_primes_below(int n)
{
    unsigned long long sum = n >= 2 ? 2ULL : 0ULL;

    for (int i = 3; i <= n; i+=2)
    {
        if (is_prime(i))
            sum += i;
    }
    return sum;
}

int main(int argc, char **argv)
{
    const int n = argc == 2 ? strtol(argv[1], NULL, 10) : 10;
    const unsigned long long sum = sum_primes_below(n);
    printf("Sum of primes below %d: %llu\n", n, sum);
    return 0;
}