#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_next_quote_index(char *str, int start)
{
	int length = strlen(str);
	if (start >= length)
		return -1;
	for(int i = start; i < length; i++)
	{
		if (str[i] == '"')
			return i;
	}
	return -1;
}

int compareStrings(const void *a, const void *b)
{
	return strcmp(*(const char **)a, *(const char **)b);
}


char** names_to_array(char *all_names, const int count)
{
	char **names = malloc(count * sizeof(char*));
	int name_index = 0;
	int i = 0;
	while((i = get_next_quote_index(all_names, i)) != -1)
	{
		const int word_start = i + 1;
		const int word_end = get_next_quote_index(all_names, word_start);
		const int length = word_end - word_start;
		char *word = malloc(length + 1);
		for (int j = 0; j < length; j++)
		{
			word[j] = all_names[word_start + j];
		}
		word[length] = '\0';
		names[name_index++] = word;
		i = word_end+1;
	}
	free(all_names);
	qsort(names, count, sizeof(char *), compareStrings);
	return names;
}

void free_names(char **names, const int count)
{
	for (int i = 0; i < count; i++)
	{
		free(names[i]);
	}
	free(names);
}

uint64_t score_name(char *name, int pos)
{
	uint64_t score = 0;
	size_t length = strlen(name);
	for(size_t i = 0; i < length; i++)
	{
		score += (name[i] - 'A') + 1;
	}
	return score * (uint64_t)pos;
}

uint64_t all_scores(char **names, const int count)
{
	uint64_t sum = 0;
	for (int i = 0; i < count; i++)
	{
		sum += score_name(names[i], i+1);
	}
	return sum;
}

int file_length(FILE* file)
{
	fseek(file, 0L, SEEK_END);
	int size = ftell(file);
	rewind(file);
	return size + 1;
}

int count_names(char *all_names)
{
	size_t length = strlen(all_names);
	int count = 0;
	for (size_t i = 0; i < length; i++)
	{
		if (all_names[i] == '"')
			count++;
	}
	return count / 2;
}

int main(int argc, char **argv)
{
	char *filename = "names.txt";
	if (argc == 2)
		filename = argv[1];

	FILE *infile = fopen(filename, "r");
	if (infile == NULL)
	{
		printf("Error opening file %s\n", filename);
		return 1;
	}

	int file_size = file_length(infile);

	char *all_names = malloc(file_size);
	if (fgets(all_names, file_size, infile) == NULL)
	{
		printf("Error reading file %s\n", filename);
		fclose(infile);
		return 1;
	}
	fclose(infile);

	int name_count = count_names(all_names);
	char **names = names_to_array(all_names, name_count);
	uint64_t score = all_scores(names, name_count);
	printf("Total score: %llu\n", score);
	free_names(names, name_count);
}
