#include "../config.h"
#include <check.h>
#include <stdlib.h>

#include "../src/tailor.h"
#include <ctype.h>
#include "../src/common.h"

#include "../src/globals.h"
#include "../src/hd-astro.h"
#include "../src/hd-defs.h"
#include "../src/rc-defs.h"
#include "../src/hd-data.h"
#include "../src/tty.h"
#include "../src/utils.h"
#include "../src/hd-use.h"
#include "../src/hd-data1.h"

/*
these functions are defined in a different check_* file and can be used here as well
*/
int length_of_hd_table();
int length_of_cc_holidays_table();

START_TEST(test_hdy)
{
    int tableLength, hd_elems=0, easter;
    Bool init_data=true;
    int fday, i, j, count=0;

    int cc_holidays_length = length_of_cc_holidays_table();
    ck_assert_int_ne(cc_holidays_length, 0); // cc_holidays_length should be around 354

    tableLength=length_of_hd_table(); ck_assert_int_eq(tableLength, 0);

    fiscal_month=1;
    easter = knuth_easter_formula (year);
    if (fiscal_month > MONTH_MIN)
        {
          fday = day_of_year (DAY_MIN, fiscal_month, year);
          j = is_leap_year;
          i = year;
        }

    printf("XXX before au_hdy: init_data: %i  hd_elemes: %i\n",init_data, hd_elems);
    au_hdy (&init_data, true, easter, 2025, &hd_elems, fday, count);
    printf("XXX au_hdy: init_data: %i  hd_elemes: %i\n",init_data, hd_elems);

}
END_TEST

Suite *gcal_suite_hd_data(char *testname)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create(testname);

    /* Core test case */
    tc_core = tcase_create(testname);

    tcase_add_test(tc_core, test_hdy);

    suite_add_tcase(s, tc_core);

    return s;
}

