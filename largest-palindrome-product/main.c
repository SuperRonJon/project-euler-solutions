#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_palindrome(int value)
{
    char str[7];
    snprintf(str, 7, "%d", value);
    const size_t len = strlen(str);
    for (int i = 0; i < len / 2; i++)
    {
        const int j = (len - 1) - i;
        if (str[i] != str[j])
            return 0;
    }
    return 1;
}

int largest_palindrome_product(int min, int max)
{
    int largest = 0;
    for (int i = min; i < max; i++)
    {
        for (int j = min; j < max; j++)
        {
            const int product = i * j;
            if (is_palindrome(product))
            {
                if (product > largest)
                    largest = product;
            }
        }
    }
    return largest;
}

int main(void)
{
    const int largest = largest_palindrome_product(100, 1000);
    printf("Largest palindrome product: %d\n", largest);
    return 0;
}