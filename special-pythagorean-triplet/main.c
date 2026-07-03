#include <stdio.h>
#include <math.h>

int main(void)
{
    const int target = 1000;

    for (int b = 2; b < target; b++)
    {
        for (int a = 1; a < b; a++)
        {
            const double cd = sqrt((a * a) + (b * b));
            if (fmod(cd, 1.0) != 0.0)
                continue;
            const int c = (int) cd;
            if (a + b + c == target)
            {
                const int product = a * b * c;
                printf("Found triplet %d + %d + %d = %d\n", a, b, c, target);
                printf("Product: %d\n", product);
                break;
            }
        }
    }
    return 0;
}