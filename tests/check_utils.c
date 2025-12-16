#include "../config.h"
#include <check.h>
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

const char *dflt_month_name(const int month);

#include <check.h>

START_TEST(test_utils_my_atoi)
{
    char *snumber0 = "0";
    char *snumber000 = "000";
    char *snumber8 = "8";
    char *snumber999 = "999";
    char *snumber555555555555 = "555555555555";
    char *snumberm1 = "-1";
    char *snumberm100 = "-100";
    
    ck_assert_int_eq(0, my_atoi(snumber0));
    ck_assert_int_eq(0, my_atoi(snumber000));
    ck_assert_int_eq(8, my_atoi(snumber8));
    ck_assert_int_eq(999, my_atoi(snumber999));
    ck_assert_int_eq(0, my_atoi(snumber555555555555));            // number is longer than len_year_max
    ck_assert_int_eq(0, my_atoi(snumberm1));                      // negative numbers are not allowed
    ck_assert_int_eq(0, my_atoi(snumberm100));                    // negative numbers are not allowed
    ck_assert_int_ne(555555555555, my_atoi(snumber555555555555)); // number is longer than len_year_max
    ck_assert_int_ne(-1, my_atoi(snumberm1));                     // negative numbers are not allowed
    ck_assert_int_ne(-100, my_atoi(snumberm100));                 // negative numbers are not allowed
}
END_TEST

START_TEST(test_utils_julian_gregorian_diff)
{
    ck_assert_int_eq(julian_gregorian_diff( 1,  1, 1970), 13);
    ck_assert_int_eq(julian_gregorian_diff(29,  2, 2000), 13);
    ck_assert_int_eq(julian_gregorian_diff(29,  2, 2004), 13);
    ck_assert_int_eq(julian_gregorian_diff( 1,  1, 1200),  0);
    ck_assert_int_eq(julian_gregorian_diff( 4, 10, 1582),  0);
    ck_assert_int_eq(julian_gregorian_diff(14, 10, 1582),  0);
    ck_assert_int_eq(julian_gregorian_diff(15, 10, 1582), 10);
    ck_assert_int_eq(julian_gregorian_diff(28,  2, 1700), 10);
//XXX there seems to be a bug!?
//    ck_assert_int_eq(julian_gregorian_diff( 1,  3, 1700), 11);
//    ck_assert_int_eq(julian_gregorian_diff( 1,  4, 1700), 11);
//    ck_assert_int_eq(julian_gregorian_diff( 1,  5, 1700), 11);
//    ck_assert_int_eq(julian_gregorian_diff( 1,  6, 1700), 11);
//    ck_assert_int_eq(julian_gregorian_diff( 1,  7, 1700), 11);
//    ck_assert_int_eq(julian_gregorian_diff( 1,  8, 1700), 11);
//    ck_assert_int_eq(julian_gregorian_diff( 1,  9, 1700), 11);
//    ck_assert_int_eq(julian_gregorian_diff( 1, 10, 1700), 11);
//    ck_assert_int_eq(julian_gregorian_diff( 1, 11, 1700), 11);
//    ck_assert_int_eq(julian_gregorian_diff( 1, 12, 1700), 11);
    ck_assert_int_eq(julian_gregorian_diff( 1,  1, 1701), 11);
    ck_assert_int_eq(julian_gregorian_diff(28,  2, 1800), 11);
//    ck_assert_int_eq(julian_gregorian_diff( 1,  3, 1800), 12);
    ck_assert_int_eq(julian_gregorian_diff(28,  2, 1900), 12);
//    ck_assert_int_eq(julian_gregorian_diff( 1,  3, 1900), 13);
    ck_assert_int_eq(julian_gregorian_diff(28,  2, 2100), 13);
//    ck_assert_int_eq(julian_gregorian_diff( 1,  3, 2100), 14);
    ck_assert_int_eq(julian_gregorian_diff(28,  2, 2200), 14);
}
END_TEST

START_TEST(test_utils_knuth_easter_formula)
{
     ck_assert_int_eq(knuth_easter_formula( 463), 111);
     ck_assert_int_eq(knuth_easter_formula( 464), 103);
     ck_assert_int_eq(knuth_easter_formula(1200), 100);
     //XXX does not always work?? : ck_assert_int_eq(knuth_easter_formula(2025), 110);
}
END_TEST

