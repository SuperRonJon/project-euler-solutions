#include <stdio.h>

inline unsigned long long nth_triangular(int _n)
{
    const unsigned long long n = _n;
    return n * (n + 1) / 2;
}

inline unsigned long long nth_pentagonal(int _n)
{
    const unsigned long long n = _n;
    return n * ((3 * n) - 1) / 2;
}

inline unsigned long long nth_hexagonal(int _n)
{
    const unsigned long long n = _n;
    return n * ((2 * n) - 1);
}

enum shape
{
    TRIANGULAR,
    PENTAGONAL,
    HEXAGONAL
};

unsigned long long is_shape(unsigned long long value, unsigned long long max, enum shape shp)
{
    for (unsigned long long i = max; i > 0; i--)
    {
        unsigned long long current_shape_value = 0;
        switch(shp)
        {
            case TRIANGULAR:
                current_shape_value = nth_triangular(i);
                break;
            case PENTAGONAL:
                current_shape_value = nth_pentagonal(i);
                break;
            case HEXAGONAL:
                current_shape_value = nth_hexagonal(i);
                break;
        }
        if (current_shape_value == value)
            return i;
        if (current_shape_value < value)
            return 0;
    }
    return 0;
}

struct all_shapes
{
    int triangular_n;
    int pentagonal_n;
    int hexagonal_n;
    unsigned long long value;
};

void next_all_shapes(struct all_shapes *result, int t_start)
{
    for (int i = t_start; i< 100000; i++)
    {
        const unsigned long long current_triangle = nth_triangular(i);
        const int is_pentagonal = is_shape(current_triangle, i, PENTAGONAL);
        if (is_pentagonal)
        {
            const int is_hexagonal = is_shape(current_triangle, is_pentagonal, HEXAGONAL);
            if (is_hexagonal)
            {
                result->triangular_n = i;
                result->pentagonal_n = is_pentagonal;
                result->hexagonal_n = is_hexagonal;
                result->value = current_triangle;
                return;
            }
        }
    }
    result->triangular_n = 0;
    result->pentagonal_n = 0;
    result->hexagonal_n = 0;
    result->value = 0;
    return;
}

int main(void)
{
    struct all_shapes next;
    next_all_shapes(&next, 2);
    printf("First common value T_%d = P_%d = H_%d = %llu\n", next.triangular_n, next.pentagonal_n, next.hexagonal_n, next.value);

    next_all_shapes(&next, next.triangular_n + 1);
    printf("Second common value T_%d = P_%d = H_%d = %llu\n", next.triangular_n, next.pentagonal_n, next.hexagonal_n, next.value);
}
