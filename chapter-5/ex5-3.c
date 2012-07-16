/* Ex 5-3: Write a pointer version of the function strcat that we showed in
 * Chapter 2: strcat(s,t) copies the string t to the end of s. */

#include <string.h>
#include "minunit.h"
#include "dbg.h"

void mystrcat(char *s, char *t)
{
    int i, j;

    i = j = 0;
    while (*(s+i) != '\0') /* find end of s */
        i++;
    while ((*(s+i) = *(t+j)) != '\0') {
        i++;
        j++;
    }
}

char *test_strcat()
{
    char string[12];

    strcpy(string, "Hello");
    mystrcat(string, " World");

    mu_assert(strcmp(string, "Hello World") == 0, "String does not equal 'Hello World'");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_strcat);

    return NULL;
}

RUN_TESTS(all_tests);
