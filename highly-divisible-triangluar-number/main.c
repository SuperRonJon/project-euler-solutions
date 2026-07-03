#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int nth_triangle(int n)
{
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		sum += i;
	}
	return sum;
}

int num_divisors(int n)
{
	int count = 0;
	for(int i = 1; i <= (int)sqrt(n); i++)
	{
		if (n % i == 0)
		{
			if (n == 1)
				count++;
			else
				count += 2;	
		}
	}
	return count;
}

int triangle_n_divisors(int n)
{
	int divisor_count = 0;
	int i = 0;
	int triangle = 0;
	while(divisor_count < n)
	{
		i++;
		triangle = nth_triangle(i);
		divisor_count = num_divisors(triangle);
	}
	return triangle;
}

int main(int argc, char **argv)
{
	int divisors = 5;
	if (argc == 2)
		divisors = strtol(argv[1], NULL, 10);
	int result = triangle_n_divisors(divisors);
	printf("First triangle number with over %d divisors: %d\n", divisors, result);
	return 0;
}
