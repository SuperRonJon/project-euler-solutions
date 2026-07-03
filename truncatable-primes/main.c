#include <math.h>
#include <stdio.h>

int is_prime(int value)
{
    if (value <= 1)
        return 0;
    if (value == 2)
        return 1;
    if (value % 2 == 0)
        return 0;

    int i;
    for (i = 3; i <= sqrt(value); i++)
    {
        if (value % i == 0)
            return 0;
    }
    return 1;
}

enum direction
{
    LEFT,
    RIGHT
};

static inline int truncate(const int value, const enum direction dir)
{
    switch (dir)
    {
        case LEFT:
            return value % (int)pow(10.0, (int)log10(value));
        case RIGHT:
        default:
            return (int) value / 10;
    }
}

int is_truncatable(const int value, const enum direction dir)
{
    int val = value;
    while (val > 0)
    {
        if (!is_prime(val))
            return 0;
        val = truncate(val, dir);
    }

    return 1;
}

int main(int argc, char **argv)
{
    size_t found = 0;
    int sum = 0;
    int curr = 9;
    while (found < 11)
    {
        if (is_truncatable(curr, RIGHT) && is_truncatable(curr, LEFT))
        {
            printf("%d\n", curr);
            sum += curr;
            found++;
        }
        curr += 2;
    }
    printf("Sum of truncatable primes: %d\n", sum);
}
