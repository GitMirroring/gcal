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

Suite *gcal_suite_utils(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("GCAL.utils");

    /* Core test case */
    tc_core = tcase_create("utils");

    tcase_add_test(tc_core, test_utils_my_atoi);
    tcase_add_test(tc_core, test_utils_julian_gregorian_diff);
    tcase_add_test(tc_core, test_utils_knuth_easter_formula);

    suite_add_tcase(s, tc_core);

    return s;
}

