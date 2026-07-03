#include <math.h>
#include <stdio.h>
#include <stdbool.h>

bool is_prime(int value)
{
    if (value <= 1)
        return false;
    if (value == 2)
        return true;
    if (value % 2 == 0)
        return false;
    
    for (int i = 3; i <= sqrt(value); i+=2)
    {
        if (value % i == 0)
            return false;
    }
    return true;
}

bool is_pandigital(int value)
{
    bool seen[9] = {false};
    int digits = 0;
    if (value < 10)
        return false;
    while (value > 0)
    {
        digits++;
        const int digit = value % 10;
        value /= 10;
        if (seen[digit])
            return false;
        seen[digit] = true;
    }
    for (int i = 0; i < 9; i++)
    {
        if (seen[i] && (i > digits || i == 0))
            return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    int pandigital_prime = -1;
    for (int i = 987654321; i > 99; i--)
    {
        if (is_pandigital(i) && is_prime(i))
        {
            pandigital_prime = i;
            break;
        }
    }
    if (pandigital_prime != -1)
        printf("Largest pandigital prime: %d\n", pandigital_prime);
    else
        puts("Didn't find anything");
    return 0;
}