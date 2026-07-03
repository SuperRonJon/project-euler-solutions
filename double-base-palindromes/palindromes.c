#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 100

static inline size_t num_digits(const int value, const int base)
{
    return (size_t) floor(log10(value) / log10(base)) + 1;
}

static inline void reverse_str(char *str)
{
    const size_t len = strlen(str);

    for (size_t i = 0; i < len / 2; i++)
    {
        const size_t j = (len - 1) - i;
        const char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}

char *tostrb(char *buff, const size_t n, const int value, const int base)
{
    static const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const size_t digits_len = strlen(digits);
    if (base > digits_len)
        return NULL;

    size_t res_i = 0;
    int val = value;
    while (val > 0 && res_i < n)
    {
        const int digit = val % base;
        buff[res_i++] = digits[digit];
        val /= base;
    }
    buff[res_i] = '\0';
    reverse_str(buff);
    return buff;
}

char *new_tostrb(const int value, const int base)
{
    const size_t len = num_digits(value, base);
    char *result = malloc ((len + 1) * sizeof(*result));
    result = tostrb(result, len + 1, value, base);
    return result;
}

int is_palindrome(const char *const str)
{
    const size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++)
    {
        const size_t j = (len - 1) - i;
        if (str[i] != str[j])
            return 0;
    }
    return 1;
}

size_t count_double_base_palindromes(const int max_value)
{
    size_t sum = 0;
    char buff[BUFFSIZE];
    for (int i = 0; i < max_value; i++)
    {
        tostrb(buff, BUFFSIZE, i, 10);
        if(!is_palindrome(buff))
            continue;
        tostrb(buff, BUFFSIZE, i, 2);
        if(!is_palindrome(buff))
            continue;
        printf("%d: %s\n", i, buff);
        sum += i;
    }
    return sum;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fputs("No input given\n", stderr);
        return 1;
    }
    const int value = strtol(argv[1], NULL, 10);
    const size_t sum = count_double_base_palindromes(value);
    printf("Sum of double base palindromes under %d: %zu\n", value, sum);
    return 0;
}
