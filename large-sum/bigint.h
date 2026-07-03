#ifndef BIGINT_H
#define BIGINT_H

#include <stddef.h>
#include <stdint.h>

// Digits stored in uint8_t array in reverse order
struct bigint
{
    size_t len;
    size_t cap;
    uint8_t *digits;
};

void bigint_init(struct bigint *bi, const int value);
void bigint_init_cap(struct bigint *bi, const int value, const size_t cap);
void bigint_inits(struct bigint *bi, const char *const str);
void bigint_inits_cap(struct bigint *bi, const char *const str, const size_t cap);

void bigint_set(struct bigint *bi, const int value);
void bigint_sets(struct bigint *bi, const char *const str);
void bigint_cpy(struct bigint *dst, const struct bigint *const src);

void bigint_print(const struct bigint *const bi, const size_t max_chars);
char *bigint_tostr(const struct bigint *const bi);

void bigint_free(struct bigint *bi);

void bigint_add(struct bigint *bi, const struct bigint *const toadd);

#endif
