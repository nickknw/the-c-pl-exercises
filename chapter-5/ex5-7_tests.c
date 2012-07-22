#include "benchmark.h"
#include "getch.h"
#include "bookgetline.h"
#include "minunit.h"
#include "dbg.h"
#include "ex5-7.h"

#define MAXLINES 5000

char *lineptr[MAXLINES];

struct MemoryBuffer {
    int *buffer;
    long size;
};

/* returns size of file */
struct MemoryBuffer read_file_into_buffer(char *filename)
{
    FILE *file = fopen(filename, "r");
    check(file, "Couldn't open file");

    // obtain file size
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    // allocate memory for the file
    int *buffer = (int*) malloc(sizeof(int) * size);
    check(buffer, "Memory error");

    // copy file into buffer
    int c = fgetc(file), i = 0;
    for(i = 0; i < size && c != EOF; i++) {
        c = fgetc(file);
        buffer[i] = c;
    }

    fclose(file);

    struct MemoryBuffer result = { .buffer=buffer, .size=size };
    return result;

error:
    fclose(file);
    struct MemoryBuffer err = { .buffer=NULL, .size=0 };
    return err;

}

char *test_basic_functionality()
{
    int input[] = { 
        'z', 'e', '\n',
        'b', 'e', '\n',
        'a', 'e', '\n',
        'j', 'o', '\n',
        'j', 'a', '\n',
        EOF 
    };
    char *sortedInput[] = {
        "ae",
        "be",
        "ja",
        "jo",
        "ze"
    };

    setInput(input, 16);

    int nlines = readlines(lineptr, MAXLINES, mygetline);

    mu_assert(nlines >= 0, "error: input too big to sort");

    bookqsort(lineptr, 0, nlines-1);

    int i;
    for (i = 0; i < nlines; i++) {
        mu_assert(strcmp(lineptr[i], sortedInput[i]) == 0, "Sort out of order");
    }

    freeInput();
    return NULL;
}

char *test_bookreadlines_performance()
{
    struct MemoryBuffer membuf = read_file_into_buffer("ex5-7_data.txt");
    mu_assert(membuf.size > 0 && membuf.buffer != NULL, "Error reading file");

    setInput(membuf.buffer, membuf.size);

    // now do the performance testing part
    double start = get_time();
    int nlines = readlines(lineptr, MAXLINES, mygetline);
    double finish = get_time();

    printf("\nBOOKREADLINES\n");
    printf("Time: %f\n", finish - start);
    printf("Number of lines: %d\n", nlines);
    printf("Size: %lu\n", membuf.size);

    freeInput();
    free(membuf.buffer);

    return NULL;
}

char *test_newreadlines_performance()
{
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_basic_functionality);
    mu_run_test(test_bookreadlines_performance);

    return NULL;
}

RUN_TESTS(all_tests);
