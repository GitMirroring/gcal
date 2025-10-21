#include "../config.h"
#include <check.h>
#include <stdlib.h>

#include "../src/tailor.h"
#include <ctype.h>
#include "../src/common.h"

#include "../src/globals.h"
#include "../src/hd-astro.h"
#include "../src/hd-defs.h"
#include "../src/hd-data.h"
#include "../src/tty.h"
#include "../src/utils.h"
#include "../src/hd-use.h"

/*
int
eval_holiday (int day, const int month, const int year, const int wd, const Bool forwards)
/ *!
   Detects first (FORWARDS==TRUE) or last (FORWARDS==FALSE) appearance
     of weekday `wd' in given date starting the search at `day'
     and returns the day number of `wd' in month.
*/


START_TEST(test_eval_holiday)
{
    int eh;

    // e.g. https://www.kalender-365.eu/kalender-2011.html

    // first monday of year is 3.
    eh=eval_holiday(1, 1, 2011, 1, true);
    ck_assert_int_eq(eh, 3);
    // last monday of january in year is 3.
    eh=eval_holiday(31, 1, 2011, 1, false);
    ck_assert_int_eq(eh, 31);

    // first tuesday in february of year is 1.
    eh=eval_holiday(1, 2, 2011, 2, true);
    ck_assert_int_eq(eh, 1);
    // last tuesday in february of year is 22.
    eh=eval_holiday(28, 2, 2011, 2, false);
    ck_assert_int_eq(eh, 22);

    // first wednesday in march of year is 2.
    eh=eval_holiday(1, 3, 2011, 3, true);
    ck_assert_int_eq(eh, 2);
    // last wednesday in march of year is 3.
    eh=eval_holiday(31, 3, 2011, 3, false);
    ck_assert_int_eq(eh, 30);

    // first thursday in april of year is 7.
    eh=eval_holiday(1, 4, 2011, 4, true);
    ck_assert_int_eq(eh, 7);
    // last thursday in april of year is 28.
    eh=eval_holiday(31, 4, 2011, 4, false); // april has only 30 days, is this ok? I think so
    ck_assert_int_eq(eh, 28);

    // first friday in may of year is 6.
    eh=eval_holiday(1, 5, 2011, 5, true);
    ck_assert_int_eq(eh, 6);
    // last friday in may of year is 27.
    eh=eval_holiday(31, 5, 2011, 5, false);
    ck_assert_int_eq(eh, 27);

    // first saturday in june of year is 4.
    eh=eval_holiday(1, 6, 2011, 6, true);
    ck_assert_int_eq(eh, 4);
    // last saturday in june of year is 25.
    eh=eval_holiday(31, 6, 2011, 6, false);
    ck_assert_int_eq(eh, 25);

    // first sunday in july of year is 3.
    eh=eval_holiday(1, 7, 2011, 7, true);
    ck_assert_int_eq(eh, 3);
    // last sunday in july of year is 31.
    eh=eval_holiday(31, 7, 2011, 7, false);
    ck_assert_int_eq(eh, 31);


}
END_TEST

Suite *gcal_suite_hd_use(char *testname)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create(testname);

    /* Core test case */
    tc_core = tcase_create(testname);

    tcase_add_test(tc_core, test_eval_holiday);

    suite_add_tcase(s, tc_core);

    return s;
}

