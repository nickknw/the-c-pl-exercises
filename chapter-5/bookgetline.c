#include <stdio.h>
#include "getch.h"
#include "bookgetline.h"

int bookgetline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}

int mygetline(char s[], int lim)
{
    int c, i;

    /* I changed the call from getchar() to getch() for testing purposes */
    for (i = 0; i < lim - 1 && (c = getch()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}
