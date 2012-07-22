/* Ex 5-5: Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n characters of their argument
 * strings. For example, strncpy(s,t,n) copies at most n characters of t to s.
 * Full descriptions are in Appendix B */

#include <stdlib.h>
#include "minunit.h"

char *mystrncpy(char *destination, char *source, size_t num)
{
    size_t i;

    // copy source to destination
    for(i = 0; i < num && source[i] != '\0'; i++) {
        destination[i] = source[i];
    }

    // if source has fewer than num characters
    if (i + 1 < num) {
        i++;
        // then pad with NULL
        for ( ; i < num; i++) {
            destination[i] = '\0';
        }
    }

    return destination;
}

char *mystrncat(char *destination, char *source, size_t num)
{
    int i;

    // find end of destination
    for (i = 0; destination[i] != '\0'; i++) { }

    // copy source to destination, starting at end of destination
    mystrncpy(destination+i, source, num);

    return destination;
}

int mystrncmp(char *one, char *two, size_t num)
{
    size_t i;

    for (i = 0; i < num && one[i] != '\0' && two[i] != '\0'; i++) {
        if (one[i] != two[i]) {
            return one[i] - two[i];
        }
    }

    return 0;
}

char *test_strncpy_same_size()
{
    char string[] = "Hello";

    /* could use 6 instead but I'd rather be explicit and visible about this,
     * makes it harder to miss. So in this file I will do the following: */
    mystrncpy(string, "World", 5);
    string[5] = '\0'; 
    mu_assert(strncmp(string, "World", 5) == 0, "String should equal 'World'");

    return NULL;
}

char *test_strncpy_big_to_small()
{
    char string[] = "tiny";

    mystrncpy(string, "larger", 4);
    string[4] = '\0';
    mu_assert(strncmp(string, "larg", 4) == 0, "String should equal 'larg'");

    return NULL;
}

char *test_strncpy_small_to_big()
{
    char string[] = "larger";
    
    mystrncpy(string, "tiny", 4);
    string[4] = '\0';
    mu_assert(strncmp(string, "tiny", 4) == 0, "String should equal 'tiny'");

    mystrncpy(string, "tiny", 6);
    string[6] = '\0';
    mu_assert(strncmp(string, "tiny", 4) == 0, "String should equal 'tiny'");

    return NULL;
}

char *test_strncat()
{
    char string[12];

    strncpy(string, "Hello", 5);
    string[5] = '\0';
    mystrncat(string, " World", 6);

    debug("%s", string);
    mu_assert(strncmp(string, "Hello World", 11) == 0, "String should equal 'Hello World'");

    return NULL;
}

char *test_strncat_empty_strings()
{
    char string1[6];

    strncpy(string1, "Hello", 5);
    string1[5] = '\0';
    mystrncat(string1, "", 0);

    debug("%s", string1);
    mu_assert(strncmp(string1, "Hello", 5) == 0, "String should equal 'Hello'");

    char string2[6];

    string2[0] = '\0';
    mystrncat(string2, "World", 5);

    debug("%s", string2);
    mu_assert(strncmp(string2, "World", 5) == 0, "String should equal 'World'");

    return NULL;
}

char *test_strcmp_equal() 
{
    mu_assert(mystrncmp("Hello World", "Hello World", 11) == 0, "Should equal 0")
    mu_assert(mystrncmp("Hello Canada", "Hello England", 6) == 0, "Should equal 0")

    return NULL;
}

char *test_strcmp_less_than() 
{
    mu_assert(mystrncmp("Hello Canada", "Hello England", 11) < 0, "Should be < 0")

    return NULL;
}

char *test_strcmp_greater_than() 
{
    mu_assert(mystrncmp("Hello England", "Hello Canada", 11) > 0, "Should be > 0")

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_strncpy_same_size);
    mu_run_test(test_strncpy_big_to_small);
    mu_run_test(test_strncpy_small_to_big);

    mu_run_test(test_strncat);
    mu_run_test(test_strncat_empty_strings);

    mu_run_test(test_strcmp_equal);
    mu_run_test(test_strcmp_less_than);
    mu_run_test(test_strcmp_greater_than);

    return NULL;
}

RUN_TESTS(all_tests);
