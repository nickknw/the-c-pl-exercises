/* Ex 5-4: Write the function strend(s,t), which returns 1 if the string t
 * occurs at the end of the string s, and zero otherwise. */

#include "minunit.h"

int strend(char *s, char *t)
{
    int i, j;

    // find the end of s
    for(i = 0; s[i] != '\0'; i++) { }

    // find the end of t
    for(j = 0; t[j] != '\0'; j++) { }

    // starting at those positions, walk backward and compare until we reach 0.
    // if a mismatch is found return 0 immediately
    while(i >= 0 && j >= 0) {
        if (s[i] != t[j]) {
            return 0;
        }
        i--;
        j--;
    }

    return 1;
}

char *test_strend()
{
    mu_assert(strend("Hello World", "World") == 1, "Expected 1");
    mu_assert(strend("Hello World", "Worl") == 0, "Expected 0");
    
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_strend);
    
    return NULL;
}

RUN_TESTS(all_tests);