START_TEST(test_utils_doy2date)
{
  Bool valid;
  int day, month;

  valid=doy2date(1, 0, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day, 1);
  ck_assert_int_eq(month, 1);

  valid=doy2date(31, 0, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day, 31);
  ck_assert_int_eq(month, 1);

  valid=doy2date(60, 0, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day, 1);
  ck_assert_int_eq(month, 3);

  valid=doy2date(60, 1, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day, 29);
  ck_assert_int_eq(month, 2);

  valid=doy2date(61, 1, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day, 1);
  ck_assert_int_eq(month, 3);

  valid=doy2date(74, 0, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day, 15);
  ck_assert_int_eq(month, 3);

  valid=doy2date(105, 0, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day, 15);
  ck_assert_int_eq(month, 4);

  valid=doy2date(136, 1, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day, 15);
  ck_assert_int_eq(month, 5);

  valid=doy2date(166, 0, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day, 15);
  ck_assert_int_eq(month, 6);

  valid=doy2date(185, 0, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day,  4);
  ck_assert_int_eq(month, 7);

  valid=doy2date(228, 1, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day, 15);
  ck_assert_int_eq(month, 8);

  valid=doy2date(258, 0, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day, 15);
  ck_assert_int_eq(month, 9);

  valid=doy2date(288, 0, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day, 15);
  ck_assert_int_eq(month, 10);

  valid=doy2date(320, 1, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day, 15);
  ck_assert_int_eq(month, 11);

  valid=doy2date(359, 0, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day, 25);
  ck_assert_int_eq(month, 12);

  valid=doy2date(366, 1, &day, &month); ck_assert(valid);
  ck_assert_int_eq(day, 31);
  ck_assert_int_eq(month, 12);

  day=77; month=22;
  valid=doy2date(461, 1, &day, &month);
  ck_assert(!valid);
  ck_assert_int_eq(day, 77); //XXX in case of invalid doy, day and month don't change
  ck_assert_int_eq(month, 22); //XXX in case of invalid doy, day and month don't change
}
END_TEST

START_TEST(test_utils_weekday_of_date)
{
  // weekday_of_date returns 1...7 (1==mo, 2==tu...7==su)
  ck_assert_int_eq(weekday_of_date(  1,  1, 2025), 3);
  ck_assert_int_ne(weekday_of_date(  1,  1, 2025), 2);
  ck_assert_int_eq(weekday_of_date(  7, 11, 2000), 2);
  ck_assert_int_eq(weekday_of_date(  3,  5, 1950), 3);
  ck_assert_int_eq(weekday_of_date( 24, 12, 1800), 3);

  // XXX so what is the real weekday? This needs some more investigations
  //XXX ck_assert_int_eq(weekday_of_date( 27,  4, 1652), 2); // shall be 2 according to https://www.timeanddate.com/date/weekday.html?day=27&month=4&year=1652

  // according to https://www.timeanddate.com/date/weekday.html?day=4&month=10&year=1582  the weekday is Thursday = 4 <- same as gcal
  // according to https://www.timeanddate.com/date/weekday.html?day=15&month=10&year=1582 the weekday is Monday = 1 <- different from gcak
  // according to https://ahnenforschung-vhs-mosbach.de/wp/wp-content/uploads/2020/03/AK-Mosbach-Julian-Gregorianisch.pdf the 15.10.1582 is a Tuesday
  ck_assert_int_eq(weekday_of_date(  4, 10, 1582), 4);
  ck_assert_int_eq(weekday_of_date( 15, 10, 1582), 5);
  ck_assert_int_eq(weekday_of_date( 13, 10, 1439), 2);
}
END_TEST

// obtained from https://ahnenforschung-vhs-mosbach.de/wp/wp-content/uploads/2020/03/AK-Mosbach-Julian-Gregorianisch.pdf
// 	Julian			Gregorian
//	23. Sep	Thursday	03. Oct
//	24. Sep	Friday		04. Oct
//	25. Sep	Saturday	05. Oct
//	26. Sep	Sunday		06. Oct
//	27. Sep	Monday		07. Oct
//	28. Sep	Tuesday		08. Oct
//	29. Sep	Wednesday	09. Oct
//	30. Sep	Thursday	10. Oct
//	01. Oct	Friday		11. Oct
//	02. Oct	Saturday	12. Oct
//	03. Oct	Sunday		13. Oct
//	04. Oct	Monday		14. Oct <-
//	05. Oct	Tuesday		15. Oct
//	06. Oct	Wednesday	16. Oct
//	07. Oct	Thursday	17. Oct
//	08. Oct	Friday		18. Oct
//	09. Oct	Saturday	19. Oct
//	10. Oct	Sunday		20. Oct

