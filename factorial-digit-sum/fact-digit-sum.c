#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

unsigned int sum_digits(mpz_t n)
{
    char *n_str = mpz_get_str(NULL, 10, n);
    const size_t len = strlen(n_str);
    unsigned int total = 0;

    for (size_t i = 0; i < len; i++)
    {
        unsigned int current_digit = n_str[i] - '0';
        total += current_digit;
    }
    free(n_str);
    return total;
}

int main(int argc, char **argv)
{
	const unsigned int n = argc == 2 ? strtoul(argv[1], NULL, 10) : 100;
    mpz_t n_fact;
    mpz_fac_ui(n_fact, n);
	unsigned int sum = sum_digits(n_fact);
    gmp_printf("%u! = %Zu\nSum : %u\n", n, n_fact, sum);
    mpz_clear(n_fact);
	return 0;
}
