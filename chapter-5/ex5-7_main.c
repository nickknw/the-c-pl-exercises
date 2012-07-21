#include <stdio.h>
#include "ex5-7.h"
#include "bookgetline.h"

#define MAXLINES 5000

char *lineptr[MAXLINES];

int main(int argc, char *argv[])
{
    int nlines;

    if ((nlines = readlines(lineptr, MAXLINES, bookgetline)) >= 0) {
        bookqsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

