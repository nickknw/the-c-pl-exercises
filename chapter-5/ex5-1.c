/* Ex 5-1: As written, getint treats a + or - not followed by a digit as a valid
 * representation of zero. Fix it to push such a character back on the input. */

#include <ctype.h>
#include <stdio.h>
#include "minunit.h"
#include "getch.h"

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch())) /* skip whitespace */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            ungetch(c);
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

char *test_number()
{
    int rc = 0, number = 0;

    int input[] = {'1', '2', '3', EOF};
    setInput(input, 4);
    rc = getint(&number);

    mu_assert(number == 123, "Expected number to be 123");

    return NULL;
}

char *test_sign_then_number()
{
    int rc = 0, number = 0;

    int input[] = {'-', '3', '2', '5', EOF};
    setInput(input, 5);
    rc = getint(&number);

    mu_assert(number == -325, "Expected number to be -325");

    return NULL;
}

char *test_sign_then_char()
{
    int rc = 0, number = 0;

    int input[] = {'+', 'f'};
    setInput(input, 2);
    rc = getint(&number);

    mu_assert(rc == 0, "Expected result 'not a number' (0)");
    
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_number);
    mu_run_test(test_sign_then_number);
    mu_run_test(test_sign_then_char);

    return NULL;
}

RUN_TESTS(all_tests);
