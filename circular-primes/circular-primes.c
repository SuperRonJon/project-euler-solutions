#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_digits(int value)
{
    if (value == 0)
        return 1;
    size_t i = 0;
    while (value > 0)
    {
        value /= 10;
        i++;
    }
    return i;
}

int rotate_number(int value, size_t digits)
{
    char buff[10];
    snprintf(buff, 10, "%0*d", digits, value);
    const size_t len = strlen(buff);
    if (len == 0)
        return 0;

    char tmp = buff[0];
    for (size_t i = 0; i < len - 1; i++)
    {
        buff[i] = buff[i + 1];
    }
    buff[len - 1] = tmp;
    return (int) strtol(buff, NULL, 10);
}

void print_all_rotations(int value)
{
    const size_t digits = count_digits(value);
    int val = value;
    for (size_t i = 0; i < digits; i++)
    {
        printf("%d\n", val);
        val = rotate_number(val, digits);
    }
}

int is_prime(int value)
{
    if (value <= 1)
        return 0;
    if (value == 2)
        return 1;
    if (value % 2 == 0)
        return 0;
    
    for (int i = 3; i <= sqrt(value); i++)
    {
        if (value % i == 0)
            return 0;
    }
    return 1;
}

int is_circular_prime(int value)
{
    const size_t digits = count_digits(value);
    for (size_t i = 0; i < digits; i++)
    {
        if (!is_prime(value))
            return 0;
        value = rotate_number(value, digits);
    }
    return 1;
}

int main(int argc, char **argv)
{
    const int value = argc == 2 ? strtol(argv[1], NULL, 10) : 1000000;
    int count = 0;
    for (int i = 1; i < value; i++)
    {
        if (is_circular_prime(i))
        {
            count++;
            printf("%d\n", i);
        }
    }
    printf("%d circular primes below %d\n", count, value);
    return 0;
}
