/* Ex 5-7: Rewrite readlines to store lines in an array supplied by main, rather
 * than calling alloc to maintain storage. How much faster is the program? */

#include <stdio.h>
#include <string.h>
#include "alloc.h"
#include "benchmark.h"
#include "ex5-7.h"

#define MAXLEN 1000

int readlines(char *lineptr[], int maxlines, int (getlinefunc)(char[], int))
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = (*getlinefunc)(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            //printf("nlinesloop: %d\n", nlines);
            //printf("len: %d\n", len);
            //printf("p: %p\n", p);
            return -1;
        } else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p,  line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
}

int newreadlines(char *lineptr[], int maxlines, int (getlinefunc)(char[], int))
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = (*getlinefunc)(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p,  line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}

void bookqsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right) {
        return;
    }

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    bookqsort(v, left, last-1);
    bookqsort(v, last+1, right);
}

void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