START_TEST(test_utils_day_of_year)
{
  ck_assert_int_eq(day_of_year(  1,  1, 2025),   1);
  ck_assert_int_eq(day_of_year(  7, 11, 2000), 312);
  ck_assert_int_eq(day_of_year(  3,  5, 1950), 123);
  ck_assert_int_eq(day_of_year( 24, 12, 1800), 358);
  ck_assert_int_eq(day_of_year( 27,  4, 1652), 118);
  ck_assert_int_eq(day_of_year(  4, 10, 1582), 277);
  ck_assert_int_eq(day_of_year( 15, 10, 1582), 288); //XXX as the 04.10. is directly followed by the 15.10., shouldn't be there only one day between them?
  ck_assert_int_eq(day_of_year( 13, 10, 1439), 286);
}
END_TEST

START_TEST(test_utils_days_of_february)
{
  ck_assert_int_eq(days_of_february(   4), 28); //XXX find literatur that confirms this
  ck_assert_int_eq(days_of_february(2025), 28);
  ck_assert_int_eq(days_of_february(2020), 29);
  ck_assert_int_eq(days_of_february(2000), 29);
  ck_assert_int_eq(days_of_february(1900), 28);
  ck_assert_int_eq(days_of_february(1840), 29);
  ck_assert_int_eq(days_of_february(1800), 28);
  ck_assert_int_eq(days_of_february(1801), 28);
  ck_assert_int_eq(days_of_february(1804), 29);
}
END_TEST

START_TEST(test_utils_valid_date)
{
  ck_assert( valid_date(22, 11, 1965));
  ck_assert(!valid_date(30,  2, 2045));
  ck_assert(!valid_date(15, 19, 2045));
  ck_assert( valid_date(29, 02, 2024));
  ck_assert(!valid_date(29, 02, 2025));
}
END_TEST

