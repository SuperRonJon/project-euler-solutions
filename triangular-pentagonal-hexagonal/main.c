#include <stdio.h>

unsigned long long nth_triangular(int _n)
{
    const unsigned long long n = _n;
    return n * (n + 1) / 2;
}

unsigned long long nth_pentagonal(int _n)
{
    const unsigned long long n = _n;
    return n * ((3 * n) - 1) / 2;
}

unsigned long long nth_hexagonal(int _n)
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

struct all_shapes next_all_shapes(int t_start)
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
                struct all_shapes result = {i, is_pentagonal, is_hexagonal, current_triangle};
                return result;
            }
        }
    }
    struct all_shapes result = {0, 0, 0, 0};
    return result;
}

int main(void)
{
    const int n = 2;
    struct all_shapes next = next_all_shapes(n);
    printf("First common value T_%d = P_%d = H_%d = %llu\n", next.triangular_n, next.pentagonal_n, next.hexagonal_n, next.value);

    next = next_all_shapes(next.triangular_n + 1);
    printf("Second common value T_%d = P_%d = H_%d = %llu\n", next.triangular_n, next.pentagonal_n, next.hexagonal_n, next.value);
}
