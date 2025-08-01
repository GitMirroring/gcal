#include <stdlib.h>

#include "../src/tailor.h"
#include "../src/common.h"
#if USE_RC
# include "../src/rc-defs.h"
#endif /* USE_RC */
#include "../src/globals.h"
#include "../src/hd-defs.h"
#include "../src/hd-use.h"
#if USE_RC
# include "../src/rc-utils.h"
#endif /* USE_RC */
#include "../src/utils.h"

#include <check.h>

START_TEST(test_gcal_dummy)
{
    ck_assert_int_eq(254, 254);
}
END_TEST

START_TEST(test_utils_my_atoi)
{
    int number = 8;
    char *snumber = "8";
    
    ck_assert_int_eq(number, my_atoi(snumber));
    ck_assert_int_eq(number, my_atoi(snumber));
}
END_TEST

Suite *gcal_suite_utils(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("GCAL.utils");

    /* Core test case */
    tc_core = tcase_create("utils");

    tcase_add_test(tc_core, test_gcal_dummy);
    tcase_add_test(tc_core, test_utils_my_atoi);

    suite_add_tcase(s, tc_core);

    return s;
}