START_TEST(test_utils_prev_date)
{
  int day, month, year;
  int doy, ndoy; /* Day Of Year / New Day Of Year */

  day=1; month=1; year=2025;
  doy=day_of_year(day, month, year);
  ck_assert(prev_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(doy, 1);
  ck_assert_int_eq(ndoy, 366); // previous year (=2024) is leap year

  day=1; month=1; year=2023;
  doy=day_of_year(day, month, year);
  ck_assert(prev_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(doy, 1);
  ck_assert_int_eq(ndoy, 365); // previous year (=2022) is no leap year

  day=27; month=5; year=2022;
  doy=day_of_year(day, month, year);
  ck_assert(prev_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(doy-1, ndoy);

  day=1; month=3; year=2024;
  doy=day_of_year(day, month, year);
  ck_assert(prev_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(doy-1, ndoy);
  ck_assert_int_eq(day, 29);

  day=1; month=3; year=2023;
  doy=day_of_year(day, month, year);
  ck_assert(prev_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(doy-1, ndoy);
  ck_assert_int_eq(day, 28);

  day=16; month=10; year=1582;
  doy=day_of_year(day, month, year);
  ck_assert(prev_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(doy-1, ndoy);

  day=15; month=10; year=1582;
  doy=day_of_year(day, month, year);
  ck_assert(!prev_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(doy-1-10, ndoy);
  ck_assert_int_eq(day, 4);

  day=10; month=10; year=1582;
  doy=day_of_year(day, month, year);
  ck_assert(!prev_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(ndoy,277);
  ck_assert_int_eq(day, 4);

  day=5; month=10; year=1582;
  doy=day_of_year(day, month, year);
  ck_assert(!prev_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(doy-1, ndoy);
}
END_TEST

START_TEST(test_utils_next_date)
{
  int day, month, year;
  int doy, ndoy; /* Day Of Year / New Day Of Year */

  day=31; month=12; year=2024;
  doy=day_of_year(day, month, year);
  ck_assert(next_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(doy, 366);
  ck_assert_int_eq(ndoy, 1);

  day=27; month=5; year=2022;
  doy=day_of_year(day, month, year);
  ck_assert(next_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(doy+1, ndoy);

  day=28; month=2; year=2024;
  doy=day_of_year(day, month, year);
  ck_assert(next_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(doy+1, ndoy);
  ck_assert_int_eq(day, 29);

  day=28; month=2; year=2023;
  doy=day_of_year(day, month, year);
  ck_assert(next_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(doy+1, ndoy);
  ck_assert_int_eq(day, 1);

  day=3; month=10; year=1582;
  doy=day_of_year(day, month, year);
  ck_assert(next_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(doy+1, ndoy);

  day=4; month=10; year=1582;
  doy=day_of_year(day, month, year);
  ck_assert(!next_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(doy+1+10, ndoy);
  ck_assert_int_eq(day, 15);

  day=10; month=10; year=1582;
  doy=day_of_year(day, month, year);
  ck_assert(!next_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(ndoy,288);
  ck_assert_int_eq(day, 15);

  day=5; month=10; year=1582;
  doy=day_of_year(day, month, year);
  ck_assert(!next_date(&day, &month, &year));
  ndoy=day_of_year(day, month, year);
  ck_assert_int_eq(doy+1+9, ndoy);
}
END_TEST

START_TEST(test_utils_week_number)
{
  ck_assert_int_eq(week_number( 31, 12, 2020, true, 1), -53);
  ck_assert_int_eq(week_number(  1,  1, 2021, true, 1), -53);
  ck_assert_int_eq(week_number(  2,  1, 2021, true, 1), -53);
  ck_assert_int_eq(week_number(  3,  1, 2021, true, 1), -53);
  ck_assert_int_eq(week_number(  4,  1, 2021, true, 1),   1);
  ck_assert_int_eq(week_number(  1,  1, 2022, true, 1), -52);
  ck_assert_int_eq(week_number(  2,  1, 2022, true, 1), -52);
  ck_assert_int_eq(week_number(  3,  1, 2022, true, 1),   1);
  ck_assert_int_eq(week_number(  1,  3, 2022, true, 1),   9);
  ck_assert_int_eq(week_number(  5,  4, 2022, true, 1),  14);
  ck_assert_int_eq(week_number(  9,  5, 2022, true, 1),  19);
  ck_assert_int_eq(week_number( 13,  6, 2022, true, 1),  24);
  ck_assert_int_eq(week_number( 17,  7, 2022, true, 1),  28);
  ck_assert_int_eq(week_number( 21,  8, 2022, true, 1),  33);
  ck_assert_int_eq(week_number( 25,  9, 2022, true, 1),  38);
  ck_assert_int_eq(week_number( 29, 10, 2022, true, 1),  43);
  ck_assert_int_eq(week_number(  1,  1, 2023, true, 1), -52);
  ck_assert_int_eq(week_number(  1,  1, 2024, true, 1),   1);
  ck_assert_int_eq(week_number(  1,  1, 2025, true, 1),   0);
  ck_assert_int_eq(week_number(  1,  1, 2026, true, 1),   0);
  ck_assert_int_eq(week_number(  1,  1, 2027, true, 1), -53);
  ck_assert_int_eq(week_number(  1,  1, 2028, true, 1), -52);
  ck_assert_int_eq(week_number(  1,  1, 2029, true, 1),   1);
  //XXX check with year having 51 weeks
  //XXX probably also check with is_iso_week = false
}
END_TEST

START_TEST(test_utils_weekno2doy)
{
  ck_assert_int_eq(weekno2doy(  1, 2029, true, 1),   1);
  ck_assert_int_eq(weekno2doy(  1, 2028, true, 1),   3);
  ck_assert_int_eq(weekno2doy(  1, 2021, true, 1),   4);
  ck_assert_int_eq(weekno2doy( 52, 2028, true, 1), 360);
  ck_assert_int_eq(weekno2doy( 52, 2027, true, 1), 361);
  ck_assert_int_eq(weekno2doy( 52, 2026, true, 1), 355);
}
END_TEST

Suite *gcal_suite_utils(char *testname)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create(testname);

    /* Core test case */
    tc_core = tcase_create(testname);

    tcase_add_test(tc_core, test_utils_my_atoi);
    tcase_add_test(tc_core, test_utils_julian_gregorian_diff);
    tcase_add_test(tc_core, test_utils_knuth_easter_formula);
    tcase_add_test(tc_core, test_utils_doy2date);
    tcase_add_test(tc_core, test_utils_weekday_of_date);
    tcase_add_test(tc_core, test_utils_day_of_year);
    tcase_add_test(tc_core, test_utils_days_of_february);
    tcase_add_test(tc_core, test_utils_valid_date);
    tcase_add_test(tc_core, test_utils_prev_date);
    tcase_add_test(tc_core, test_utils_next_date);
    tcase_add_test(tc_core, test_utils_week_number);
    tcase_add_test(tc_core, test_utils_weekno2doy);

    suite_add_tcase(s, tc_core);

    return s;
}

