#include "../config.h"
#include <check.h>
#include <stdlib.h>

#include "../src/tailor.h"
#include <ctype.h>
#include "../src/common.h"

#include "../src/globals.h"
#include "../src/rc-defs.h"
#include "../src/rc-use.h"

START_TEST(test_settings)
{
    //XXX maybe check other variables that have been set in rc_use()
    ck_assert_pstr_ne(rc_bio_emo_lit,  _("Emo"));

    rc_use();

    ck_assert_pstr_eq(rc_bio_emo_lit,  _("Emo"));
}
END_TEST

Suite *gcal_suite_rc_use(char *testname)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create(testname);

    /* Core test case */
    tc_core = tcase_create(testname);

    tcase_add_test(tc_core, test_settings);

    suite_add_tcase(s, tc_core);

    return s;
}

