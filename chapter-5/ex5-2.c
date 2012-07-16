/* Ex 5-2: Write getfloat, the floating-point analog of getint. What type does
 * getfloat return as its function value? */

#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include "minunit.h"
#include "getch.h"

/* getint: get next integer from input into *pn */
int getfloat(float *pn)
{
    int c, sign, exp;

    do {
        c = getch();
    } while(isspace(c));

    if(!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c) && c != '.') {
            ungetch(c);
            return 0;
        }
    }

    // before decimal
    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * (*pn) + (c - '0');
    }

    // after decimal
    if (c == '.') {
        c = getch();
        for (exp = 1; isdigit(c); c = getch(), exp++) {
            *pn = *pn + ((c - '0') * pow(.1, exp));
        }
    }

    *pn *= sign;

    if (c != EOF) {
        ungetch(c);
    }

    return c;
}

char *test_whole_number()
{
    int rc = 0;
    float number = 0;

    int input[] = {'1', '2', '3', EOF};
    setInput(input, 4);
    rc = getfloat(&number);

    mu_assert(rc == EOF, "Expected result to be EOF");
    mu_assert(number == 123, "Expected number to be 123");

    return NULL;
}

char *test_float()
{
    int rc = 0;
    float number = 0;

    int input[] = {'3', '2', '1', '.', '4', '5', EOF};
    setInput(input, 7);
    rc = getfloat(&number);

    debug("%f", number);
    mu_assert(rc == EOF, "Expected result to be EOF");
    mu_assert(number > 321.449 && number < 321.451, "Expected number to be 321.45");

    return NULL;
}

char *test_sign_then_float()
{
    int rc = 0;
    float number = 0;

    int input[] = {'+', '3', '2', '1', '.', '4', '5', EOF};
    setInput(input, 8);
    rc = getfloat(&number);

    mu_assert(rc == EOF, "Expected result to be EOF");
    mu_assert(number > 321.449 && number < 321.451, "Expected number to be 321.45");

    return NULL;
}

char *test_sign_then_char()
{
    int rc = 0;
    float number = 0;

    int input[] = {'-', 'f'};
    setInput(input, 2);
    rc = getfloat(&number);

    mu_assert(rc == 0, "Expected result 'not a number' (0)");

    return NULL;
}

char *test_positive_return_code()
{
    int rc = 0;
    float number = 0;

    int input[] = {'-', '1', 'f'};
    setInput(input, 3);
    rc = getfloat(&number);

    mu_assert(rc > 0, "Expected positive return code.");
    mu_assert(number == -1, "Expected number to be -1");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_whole_number);
    mu_run_test(test_float);
    mu_run_test(test_sign_then_float);
    mu_run_test(test_sign_then_char);
    mu_run_test(test_positive_return_code);

    freeInput();
    return NULL;
}

RUN_TESTS(all_tests);
