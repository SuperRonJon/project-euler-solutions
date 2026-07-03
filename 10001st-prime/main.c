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

int nth_prime(int n)
{
    int found = 0;
    int i = 0;
    while (found < n)
    {
        if (is_prime(++i))
            found++;
    }
    return i;
}

int main(int argc, char **argv)
{
    int n = argc == 2 ? strtol(argv[1], NULL, 10) : 10001;
    int nth = nth_prime(n);
    printf("%dth prime: %d\n", n, nth);
    return 0;
}