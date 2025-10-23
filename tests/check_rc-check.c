#include "../config.h"
#include <check.h>
#include <stdlib.h>

/*XXX
void
rc_check (char *line_buffer, const char *filename, const long line_number, const int line_length, int *rc_elems, const int day, const int ed,
          const int wd)
/ *
   Checks whether a single line of a resource file resp.,
     eternal holiday must be displayed.
*/


START_TEST(test_rc_check)
{
    ck_assert_int_eq(254, 254);
    // prepare test case
    // do test
}
END_TEST

Suite *gcal_suite_rc_check(char *testname)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create(testname);

    /* Core test case */
    tc_core = tcase_create(testname);

    tcase_add_test(tc_core, test_rc_check);

    suite_add_tcase(s, tc_core);

    return s;
}

