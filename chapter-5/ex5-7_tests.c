#include "ex5-7.h"
#include "getch.h"
#include "bookgetline.h"
#include "minunit.h"

#define MAXLINES 5000

char *lineptr[MAXLINES];

char *test_basic_functionality()
{
    int nlines;

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

    nlines = readlines(lineptr, MAXLINES, mygetline);

    mu_assert(nlines >= 0, "error: input too big to sort");

    bookqsort(lineptr, 0, nlines-1);

    int i;
    for (i = 0; i < nlines; i++) {
        mu_assert(strcmp(lineptr[i], sortedInput[i]) == 0, "Sort out of order");
    }

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_basic_functionality);

    return NULL;
}

RUN_TESTS(all_tests);
