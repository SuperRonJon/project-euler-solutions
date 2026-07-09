#include <limits.h>
#include <stdio.h>
#include <string.h>

#define BUFFSIZE 32

void count_digits(const char *str, int c1[])
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        size_t current_digit = str[i] - '0';
        c1[current_digit]++;
    }
}

// Return 1 if the two integers contain the same exact digits
int compare_digits(unsigned int d1, unsigned int d2)
{
    char b1[BUFFSIZE];
    char b2[BUFFSIZE];
    snprintf(b1, sizeof(b1), "%llu", d1);
    snprintf(b2, sizeof(b2), "%llu", d2);

    if (strlen(b1) != strlen(b2))
        return 0;
    int c1[10] = {0};
    int c2[10] = {0};
    count_digits(b1, c1);
    count_digits(b2, c2);
    for (size_t i = 0; i < 10; i++)
    {
        if (c1[i] != c2[i])
            return 0;
    }
    return 1;
}

int main(void)
{
    unsigned int i = 1;
    while (i < (UINT_MAX / 6))
    {
        const unsigned int ix2 = 2 * i;
        if (
                compare_digits(i, ix2) &&
                compare_digits(ix2, 3 * i) && 
                compare_digits(ix2, 4 * i) && 
                compare_digits(ix2, 5 * i) && 
                compare_digits(ix2, 6 * i)
            )
        {
            printf("%u\n", i);
            break;
        }
        i++;
    }
    return 0;
}
