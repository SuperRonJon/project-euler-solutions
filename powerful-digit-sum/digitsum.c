#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

unsigned int digital_sum(mpz_t value)
{
    char *str = mpz_get_str(NULL, 10, value);
    const size_t len = strlen(str);

    int sum = 0;
    for (size_t i = 0; i < len; i++)
        sum += str[i] - '0'; 
    free(str);
    return sum;
}

struct digital_sum_result
{
    unsigned int largest_sum;
    unsigned int largest_a;
    unsigned int largest_b;
};

struct digital_sum_result largest_digital_sum(mpz_t largest)
{
    unsigned int largest_sum = 0;
    unsigned int largest_a = 0;
    unsigned int largest_b = 0;
    
    mpz_t curr;
    mpz_init(curr);
    mpz_init(largest);

    for (unsigned int a = 1; a < 100; a++)
    {
        for (unsigned int b = 1; b < 100; b++)
        {
            mpz_ui_pow_ui(curr, a, b);
            const unsigned int curr_sum = digital_sum(curr);
            if (curr_sum > largest_sum)
            {
                mpz_set(largest, curr);
                largest_sum = curr_sum;
                largest_a = a;
                largest_b = b;
            }
        }
    }
    // gmp_printf("Value with largest sum %u^%u = %Zu\nSum: %d\n", largest_a, largest_b, largest, largest_sum);
    mpz_clear(curr);
    struct digital_sum_result result = {largest_sum, largest_a, largest_b};
    return result;
}

int main(void)
{
    mpz_t largest;
    struct digital_sum_result result = largest_digital_sum(largest);
    gmp_printf("Value with largest sum %u^%u = %Zu\nSum: %d\n", result.largest_a, result.largest_b, largest, result.largest_sum);
    return 0;
}
