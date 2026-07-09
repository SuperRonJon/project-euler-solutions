#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int sum_digits_n_power(unsigned int value, int n)
{
    char str[10];
    snprintf(str, 10, "%u", value);
    size_t len = strlen(str);
    unsigned int sum = 0;

    for (size_t i = 0; i < len; i++)
    {
        const unsigned int digit = str[i] - '0';
        sum += (int) pow(digit, n);
    }
    return sum;
}

unsigned int sum_all_n_powers(unsigned int n)
{
    unsigned int total = 0;
    for (unsigned int i = 10; i < 10000000; i++)
    {
        const unsigned int sum = sum_digits_n_power(i, n);
        if (sum == i)
            total += sum;
    }
    return total;
}

int main(int argc, char **argv)
{
    const unsigned int n = argc == 2 ? strtoul(argv[1], NULL, 10) : 4;

    unsigned int sum = sum_all_n_powers(n);
    printf("Sum: %u\n", sum);
}
