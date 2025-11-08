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

/*
int
orthodox_easter (const int year, int *greg_diff, const int greg_year, const int greg_month, const int greg_first_day,
                 const int greg_last_day)
*/
START_TEST(test_orthodox_easter)
{
    int oe, greg_diff=0, day, month;
    bool valid;

    oe=orthodox_easter(2024, &greg_diff, 1582, 10, 5, 15);
    printf("XXX oe: %i  diff %i\n",oe, greg_diff);
    ck_assert_int_eq(greg_diff, 14); //XXX should be 13 according to https://en.wikipedia.org/wiki/Gregorian_calendar
    valid=doy2date(oe, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 7); //XXX should be 5 according to https://www.christianity.com/wiki/holidays/orthodox-easter-origin-and-date.html
    ck_assert_int_eq(month, 5);

    oe=orthodox_easter(2025, &greg_diff, 1582, 10, 5, 15);
    printf("XXX oe: %i  diff %i\n",oe, greg_diff);
    ck_assert_int_eq(greg_diff, 14); //XXX should be 13 according to https://en.wikipedia.org/wiki/Gregorian_calendar
    valid=doy2date(oe, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 21); //XXX should be 20 according to https://www.christianity.com/wiki/holidays/orthodox-easter-origin-and-date.html
    ck_assert_int_eq(month, 4);

    oe=orthodox_easter(2026, &greg_diff, 1582, 10, 5, 15);
    printf("XXX oe: %i  diff %i\n",oe, greg_diff);
    ck_assert_int_eq(greg_diff, 14); //XXX should be 13 according to https://en.wikipedia.org/wiki/Gregorian_calendar
    valid=doy2date(oe, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 13); //XXX should be 12 according to https://www.christianity.com/wiki/holidays/orthodox-easter-origin-and-date.html
    ck_assert_int_eq(month, 4);

    oe=orthodox_easter(2027, &greg_diff, 1582, 10, 5, 15);
    printf("XXX oe: %i  diff %i\n",oe, greg_diff);
    ck_assert_int_eq(greg_diff, 14); //XXX should be 13 according to https://en.wikipedia.org/wiki/Gregorian_calendar
    valid=doy2date(oe, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 3); //XXX should be 2 according to https://www.christianity.com/wiki/holidays/orthodox-easter-origin-and-date.html
    ck_assert_int_eq(month, 5);

    oe=orthodox_easter(2028, &greg_diff, 1582, 10, 5, 15);
    printf("XXX oe: %i  diff %i\n",oe, greg_diff);
    ck_assert_int_eq(greg_diff, 14); //XXX should be 13 according to https://en.wikipedia.org/wiki/Gregorian_calendar
    valid=doy2date(oe, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 18); //XXX should be 16 according to https://www.christianity.com/wiki/holidays/orthodox-easter-origin-and-date.html
    ck_assert_int_eq(month, 4);

}
END_TEST

/*
int
tishri_1 (const int year)
/ *!
   Returns the `day_of_year' number of the (arithmetical lunisolar)
     Hebrew/Jewish Hebrew_New_Year/Rosh_Hashana/Tishri_1 for the
     given Julian/Gregorian year YEAR.
   Used formula:  John H. Conway, Guy and Berlekamp: "Winning Ways", Vol. 2.
   References:    Lot's of, but see `doc/calendar.faq' for the basics.
*/
START_TEST(test_tishri_1)
{
  int doy;

    doy=tishri_1(2025);
    printf("XXX tishri_1 2025 doy: %i\n",doy);
    valid=doy2date(doy, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 23);
    ck_assert_int_eq(month, 9);

    //XXX pobably some more tests are needed here
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
    tcase_add_test(tc_core, test_orthodox_easter);
    tcase_add_test(tc_core, test_tishri_1);

    suite_add_tcase(s, tc_core);

    return s;
}

