#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigint.h"

static inline size_t num_digits(const int value)
{
    if (value == 0)
        return 1;
    int val = value;
    size_t count = 0;
    while (val > 0)
    {
        val /= 10;
        count++;
    }
    return count;
}

static inline struct bigint *update_to_cap(struct bigint *bi, const size_t new_cap)
{
    bi->cap = new_cap;
    bi->digits = realloc(bi->digits, bi->cap);
    if (!bi->digits)
        return NULL;
    else
        return bi;
}

static inline void standard_increase(struct bigint *bi, const size_t minimum_size)
{
    size_t to_mult = 2;
    while (bi->cap * to_mult < minimum_size)
        to_mult *= 2;
    update_to_cap(bi, bi->cap * to_mult);
}

void bigint_set(struct bigint *bi, const int value)
{
    const size_t num_dig = num_digits(value);
    bi->len = num_dig;
    if (bi->cap < num_dig)
    {
        standard_increase(bi, num_dig);
        memset(bi->digits, 0, bi->cap);
    }

    int val = value;

    for (size_t i = 0; i < num_dig; i++)
    {
        bi->digits[i] = (uint8_t) (val % 10);
        val /= 10;
    }
}

void bigint_sets(struct bigint *bi, const char *const str)
{
    size_t len = strlen(str);
    if (str[len - 1] == '\n')
        len--;
    bi->len = len;
    if (bi->cap < bi->len)
    {
        standard_increase(bi, len);
        memset(bi->digits, 0, bi->cap);
    }

    for (size_t i = 0; i < bi->len; i++)
    {
        const size_t str_i = (len - 1) - i;
        bi->digits[i] = (uint8_t) (str[str_i] - '0');
    }
}

void bigint_init_cap(struct bigint *bi, const int value, const size_t cap)
{
    bi->cap = cap;
    bi->digits = calloc(cap, sizeof(*bi->digits));
    bigint_set(bi, value);
}

void bigint_init(struct bigint *bi, const int value)
{
    const size_t num_dig = num_digits(value);
    bigint_init_cap(bi, value, num_dig);
}

void bigint_inits_cap(struct bigint *bi, const char *const str, const size_t cap)
{
    bi->cap = cap;
    bi->digits = calloc(cap, sizeof(*bi->digits));
    bigint_sets(bi, str);
}

void bigint_inits(struct bigint *bi, const char *const str)
{
    size_t len = strlen(str);
    if (str[len - 1] == '\n')
        len--;
    bigint_inits_cap(bi, str, len);
}

void bigint_add(struct bigint *bi, const struct bigint *const toadd)
{
    const size_t result_max = (bi->len >= toadd->len ? bi->len : toadd->len) + 1;
    size_t to_mult = 2;
    if (result_max > bi->cap)
    {
        standard_increase(bi, result_max);
    }
    uint8_t carry = 0;
    size_t i;
    for (i = 0; i < bi->len; i++)
    {
        if (i < toadd->len)
        {
            uint8_t add_result = bi->digits[i] + toadd->digits[i] + carry;
            carry = 0;
            if (add_result >= 10)
            {
                add_result = add_result % 10;
                carry = 1;
            }
            bi->digits[i] = add_result;
        }
        else if (carry == 1)
        {
            uint8_t add_result = bi->digits[i] + carry;
            carry = 0;
            if (add_result >= 10)
            {
                add_result = add_result % 10;
                carry = 1;
            }
            bi->digits[i] = add_result;
        }
    }
    while (i < toadd->len)
    {
        uint8_t add_result = toadd->digits[i] + carry;
        carry = 0;
        if (add_result >= 10)
        {
            add_result = add_result % 10;
            carry = 1;
        }
        bi->digits[i] = add_result;
        bi->len++;
        i++;
    }
    if (carry == 1)
    {
        bi->len++;
        bi->digits[i] = 1;
    }
}

void bigint_cpy(struct bigint *dst, const struct bigint *const src)
{
    dst->len = src->len;
    if (dst->cap < src->len)
        standard_increase(dst, src->len);
    for (size_t i = 0; i < dst->len; i++)
    {
        dst->digits[i] = src->digits[i];
    }
}

void bigint_print(const struct bigint *const bi, const size_t max_chars)
{
    const size_t amount = max_chars >= bi->len ? bi->len : max_chars;
    for (size_t i = 0; i < amount; i++)
    {
        const size_t index = (bi->len - 1) - i;
        printf("%d", bi->digits[index]);
    }
}

char *bigint_tostr(const struct bigint *const bi)
{
    char *str = malloc((bi->len + 1) * sizeof(char));
    for (size_t i = 0; i < bi->len; i++)
    {
        const size_t index = (bi->len - 1) - i;
        str[i] = (char)bi->digits[index] + '0';
    }
    str[bi->len] = '\0';
    return str;
}

void bigint_free(struct bigint *bi)
{
    free(bi->digits);
}