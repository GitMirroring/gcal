#include "../config.h"
#include <check.h>
#include <stdlib.h>

#include "../src/tailor.h"
#include "../src/common.h"
#include "../src/globals.h"
#include "../src/utils.h"

#include "../src/rc-defs.h"
#include "../src/rc-utils.h"

START_TEST(test_valid_day)
{
    Bool rc;

    rc=rc_valid_day("", 1, 1, 2025); ck_assert(rc); 	// no exclusion
    rc=rc_valid_day("",30, 2, 2025); ck_assert(rc);     // no exclusion
    rc=rc_valid_day("V", 1, 1, 2025); ck_assert(rc); 
    rc=rc_valid_day("v", 1, 1, 2025); ck_assert(!rc); 
    rc=rc_valid_day("C",24, 9, 2025); ck_assert(rc); 

}
END_TEST

Suite *gcal_suite_rc_utils(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("GCAL.rc-utils");

    /* Core test case */
    tc_core = tcase_create("rc-utils");

    tcase_add_test(tc_core, test_valid_day);

    suite_add_tcase(s, tc_core);

    return s;
}

