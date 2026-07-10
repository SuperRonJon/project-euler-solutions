#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bigint.h"

int main(int argc, char **argv)
{
    FILE *fp = NULL;
    if (argc != 2)
        fp = stdin;
    else
        fp = fopen(argv[1], "r");

    if (!fp)
    {
        perror("Error opening input file");
        return 1;
    }

    char linebuff[100];
    int get_first = 1;
    struct bigint val;
    struct bigint toadd;

    struct timespec start, end;
    timespec_get(&start, TIME_UTC);

    while (fgets(linebuff, sizeof(linebuff), fp) != NULL)
    {
        // Remove newline character from linebuff
        const size_t newline_i = strcspn(linebuff, "\n");
        if (newline_i < strlen(linebuff))
            linebuff[newline_i] = '\0';
        if (get_first == 1)
        {
            bigint_inits(&val, linebuff);
            bigint_inits(&toadd, linebuff);
            get_first = 0;
        }
        else
        {
            bigint_sets(&toadd, linebuff);
            bigint_add(&val, &toadd);
        }
    }
    if (fp != stdin)
        fclose(fp);
    bigint_free(&toadd);

    timespec_get(&end, TIME_UTC);
    const long seconds_elapsed = end.tv_sec - start.tv_sec;
    const long nanosec_elapsed = end.tv_nsec - start.tv_nsec;
    const double elapsed_time = (nanosec_elapsed / 1000000000.0) + seconds_elapsed;

    fputs  ("Sum:               ", stdout);
    bigint_print(&val, -1);
    fputs("\nFirst 10 digits:   ", stdout);
    bigint_print(&val, 10);

    printf("\nElapsed time:      %.8fs\n", elapsed_time);
    printf  ("                   %lds %ldns\n", seconds_elapsed, nanosec_elapsed);
    bigint_free(&val);
    return 0;
}
