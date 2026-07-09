#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

void self_power_series(mpz_t result, unsigned int n)
{
    mpz_init_set_ui(result, 0U);

    mpz_t curr;
    mpz_init(curr);
    for (unsigned int i = 1; i <= n; i++)
    {
        mpz_ui_pow_ui(curr, i, i);
        mpz_add(result, result, curr);
    }
    mpz_clear(curr);
}

int main(int argc, char **argv)
{
    const int n = argc == 2 ? strtol(argv[1], NULL, 10) : 1000;

    mpz_t series_result;
    self_power_series(series_result, n);
    char *result_str = mpz_get_str(NULL, 10, series_result);
    const size_t len = strlen(result_str);
    if (len >= 10)
    {
        printf      ("Last 10 digits:   %s\n", result_str + (len - 10));
        printf      ("Total digits:     %zu\n", len);
    }
    else
        printf("%s\n", result_str);
    free(result_str);
    mpz_clear(series_result);
}
