#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 1024

struct adj_product
{
	uint64_t product;
	int *digits;
};

struct adj_product highest_adjacent_product(char *numbers, int n)
{
	struct adj_product result;
	result.product = 0;
	size_t digits_size = (size_t) n * sizeof(int);
	result.digits = malloc(digits_size);
	size_t numbers_len = strlen(numbers);
	for (int i = 0; i < numbers_len - n; i++)
	{
		uint64_t product = 1;
		int *curr_digits = malloc(digits_size);
		int iter = 0;
		for (int j = i; j < i + n; j++)
		{
			int digit = numbers[j] - '0';
			curr_digits[iter++] = digit;
			product *= digit;
		}
		if (product > result.product)
		{
			result.product = product;
			memcpy(result.digits, curr_digits, digits_size);
		}
		free(curr_digits);
	}
	return result;
}

int main(int argc, char **argv)
{
	if (argc == 2 || argc == 3)
	{
		FILE* infile = fopen(argv[1], "r");

		char buff[BUFFSIZE];
		if (fgets(buff, sizeof(buff), infile) == NULL)
		{
			fputs("Error reading input file\n", stderr);
			return 1;
		}

		if (fclose(infile) != 0)
		{
			fputs("Error closing input file\n", stderr);
			return 1;
		}

		int num_digits = 4;
		if (argc == 3)
		{
			num_digits = strtol(argv[2], NULL, 10);
		}
		struct adj_product largest = highest_adjacent_product(buff, num_digits);
		printf("Largest adjacent product of %d digits: %llu\n", num_digits, largest.product);
		for (int i = 0 ; i < num_digits; i++)
		{
			printf("%d", largest.digits[i]);
			if (i < num_digits - 1)
				printf(", ");
		}
		printf("\n");
		free(largest.digits);
	}
	else
	{
		puts("Usage:\n  ./main [input_file] [num adjacent digits]\n  input_file should contain a single line of digits only");
	}
	return 0;
}
