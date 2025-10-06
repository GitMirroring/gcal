#include "../config.h"
#include <check.h>
#include <stdlib.h>


START_TEST(test_gcal_dummy)
{
    ck_assert_int_eq(254, 254);
}
END_TEST

Suite *gcal_suite_print(char *testname)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create(testname);

    /* Core test case */
    tc_core = tcase_create(testname);

    tcase_add_test(tc_core, test_gcal_dummy);

    suite_add_tcase(s, tc_core);

    return s;
}

