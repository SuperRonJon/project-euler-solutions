#include <limits.h>
#include <stdio.h>

// Fills counts with the number of times the index appears as a digit in value
// Returns the number of digits int value
int count_digits(unsigned int value, int counts[])
{
    if (value == 0)
    {
        counts[0]++;
        return 1;
    }
    int count = 0;
    while (value > 0)
    {
        const size_t digit = value % 10;
        counts[digit]++;
        value /= 10;
        count++;
    }
    return count;
}

// Return 1 if the two integers contain the same exact digits
int compare_digits(unsigned int d1, unsigned int d2)
{
    int c1[10] = {0};
    int c2[10] = {0};
    int len1 = count_digits(d1, c1);
    int len2 = count_digits(d2, c2);
    if (len1 != len2)
        return 0;
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
