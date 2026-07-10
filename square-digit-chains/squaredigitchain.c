#include <stdio.h>
#include <stdlib.h>

static inline unsigned int chain_next(unsigned int current)
{
    unsigned int sum = 0;
    while (current > 0)
    {
        const unsigned int digit = current % 10;
        current /= 10;
        sum += digit * digit;
    }
    return sum;
}

int chain_ends_89(unsigned int starting_value)
{
    unsigned int current = starting_value;
    while (current != 89 && current != 1)
    {
        current = chain_next(current);
    }
    return current == 89;
}

int main(int argc, char **argv)
{
    const unsigned int n = argc == 2 ? strtoul(argv[1], NULL, 10) : 10000000;

    int count = 0;
    for (unsigned int i = 2; i < n; i++)
    {
        if (chain_ends_89(i))
            count++;
    }
    printf("Number of chains under %u that end in 89: %d\n", n, count);
    return 0;
}