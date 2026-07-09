#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int factorial(unsigned int n)
{
    unsigned int total = 1;
    for (unsigned int i = 2; i <= n; i++)
    {
        total *= i;
    }
    return total;
}

unsigned int sum_fact_digits(unsigned int n)
{
    const size_t str_size = 10;
    char str[str_size];
    snprintf(str, str_size, "%u", n);
    const size_t len = strlen(str);
    unsigned int sum = 0;

    for (size_t i = 0; i < len; i++)
    {
        const unsigned int current_digit = str[i] - '0';
        sum += factorial(current_digit);
    }
    return sum;
}

unsigned int sum_all_eq()
{
    unsigned int total = 0;

    for (unsigned int i = 10; i < 9999999U; i++)
    {
        const unsigned int sum = sum_fact_digits(i);
        if (sum == i)
            total += sum;
    }
    return total;
}

int main(int argc, char **argv)
{
    const unsigned int result = sum_all_eq();
    printf("%u\n", result);
    return 0;
}
