#include "../config.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/tailor.h"
#include "../src/common.h"
#include "../src/globals.h"
#include "../src/utils.h"
#include "../src/tty.h"

START_TEST(test_print_text)
{
//TODO check with USE_PAGER defined
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE *f;
    #define OUTPUTFILE "test_print_text.output"
    #define LINE1 "hurzilein"
    #define LINE2 "blubber opt blah"

    f=fopen(OUTPUTFILE, "w");

    sprintf (s1, _(LINE1));
    print_text (f, s1);

    sprintf (s1, _(LINE2));
    print_text (f, s1);

    fclose(f);

    f=fopen(OUTPUTFILE, "r");
    read = getline(&line, &len, f);
    line[strlen(line)-1]='\0'; // we dont't compare with newline
    ck_assert_str_eq(LINE1, line);
    read = getline(&line, &len, f);
    line[strlen(line)-1]='\0'; // we dont't compare with newline
    ck_assert_str_eq(LINE2, line);
}
END_TEST

START_TEST(test_get_tty_hls)
{
    const char *sequence = NULL;
    get_tty_hls (sequence);

    printf("XXX sequence: %s\n",sequence);
}
END_TEST

START_TEST(test_get_tty_scr_size)
{
    int rows, cols;

    const char *sequence = NULL;
    get_tty_scr_size (&rows, &cols);

    // it needs to be non zero
    ck_assert_int_ne(rows, 0);
    ck_assert_int_ne(cols, 0);
}
END_TEST

Suite *gcal_suite_tty(char *testname)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create(testname);

    /* Core test case */
    tc_core = tcase_create(testname);

    tcase_add_test(tc_core, test_print_text);
    tcase_add_test(tc_core, test_get_tty_hls);
    tcase_add_test(tc_core, test_get_tty_scr_size);
    /* other functions in tty.c are static */

    suite_add_tcase(s, tc_core);

    return s;
}
