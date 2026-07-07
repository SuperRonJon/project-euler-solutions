#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

size_t bigfib(struct bigint *x, const size_t max_digits)
{
    struct bigint y;
    struct bigint z;
    bigint_init(x, 0);
    bigint_init(&y, 1);
    bigint_init(&z, 1);

    size_t digits = 1;
    size_t i = 0;
    while (x->len < max_digits)
    {
        bigint_cpy(&z, x);
        bigint_add(&z, &y);
        bigint_cpy(x, &y);
        bigint_cpy(&y, &z);
        i++;
    }
    return i;
}

int main(int argc, char **argv)
{
    const size_t n = argc == 2 ? strtoull(argv[1], NULL, 10) : 1000;

    struct bigint x;
    const size_t i = bigfib(&x, n);
    printf("First fibonacci number to %zu digits\nfib(%zu) = ", n, i);
    bigint_print(&x, -1);
    putchar('\n');
    return 0;
}