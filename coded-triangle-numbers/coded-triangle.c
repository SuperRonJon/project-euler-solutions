#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int nth_triangle_number(int n)
{
    return (n * 0.5) * (n + 1);
}

int is_triangle_number(int n)
{
    int current_triangle = 0;
    int i = 1;
    while (current_triangle <= n)
    {
        current_triangle = nth_triangle_number(i++);
        if (current_triangle == n)
            return 1;
    }
    return 0;
}

int get_word_value(const char *const word)
{
    int sum = 0;
    const size_t len = strlen(word);
    for (size_t i = 0; i < len; i++)
    {
        sum += (word[i] - 'A') + 1;
    }
    return sum;
}

size_t get_delim(char **strptr, size_t *n, const char delimiter, FILE *stream)
{
    char ch;
    size_t i = 0;

    size_t buffsize = 32;
    char *buffer = malloc(buffsize * sizeof(*buffer));
    if (!buffer)
        return -1;

    while ((ch = getc(stream)) != '\0')
    {
        if (ch == EOF)
        {
            if (i == 0)
                return -1;
            break;
        }
        if (i >= buffsize - 1)
        {
            buffsize *= 2;
            buffer = realloc(buffer, buffsize * sizeof(*buffer));
            if (!buffer)
                return -1;
        }
        buffer[i++] = ch;
        if (ch == delimiter)
            break;
    }
    buffer[i] = '\0';
    if (*n < i + 1 || *strptr == NULL)
    {
        *n = i + 1;
        *strptr = realloc(*strptr, i + 1);
    }
    strncpy(*strptr, buffer, i + 1);
    free(buffer);
    return i;
}

char **read_words(FILE *input, size_t *n)
{
    size_t current_length = 0;
    size_t current_cap = 20;
    char **words = malloc(current_cap * sizeof(*words));
    char *buffer = NULL;
    size_t buff_size = 0;
    ssize_t read;

    while ((read = get_delim(&buffer, &buff_size, ',', input)) != -1)
    {
        char *current_word = malloc((read - 2) * sizeof(*current_word));
        size_t word_i = 0;
        int in_word = 0;
        for (ssize_t i = 0; i < read; i++)
        {
            if (!in_word && buffer[i] == '"')
            {
                in_word = 1;
                continue;
            }
            if (in_word && buffer[i] == '"')
            {
                current_word[word_i] = '\0';
                in_word = 0;
                break;
            }
            current_word[word_i++] = buffer[i];
        }
        if (in_word)
        {
            free(current_word);
            continue;
        }
        if (current_length >= current_cap)
        {
            current_cap *= 2;
            words = realloc(words, current_cap * sizeof(*words));
        }
        words[current_length++] = current_word;
    }
    free(buffer);
    *n = current_length;
    words = realloc(words, *n * sizeof(*words));
    return words;
}

void free_words(char **words, const size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        free(words[i]);
    }
    free(words);
}

int main(int argc, char **argv)
{
    FILE *infile;

    if (argc != 2)
        infile = stdin;
    else
        infile = fopen(argv[1], "r");

    if (!infile)
    {
        perror("Error opening input file");
        return 1;
    }
    size_t n;
    char **words = read_words(infile, &n);
    size_t triangle_words = 0;
    for (size_t i = 0; i < n; i++)
    {
        const size_t word_len = strlen(words[i]);
        const int word_value = get_word_value(words[i]);
        if (is_triangle_number(word_value))
            triangle_words++;
    }
    free_words(words, n);
    printf("%zu triangle words out of %zu total words\n", triangle_words, n);
    return 0;
}
