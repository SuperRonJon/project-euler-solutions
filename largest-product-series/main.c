#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 1024

uint64_t highest_adjacent_product(char *numbers, int n)
{
	uint64_t largest_product = 0;
	size_t numbers_len = strlen(numbers);
	for (int i = 0; i < numbers_len - n; i++)
	{
		uint64_t product = 1;
		for (int j = i; j < i + n; j++)
		{
			int digit = numbers[j] - '0';
			product *= digit;
		}
		if (product > largest_product)
			largest_product = product;
	}
	return largest_product;
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
		uint64_t largest = highest_adjacent_product(buff, num_digits);
		printf("Largest adjacent product of %d digits: %llu\n", num_digits, largest);
	}
	else
	{
		puts("Usage:\n  ./main [input_file] [num adjacent digits]\n  input_file should contain a single line of digits only");
	}
	return 0;
}
